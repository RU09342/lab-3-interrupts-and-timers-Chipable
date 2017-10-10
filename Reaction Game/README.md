# Simple Blink
## description
Applicable for code written for the following dev boards:
* FR5994
* FR2311
* F5529
* G2553
* FR6989

The code toggles one of the onboard LEDs when the coresponding button is pressed

## Similarities 
All of the files go through three main sections
* Turn off watchdog timer
* INIT GPIO
* Loop

### Turn Off Watchdog Timer
All of the source files contain the code "WDTCTL = WDTPW | WDTHOLD;", which stops the watchdog timer

### INIT GPIO
All of the source files contain some kind of GPIO initialzation. They all consist of setting the port direction and setting the port muxes. The only changes between dev boards are on the pins configured

### Loop
Finally all the source files have an infinite while loop. Inside the loop there is an if statement that is constntly polling the state of the input pin when the input pin is pulled low by the switch the if statement condition becomes true and toggles the state of the ouput pin. A state variable is set prevent the if statement from being entered again until after the button is released.

## Differences
One of the main differences is that the FR boards require and extra line of code "PM5CTL0 &= ~LOCKLPM5;" to adjust the power settings in order to be able to adjust the P1 registers

## EXTRA WORK
A Debounce function "debounce(int pxin, int bitx)" was implemented for the FR2311 dev board to return the debounced value of an input pin. Although the debounce function was only used with the FR2311 it can be used with the other boards aswell. With inputs of "pxin" and "bitx" this function can be used for any pin on any gpio port.