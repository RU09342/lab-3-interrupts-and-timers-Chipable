#include <msp430.h> 
/**
 * main.c
 * up timer interrupt on CCR1 and CCR2
 */

    volatile int laps;
    volatile int lap_goal;  // amount of over flows desired
    volatile int end_laps;  // overflows counted in registerd
    volatile int initial;
    volatile int final;
int main(void){


    laps = lap_goal = end_laps = initial = final = 0;

    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5; // Disable the GPIO power-on default high-impedance mode

    /*LED Output*/
    P1DIR=0x01; //sets p1 bit 0 as an output
    P1SEL0=0x00; //sets p1 bit 0 as I/O
    P1OUT=0x00; //Turns led off

    /*Button Input*/
    P1DIR &= ~(1<<1);   // SETS P1.1 as an input
    P1REN |= (1<<1);    // Enables pull up resistor on P1.1
    P1OUT |= (1<<1);    // Sets pull up to VCC

    /* INTERRUPT INIT */
    P1IE |= BIT1;
    P1IES |= BIT1;      //interrupt on posedge
    P1IFG &= ~BIT1;

    TB0CTL= ( MC__UP  + TBSSEL__SMCLK + ID__8);             //up timer, Aclk, div 8

    TB0CCTL1 = (CCIE);
    TB0CCR0= 6250;        // sets maximum timer value
    TB0CCR1= 6250;

    TB1CTL= ( MC__UP  + TBSSEL__SMCLK + ID__8);     //up timer, Aclk, div 8
    TB1CCTL1 = CCIE;
    TB1CCR0= 6250;
    TB1CCR1= 6250;

    _BIS_SR(LPM0_bits + GIE);   //enters low power mode with interrupts
}

// Timer B0 interrupt service routine
#pragma vector=TIMER0_B1_VECTOR
__interrupt void Timer0_B1_ISR (void)
{
        if (laps == lap_goal){
            P1OUT ^= BIT0;          //flips LED 1
            laps = 0;
        }
        else
            laps += 1;

        TB0CCTL1&=~BIT0;    //clears flags
}
// Timer B1 interrupt service routine
#pragma vector=TIMER1_B1_VECTOR
__interrupt void Timer1_B1_ISR (void){
    end_laps += 1;          // keeps track of the number of times the counter resets
    TB1CCTL1&=~BIT0;    //clears flags
}
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void){
    /* DEBOUNCE AND WAIT FLIP EDGE TRIGGER */
    P1IE &= ~BIT1;
    _delay_cycles(50000);
    P1IE |= BIT1;               //re-enable interrupt
    P1IES ^= BIT1;

    if (~P1IES & BIT1){           //if interrupt entered on posedge
        initial = TB1R;
        laps = end_laps = lap_goal = 0;
    }
    else if (P1IES & BIT1){      // executes on the negedge
        final = TB1R;
        if(final>=initial){             // if final ccr value is greater than initial ccr val
            TB0CCR1=final-initial;      //sets new timer ccr
            lap_goal = end_laps;        //sets the amount of overflows
        }
        else if(final<initial){             // if final ccr val is less than initial ccr val
            TB0CCR1=6250-initial-final;
            lap_goal = end_laps - 1;
        }
    }

    P1IFG &= ~BIT1;         // resets flag
}
