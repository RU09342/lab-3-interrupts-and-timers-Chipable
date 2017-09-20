/* Lab 3 Button LED Toggle w\ interrupt
 * MSP430FR2311
 * 9/20/2017
 * Robert Page
 * main.c
 */

#include <msp430.h> 

int main(void){

    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;  // adjust power settings

    /* GPIO INIT*/
    P1SEL0 &= ~(1<<0);       // sets port mux
    P1SEL1 &= ~(1<<0);       // sets port mux
    P1DIR |= (1<<0);    // Sets P1.0 as an output
    P1DIR &= ~(1<<1);   // sETS P1.1 as an input
    P1REN |= (1<<1);    // Enables pull up resistor on P1.1
    P1OUT |= (1<<1);    // Sets pull up to VCC

    /* INTERRUPT INIT */
    P1IE |= BIT1;
    P1IES &= ~BIT1;
    P1IFG &= ~BIT1;

    _BIS_SR(CPUOFF + GIE);        // Enter LPM0 w/ interrupt

    while(1){}
}

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void){
    P1OUT ^=(1<<0);
    P1IFG &= ~BIT1;
}
