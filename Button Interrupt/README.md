# Button Interrupt
## description
Applicable for code written for the following dev boards:
* FR5994
* FR2311
* F5529
* G2553
* FR6989

The code toggles one of the onboard LEDs when the coresponding button is pressed. Instead of using polling like the last lab in this lab interrupts were used to change the state of the button

## Similarities between programs
All of the files use interrupts, while the processor is in low power mode. All of the code that makes the led turn on and off is in a interrupt service routine that triggers on the negedge of the button press. The code uses XOR to toggle the state of the LED output

## Differences
One of the main differences is that the FR boards require and extra line of code "PM5CTL0 &= ~LOCKLPM5;" to adjust the power settings in order to be able to adjust the P1 registers. The other main difference is in what pins are toggled between differnt boards.
