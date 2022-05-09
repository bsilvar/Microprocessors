#include <seg7.h>

// Define registers for port D
#define gpiod_moder (*((volatile unsigned int*)0x40020c00))
#define gpiod_odr (*((volatile unsigned int*)0x40020c14))

// Define registers for port C
#define gpioc_moder (*((volatile unsigned int*)0x40020800))
#define gpioc_idr (*((volatile unsigned int*)0x40020810))

void delay_ms(int milliseconds); // Prototype of the delay function

int main(){
  unsigned int switches, display_number, hex_val;

  gpioc_moder = 0x00000000; // Port C mode register - make all pins inputs
  gpiod_moder = 0x55555555; // Port D mode register - make all pins output

  /* 0 turns a segment on, 1 turns a segment off, 
   * segment values are in the order gfedcba in the least significant 7 bits */
  seg7_init();          // Initialize the 7-segment display
  seg7_put(0, 0x40);    /* <-- Puts the digit '0' on the right-most display 
                         * note - 0x40 = 0b01000000 (g=off, f=on, e=on, etc.) */
  
  /* initialize array with the hex values which turn on the specific segments 
   * in the 7-seg display to represent each of the 16 hex values. 
   * each hex value matches each index of the array */
  int array[16] = {0x40, 0x79, 0x24, 0x30, 
                   0x19, 0x12, 0x02, 0x78, 
                   0x00, 0x10, 0x08, 0x03, 
                   0x46, 0x21, 0x06, 0x0e};

  while(1){
    switches = gpioc_idr; // Read the switches
    /* Display number 7 is the left-most 7-segment display 
     * Display number 0 is the right-most 7-segment display */
    display_number = switches & (7<<12); // Zero out all switches other than switches 14, 13, and 12
    display_number = display_number>>12; /* <- Move switch values 14:12 down to bits 2:0 
                                          * (we now have an integer in the range 0-7) */
    
    hex_val = switches & 0xf; // Capture the hex value set by using switches [3:0]
 
    if (switches & 0x00008000){ // checks that SW15 is on
      seg7_put(display_number, array[hex_val]); // puts the specified hex value on the display number given by switches 14:12
      //gpiod_odr = seg7_put;
      gpiod_odr = array[hex_val]; /* <-- Displays the seven segment value on LEDs[6:0]. Meaning it
                                   * turns on each LED that corresponds to the segment that was off */
    }
    delay_ms(10);
  }
  return 0;
}

// function for causing delay (in milliseconds)
void delay_ms(int milliseconds){
  int i;
  for (i=0;i<2000*milliseconds;i++){}
}

