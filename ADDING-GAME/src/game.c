#include <seg7.h>

// Define clock-enable registers
#define rcc_ahb1enr (*((volatile unsigned int*)0x40023830)) // CRC clock-enable register (bit 12 is CRC enable)

// Define registers for port C
#define gpioc_moder (*((volatile unsigned int*)0x40020800)) // mode register (0b00 for input)
#define gpioc_idr (*((volatile unsigned int*)0x40020810))   // input data register

// Define registers for port D
#define gpiod_moder (*((volatile unsigned int*)0x40020c00)) // mode register (0b01 for output)
#define gpiod_odr (*((volatile unsigned int*)0x40020c14))   // output data register

// Define registers for CRC
#define crc_dr (*((volatile unsigned int*)0x40023000))      // CRC data register (32-bit write or read)
#define crc_cr (*((volatile unsigned int*)0x40023008))      // CR control (write a 1 to bit0 to reset data register to 0xffffffff) 

void delay_ms(int milliseconds); // Prototype of the delay function

int main() {

   unsigned int switches, crc_in_value, setOne, setTwo, sum, min, sec;

   unsigned char segments[16] = {0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x02, 0x78, 
                                 0x00, 0x10, 0x08, 0x03, 0x46, 0x21, 0x06, 0x0e};
   
   gpioc_moder = 0x00000000; // Port C mode register - make all pins input
   gpiod_moder = 0x55555555; // Port D mode register - make all pins output

   rcc_ahb1enr |= 1<<12;    // Turn on CRC clock   
   crc_cr |= 1;             // Reset CRC data register to 0xffffffff  
   
   seg7_init();             // Initialize the 7-seg display
   gpiod_odr = 0;           // Clear all the LEDs

   crc_in_value = 0x00000001;     // next value to inject into CRC
   crc_dr = crc_in_value;         // gen ran number
   setOne = crc_dr & 0x000000ff;  // grab the 8 least significant bits from CRC
   crc_dr = crc_in_value;
   setTwo = crc_dr & 0x000000ff;  // grab a second 8 bit value from CRC

   sec = 0;
   min = 0;

   while(1) {      
      switches = gpioc_idr & 0x000001ff;  // Reads switches (SW[8:0]) for binary sum
      gpiod_odr = switches;               // LEDs echo position of SW[8:0]

      if(gpioc_idr & 0x00008000) {        // if SW[15] is on, start game
         seg7_put(0, segments[setOne & 0xf]);      // displays the hex value of the 4-LSb from the first 8-bit number we got from CRC
         seg7_put(1, segments[(setOne>>4) & 0xf]); // displays the next hex value from the first 8-bit number from CRC
         seg7_put(2, segments[setTwo & 0xf]);      // displays the hex value of the 4-LSb from the second 8-bit value we got from CRC
         seg7_put(3, segments[(setTwo>>4) & 0xf]); // displays the next hex value from the second 8-bit number from CRC

         sum = setOne + setTwo; // sum of the two 8-bit numbers

         if(switches == sum) {               // position of the 9 switches matches sum
            while(gpioc_idr & 0x0008000) {   // loop that waits until SW[15] is turned off so that no subsequent move of SW[8:0] can affect the game
               gpiod_odr ^= 0x00007800;      // toggles bits [14:11] to show the player was successful
               delay_ms(250);       // speed of the flashing LEDs[14:11]
            }
         } else {             // no match, game clock continues counting up
            delay_ms(50);     // speed of the game clock
            sec++;
            if(sec == 60) {
               sec = 0;
               min++;
            }
            seg7_put(4, segments[sec % 10]); // display 4, showing seconds
            seg7_put(5, segments[sec / 10]); // display 5, showing tenths seconds
            seg7_put(6, segments[min % 10]); // display 6, showing minutes
            seg7_put(7, segments[min / 10]); // display 7, showing tenths minutes
         }

      } else { // if SW[15] is off, reset 7-seg displays and generate new values for sum
         for(int i = 0; i < 4; i++) {
            seg7_put(i, 0x3f); // Puts dashes (----) on the 4 right-most displays (0x3f makes it so only segment g is on)
         }
         for(int i = 4; i < 8; i++) {
            seg7_put(i, 0x40); // Puts zeros (00:00) on the 4 left-most displays (game clock)
         }
         sec = 0;
         min = 0;
         gpiod_odr = 0;                 // Clear all the LEDs
         crc_dr = crc_in_value;         // gen ran number
         setOne = crc_dr & 0x000000ff;  // grab the 8 least significant bits from CRC
         crc_dr = crc_in_value;
         setTwo = crc_dr & 0x000000ff;  // grab a second 8 bit value from CRC
      }
   }
   return 0;
}

// function for causing delay (in milliseconds)
void delay_ms(int milliseconds){
   int i;
   for (i=0;i<2000*milliseconds;i++){}
}

