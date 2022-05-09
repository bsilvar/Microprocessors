#include <seg7.h>

// Define clock-enable registers
#define rcc_apb2enr (*((volatile unsigned int*)0x40023844))  // ADC1 clock-enable register (bit 8 is ADC1 enable)

// Define registers for port A
#define gpioa_moder (*((volatile unsigned int*)0x40020000))  // mode register (0b11 for analog)

// Define registers for port D
#define gpiod_moder (*((volatile unsigned int*)0x40020c00))  // mode register (0b01 for output)
#define gpiod_odr (*((volatile unsigned int*)0x40020c14))    // output data register

// Define registers for ADC1
#define adc1_sr (*((volatile unsigned int*)0x40012000))      // ADC1 status register (bit 1 is EOC - end of conversion)
#define adc1_cr2 (*((volatile unsigned int*)0x40012008))     // ADC1 control register 2 (bit 0 is ADON, bit 30 is SWSTART)
#define adc1_dr (*((volatile unsigned int*)0x4001204c))      // ADC1 data register (12-bit, right aligned by default)

void delay_ms(int milliseconds); // Prototype of the delay function

int main() {

   unsigned int adc_value, volts, volts_tenths, volts_hundredths, raw_1000, raw_100, raw_10, raw_1;

   unsigned char segments[] = {0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x02, 0x78,
                               0x00, 0x18, 0x08, 0x03, 0x46, 0x21, 0x06, 0x0e};

   gpioa_moder |= 0x00000003; // Port A mode register - make A0 and analog pin
   gpiod_moder = 0x55555555;  // Port D mode register - make all pins output

   rcc_apb2enr |= 1<<8;  // Turn on ADC1 clock by forcing bit 8 to 1 while keeping other bits unchanged
   adc1_cr2 |= 1;        // Turn on ADC1 by forcing bit 0 to 1 while keeping other bits unchanged

   seg7_init();          // Initialize the 7-segment display
   gpiod_odr = 0;        // Clear all the LEDs

   delay_ms(10);

   adc1_cr2 |= 1<<30;    // Start a conversion on ADC1 by forcing bit 30 to 1 while keeping other bits unchanged

   while(1){
  
      gpiod_odr |= adc1_sr & 1<<1;   // Show ADC1 end of conversion bit on LED1 (on if a conversion ever completed)
      if (adc1_sr & 1<<1) {

        delay_ms(500);               // Wait one second
        adc_value = adc1_dr;         // Read the ADC1 data register (also clears EOC bit)
        gpiod_odr &= 0x0000000f;     // Clear LEDs 14:4
        gpiod_odr |= adc_value<<4;   // Show the 12-bit converted value on LEDs 15:4

        volts = (3*adc_value)/4095;    // Find 1's position of decimal value for voltage on A0 pin
        seg7_put(6, segments[volts]);  // Output 1's position voltage digit to display number 6

        volts_tenths = ((30*adc_value)/4095)%10;
        seg7_put(5, segments[volts_tenths]); 

        volts_hundredths = ((300*adc_value)/4095)%10;
        seg7_put(4, segments[volts_hundredths]); 

        raw_1000 = (adc_value/1000)%10;    //Find 1000's position of raw value for voltage on A0 pin
        seg7_put(3, segments[raw_1000]);   // Output 1000's position raw value digit to display number 3

        raw_100 = (adc_value/100)%10;     
        seg7_put(2, segments[raw_100]); 

        raw_10 = (adc_value/10)%10; 
        seg7_put(1, segments[raw_10]);    

        raw_1 = (adc_value/1)%10;
        seg7_put(0, segments[raw_1]);    

        adc1_cr2 |= 1<<30;    // Start a conversion on ADC1 by forcing bit 30 to 1 while keeping other bits unchanged
      }
    
   delay_ms(10);

   }
   return 0;
}

// function for causing delay (in milliseconds)
void delay_ms(int milliseconds) {
   int i;
   for(i=0;i<2000*milliseconds;i++){}
}

