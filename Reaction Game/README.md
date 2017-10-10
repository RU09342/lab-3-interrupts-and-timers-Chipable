# Button Pressing Game
## description
Applicable for code written for the following dev boards:
* F5529

A 2 player game in which each player tries to press the their button faster than the other.

## How it works
Debounced button interrupts are used to keep track of the button presses. Each time a button is pressed a 1 is added to the corresponding variable. Each button press the two variables are evaluated and the greater variable's corresponding led is lit.
