# Timer A Blink
## description
Applicable for code written for the following dev boards:
* FR5994
* FR2311
* F5529
* G2553
* FR6989
This code blinks two of the dev boards leds at two different rates while in a low power mode using timer A.

## Similarities 
All of the files are simillar in that they initialize the timer in up mode and use two ccrn regisers gennerate interrupts to toggle the state of the dev boards onboard leds.

## Differences
One of the main differences is that the FR boards require and extra line of code "PM5CTL0 &= ~LOCKLPM5;" to adjust the power settings in order to be able to adjust the P1 registers. the other main difference is that the boards have their leds on different pins so there are small differences in the code because of that.

## EXTRA WORK
The extra work done for this section was that all of the led blinking was done with the processor in low power mode