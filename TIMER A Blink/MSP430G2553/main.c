
#include <msp430.h> 
/**
 * main.c
 * up timer interupt on CCR1 and CCR2
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    P1DIR=0x01; //sets p1 bit 0 as an output
    P1SEL=0x00; //sets p1 bit 0 as I/O
    P1OUT=0x00; //Turns led off
    P1DIR |= BIT6; //sets p1 bit 0 as an output

    TA1CTL= ( MC_1  + TASSEL_2 + ID_3);//updown timer, Aclk, div 1

    TA1CCTL1 = (CCIE);

    TA1CCTL2 = (CCIE);

    TA1CCR0=0xFFFF; // sets maximum timer value

    TA1CCR1=62500; // sets CCR1 interupt value

    TA1CCR2=30000; // sets CCR2 interupt value

    _BIS_SR(LPM0_bits + GIE);//enters low power mode with interupts
}

// Timer A0 interrupt service routine
#pragma vector=TIMER1_A1_VECTOR
__interrupt void Timer1_A1_ISR (void)
{
    switch(TA1IV){
    case 0x02:              // CCR1 COMPARE
        P1OUT ^= BIT0;      //flips LED 1
        TA1CCTL1&=~BIT0;    //clears flags
        break;
    case 0x04:              // CCR2 COMPARE
        P1OUT ^= BIT6;      //flips LED 2
        TA1CCTL2&=~BIT0;    //clears flags
        break;
    }

}
