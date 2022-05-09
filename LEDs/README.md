# LED manipulation using the "c" Programming Language

## For the STM32F4 DISCOVERY board.

The rightmost 16 slide switches of the DE2 board are connected to Port-C GPIO pins of the F4.
The rightmost 16 LEDs of the DE2 board connected to Port-D GPIO pins of the F4.

MODER: 00 for input behavior, 01 for output behavior
IDR(input data register)
ODR(output data register)

Program 1: Turn on LEDs[3:0] while all others are off, then wait half a second.
Repeat for LEDs [7:4], [11:8] and [15:12].

Program 2: Turn on 1 LED consecutively from LED[0] to LED[15] so that only one
led is on at a time and waits half a second between each transition.

Program 3: Read the status of the sixteen switches and if SW[n] is on make LED[n] on.
