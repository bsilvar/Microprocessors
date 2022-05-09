#include <seg7.h>

// Define clock-enable registers
#define rcc_ahb1enr (*((volatile unsigned int*)0x40023830))  // CRC clock-enable register (bit 12 is CRC enable)

//define registers for port C
#define gpioc_moder (*((volatile unsigned int*)0x40020800))  // mode register (0b00 for input)
#define gpioc_idr (*((volatile unsigned int*)0x40020810))    // input data register

// Define registers for port D
#define gpiod_moder (*((volatile unsigned int*)0x40020c00))  // mode register (0b01 for output)
#define gpiod_odr (*((volatile unsigned int*)0x40020c14))    // output data register

// Define registers for CRC
#define crc_dr (*((volatile unsigned int*)0x40023000))      // CRC data register (32-bit write or read)
#define crc_cr (*((volatile unsigned int*)0x40023008))      // CR control (write a 1 to bit0 to reset data register to 0xffffffff) 

void delay_ms(int milliseconds); // Prototype of the delay function

int main() {

   unsigned int crc_in_value;

   unsigned char segments[] = {0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x02, 0x78,
                               0x00, 0x18, 0x08, 0x03, 0x46, 0x21, 0x06, 0x0e};

   gpioc_moder = 0x00000000;  // Port C mode register - make all pins input
   gpiod_moder = 0x55555555;  // Port D mode register - make all pins output

   rcc_ahb1enr |= 1<<12;      // Turn on CRC clock
   crc_cr |= 1;               // Reset CRC data register to 0xffffffff

   seg7_init();              // Initialize the 7-segment display
   gpiod_odr = 0;            // Clear all the LEDs

   delay_ms(10);

   while(1) {

      //crc_in_value = 0x00000001;       // next value to inject into the CRC calculation

      crc_in_value = gpioc_idr & 0x00000fff; // using SW11:SW0 to generate the LS 12 bits to the next value to inject into the CRC calculation 

      if(gpioc_idr & 0x00004000) { // if SW[14] is on then 
         gpiod_odr = crc_dr>>16; // display the most-significant 16 bits of CRC on the LEDs
      } else {                      // if SW[14] is off then
         gpiod_odr = crc_dr & 0x0000ffff; // display the least-significant 16 bits of CRC on the LEDs
      }
         
      for(int i = 0; i < 8; i++) { // loop to display the CRC hex value with all 8 segments
         seg7_put(i, segments[(crc_dr>>4*i) & 0xf]); // starting from segment 0, display the correspoding CRC hex value 
      }

      delay_ms(1000);
      if(gpioc_idr & 0x00008000) 
         crc_dr = crc_in_value;         // if SW[15] is on then inject new value

      delay_ms(10);                    // allow time for new CRC value to calculate

   }
   return 0;
}

// function for causing delay (in milliseconds)
void delay_ms(int milliseconds){
   int i;
   for(i=0;i<2000*milliseconds;i++){}
}

