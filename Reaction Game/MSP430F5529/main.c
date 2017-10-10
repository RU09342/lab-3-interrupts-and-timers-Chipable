/* Lab 3 reaction game
 * MSP430F5529
 * 10/9/2017
 * Robert Page
 * main.c
 */

#include <msp430.h> 

    volatile int right = 0;
    volatile int left = 0;

int main(void){

    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    /* GPIO INIT*/
    //OUTPUTS
    P1SEL &= ~BIT0;       // sets port mux
    P4SEL &= ~BIT7;       // sets port mux
    P1DIR |= BIT0;    // Sets P1.0 as an output
    P4DIR |= BIT7;    // Sets P1.0 as an output
    //INPUTS
    P2DIR &= ~BIT1;   // sETS P1.1 as an input
    P2REN |= BIT1;    // Enables pull up resistor on P1.1
    P2OUT |= BIT1;    // Sets pull up to VCC

    P1DIR &= ~BIT1;   // sETS P1.1 as an input
    P1REN |= BIT1;    // Enables pull up resistor on P1.1
    P1OUT |= BIT1;    // Sets pull up to VCC

    /* INTERRUPT INIT */
    P2IE |= BIT1;
    P2IES &= ~BIT1;
    P2IFG &= ~BIT1;

    P1IE |= BIT1;
    P1IES &= ~BIT1;
    P1IFG &= ~BIT1;

    _BIS_SR(CPUOFF + GIE);        // Enter LPM0 w/ interrupt

}

#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void){
    P2IE &= ~BIT1;
    _delay_cycles(50000);
    P2IE |= BIT1;

    left += 1;              //adds to the left count

    /*determines the current winner or tie*/
    if (left>right){
        P1OUT |= BIT0;
        P4OUT &= ~BIT7;
    }
    else if(right>left){
        P1OUT &= ~BIT0;
        P4OUT |= BIT7;
    }
    else{
        P1OUT |= BIT0;
        P4OUT |= BIT7;
    }

    P2IFG &= ~BIT1;
}
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void){
    P1IE &= ~BIT1;
    _delay_cycles(50000);
    P1IE |= BIT1;

    right += 1;              //adds to the left count

    /*determines the current winner or tie*/
    if (left>right){
        P1OUT |= BIT0;
        P4OUT &= ~BIT7;
    }
    else if(right>left){
        P1OUT &= ~BIT0;
        P4OUT |= BIT7;
    }
    else{
        P1OUT |= BIT0;
        P4OUT |= BIT7;
    }

    P1IFG &= ~BIT1;
}
