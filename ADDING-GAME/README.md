Final Project

In this project you will build a game that tests how fast you can add two 8-bit unsigned binary numbers.

Game Specifications:

1. SW15 controls whether the game is in run mode (SW15 on) or reset mode (SW15 off). In reset mode, the game clock should be set to 00:00, the 7-segment displays showing the numbers to be added should be blank, and all LEDs should be off.
2. The left-most four 7-segment displays (displays 4 through 7) are the game clock and display the time in the format mm:ss, where mm is the number of minutes and ss is the number of seconds. In run mode these should count up until the correct binary sum is entered on the switches.
3. The right-most four 7-segment displays (displays 0 through 3) show the two 8- bit numbers to be added (in hex). Displays 3 and 2 show one of the 8-bit numbers and displays 1 and 0 show the other 8-bit number. In reset mode these should be blank. In run mode they show the numbers to add.
4. The right-most nine switches (SW[8:0]) are used to enter the binary sum calculated by the player. In run mode the game clock continues to count up until the positions of these nine switches exactly matches the binary sum of the two number on the right-most 7-segment displays. Once the correct switch positions have been achieved, the game clock should stop counting and remain at that count until entering reset mode (even if SW[8:0] are subsequently moved to a wrong value).
5. The two 8-bit values to be added should be chosen randomly each time that SW15 is moved from reset to run mode.
6. In run mode LEDs[8:0] should echo the positions of SW[8:0] with each LED on if and only if the matching switch is on. ECE 330L Microprocessors Lab
7. LEDs[14:11] should flash on and off with an approximately 1 second cycle once the game clock stops. This shows that the player was successful.
