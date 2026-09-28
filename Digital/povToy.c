//This is a program about digital output using buttons//


#include <avr/io.h>
#include <util/delay.h>
#include <pinDefines.h>
#define DEBOUNCE_TIME 1000

uint8_t debounce(void){
if (bit_is_clear(BUTTON_PIN,BUTTON)){
  _delay_us(DEBOUNCE_TIME);
  if (bit_is_clear(BUTTON_PIN,BUTTON)){
  	return(1);
  	}
  	}
  	return(0);
  	}


int main(void){
uint8_t buttonWasPressed;
BUTTON_PORT|= (1<<BUTTON);
LED_DDR=(1<<LED0);


while(1){
	if (debounce()){
	 if (buttonWasPressed==0){
	  LED_PORT ^=(1<<LED0);
	  buttonWasPressed=1;
	  }
	  }
	  else {
	   buttonWasPressed=0;
	   }
	   }
	   return(0);
	   }
