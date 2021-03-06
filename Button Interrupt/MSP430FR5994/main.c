/* Lab 3 Button LED Toggle w\ interrupt
 * MSP430FR5994
 * 10/4/2017
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
    P1OUT &= ~BIT0;

    P5DIR &= ~(1<<6);   // sETS P1.1 as an input
    P5REN |= (1<<6);    // Enables pull up resistor on P1.1
    P5OUT |= (1<<6);    // Sets pull up to VCC
    P5SEL0 &= ~(1<<6);       // sets port mux
    P5SEL1 &= ~(1<<6);       // sets port mux


    /* INTERRUPT INIT */
    P5IE |= BIT6;
    P5IES &= ~BIT6;
    P5IFG &= ~BIT6;

    _BIS_SR(CPUOFF + GIE);        // Enter LPM0 w/ interrupt

}

#pragma vector=PORT5_VECTOR
__interrupt void Port_1(void){
    P1OUT ^=(1<<0);
    P5IFG &= ~BIT6;
}
