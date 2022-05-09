
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

      switches = gpioc_idr;

      // switches & 0x00000001 will be 1 if SW0 is on and 0 is SW0 is off
      if (switches & 0x00000001) {
        // traverse through the 4 sets of 4 LEDs
        for(int i = 0; i < 4; i++){
           // sets 4 leds to 1 through each iteration of the loop
           gpiod_odr = 0x000f << (4*i);
           // half second delay
           delay_ms(500);
        }
      }
    }

   return 0;
}

// function for causing delay (in milliseconds)
void delay_ms(int milliseconds){
   int i;
   for (i=0;i<2000*milliseconds;i++){}
}

