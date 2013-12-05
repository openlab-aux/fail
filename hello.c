#ifndef F_CPU
    #define F_CPU 1000000UL
#endif // F_CPU

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

ISR(TIMER0_OVF_vect) {
    PORTB ^= 0b10000000;            // 
}

int main(void) {
    DDRB = 0b11111111;              // Set PortB to output

    TIMSK |= ( 1 << TOIE0);         // Enable Timer0 Overflow Interrupt

    TCCR0B = 0b00000001;            // Select Internal clock w/o prescale
    /**             --- F_CPU  **/

    TCNT0 = 0;                      // Initialize Timer0 Counter Register to 0
    sei();                          // Global Interrupt enable

    while(1) {                      // Busywork!
    }

    return 0;
}
