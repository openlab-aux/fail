#ifndef F_CPU
    #define F_CPU 1000000UL         // CPU Freq. is 1MHz.
#endif // F_CPU

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

ISR(TIMER0_COMPB_vect) {
    PORTB &= ~0b10000000;           // Set Pin 1 to LOW
}

ISR(TIMER0_COMPA_vect) {
    PORTB &= ~0b01000000;           // Set Pin 2 to LOW
}

ISR(TIMER1_COMPA_vect) {
    PORTB &= ~0b00100000;           // Set Pin 3 to LOW
}

ISR(TIMER0_OVF_vect) {
    PORTB |= 0b11000000;            // Set Pins 1 and 2 to HIGH
}
ISR(TIMER1_COMPB_vect) {
    TCNT1 = 0;                      // We use COMPB to limit Timer0 to 8 bits.
    PORTB |= 0b00100000;            // Don't show this to actual embedded-devs.
                                    // They might cut you.
                                    // Also, set Pin 3 to HIGH.
}

void init_timer() {
    DDRB = 0b11100000;              // Set PortB to output

    TIMSK |= ( 1 << TOIE0);         // Enable Timer0 Overflow Interrupt
    TIMSK |= ( 1 << OCIE0A);        // Enable Timer0 Overflow Interrupt
    TIMSK |= ( 1 << OCIE0B);        // Enable Timer0 Overflow Interrupt

    TIMSK |= ( 1 << OCIE1A);
    TIMSK |= ( 1 << OCIE1B);
    

    OCR0A = 0;                      // Set Timer0 Output Compare Register A (Pin 2)
    OCR0B = 0;                      // Set Timer0 Output Compare Register B (Pin 1)
    OCR1A = 0;                      // Set Timer1 Output Compare Register (Pin 3)

    OCR1B = 254;                    // Might be off by one.

    TCCR0B = 0b00000001;            // Select Internal clock w/o prescale
    TCCR1B = 0b00000001;            // Select Internal clock w/o prescale
    /**             --- F_CPU  **/

    TCNT0 = 0;                      // Initialize Timer0 Counter Register to 0
    TCNT1 = 0;                      // Same with Timer 1
}

int main(void) {
    init_timer();

    sei();                          // Global Interrupt enable

    while(1) {                      // Busywork!
        OCR0A = (OCR0A + 10) % 255;
        OCR0B = (OCR0B + 10) % 255;
        OCR1A = (OCR1A + 10) % 255;
        _delay_ms(10);
    }

    return 0;
}
