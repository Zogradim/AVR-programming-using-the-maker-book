// POV toy demo framework //

// ------- Preamble -------- //
#include <avr/io.h>
#include <util/delay.h>

#define DELAYTIME 85
#define LED_PORT  PORTB
#define LED_DDR   DDRB

int main(void) {
  // -------- Inits --------- //
  uint8_t i;
  uint8_t repetitions;
  uint8_t whichLED;
  uint16_t randomNumber=0x1234;
  
  LED_DDR= 0xff;                 /* Set up all of LED pins for output */
  // ------ Event loop ------ //
  while (1) {
  
   for (i=0;i<8;i++){
   	LED_PORT |=(1<<i);
   	_delay_ms(DELAYTIME);
   	}
   for (i=0;i<8;i++){
   	LED_PORT &= ~(1<<i);
   	_delay_ms(DELAYTIME);
   	}
   _delay_ms(5*DELAYTIME);
    
   for (i=7;i<255;i--){
   	LED_PORT |=(1<<i);
   	_delay_ms(DELAYTIME);
   	}
   for (i=7;i<255;i--){
   	LED_PORT &= ~(1<<i);
   	_delay_ms(DELAYTIME);
   	}
   _delay_ms(5*DELAYTIME);
   
   for (repetitions=0; repetitions<75; repetitions++){
   	randomNumber=2053*randomNumber+13849;
   	whichLED= (randomNumber>>8)&0b00000111;
   	LED_PORT^=(1<<whichLED);
   	_delay_ms(DELAYTIME);
   }
   LED_PORT=0;
   _delay_ms(5*DELAYTIME);
  }                                                    /* end mainloop */
  return 0;
}
