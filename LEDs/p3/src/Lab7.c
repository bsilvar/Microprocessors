
//define registers for port D
#define gpiod_moder (*((volatile unsigned int*)0x40020c00))
#define gpiod_otyper (*((volatile unsigned int*)0x40020c04))
#define gpiod_ospeedr (*((volatile unsigned int*)0x40020c08))
#define gpiod_pupdr (*((volatile unsigned int*)0x40020c0c))
#define gpiod_idr (*((volatile unsigned int*)0x40020c10))
#define gpiod_odr (*((volatile unsigned int*)0x40020c14))

//define registers for port C
#define gpioc_moder (*((volatile unsigned int*)0x40020800))
#define gpioc_otyper (*((volatile unsigned int*)0x40020804))
#define gpioc_ospeedr (*((volatile unsigned int*)0x40020808))
#define gpioc_pupdr (*((volatile unsigned int*)0x4002080c))
#define gpioc_idr (*((volatile unsigned int*)0x40020810))
#define gpioc_odr (*((volatile unsigned int*)0x40020814))

void delay_ms(int milliseconds); //prototype of the delay function

int main(){

   unsigned int switches;

   gpioc_moder = 0x00000000; // Port C mode register
   gpiod_moder = 0x55555555; // Port D mode register

   while(1){
      // Make the switches the input
      switches = gpioc_idr;
	  // Since each switch determines which LED should turn on next,
	  // we set the output gpiod_odr (leds) to be 
	  // equal to the input gpiod_idr (switches)
      gpiod_odr = switches;
    }

   return 0;
}

// function for causing delay (in milliseconds)
void delay_ms(int milliseconds){
   int i;
   for (i=0;i<2000*milliseconds;i++){}
}

