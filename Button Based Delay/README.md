# Button Based Delay
## description
Applicable for code written for the following dev boards:
* FR5994
* FR2311
* F5529
* G2553
* FR6989

The code uses timers and the dev board buttons to control the speed of a blinking led. all the boards start with a default blink frequency of 10Hz. Once the button is pressed a timer is used to to keep track of how long the button was pressed. Then that number of overflows and the TAR0 register value is used to determine the amount of time before the LED state is toggled again.

## Similarities 
All the code is structurally the same. They have a few vairables to keep track of the TAR0 reg when the button is first pressed and another to keep track of the TAR0 reg when the button is let go. another variable is used to keep track of the number of overflows in the timer. All of this information is then unsed in the timer ISR that controls the led output state.

Debouncing was also used to be sure the timing was not incorect from erronous interrupts

## Differences
One of the main differences is that the FR boards require and extra line of code "PM5CTL0 &= ~LOCKLPM5;" to adjust the power settings in order to be able to adjust the P1 registers. Another difference is the timers used. The FR2311 for example does not have a timer A.

## EXTRA WORK
F5529
a reset button was implemented to set the blinking led back to 10Hz

another interrupt was added to reset the number of wrap arounds and the TACCR1 register