//*
bossButton.c
*/

// ------- Preamble -------- //
#include <avr/io.h>
#include <util/delay.h>
#include "pinDefines.h"
#include "USART.h"

#define F_CPU 1000000UL

static inline void blinkLED(void) {
  LED_PORT |= (1 << LED0);   // Turn on LED
  _delay_ms(200);            // Shorter 200ms blink is more responsive
  LED_PORT &= ~(1 << LED0);  // Turn off LED
}

int main(void) {

  // -------- Inits --------- //
  BUTTON_PORT |= (1 << BUTTON);   /* input mode, turn on pullup */
  LED_DDR |= (1 << LED0);         /* set LED pin as output */
  
  initUSART();
  
  // Flash LED once on startup to show code booted
  blinkLED();

  // ------ Event loop ------ //
  while (1) {

    // Check if button is pressed (Active LOW)
    if (bit_is_clear(BUTTON_PIN, BUTTON)) {
      
      _delay_ms(50); // Small 50ms delay to debounce mechanical switch contacts

      if (bit_is_clear(BUTTON_PIN, BUTTON)) {
        
        // 1. Send 'X' followed by newline so Python readline() detects it instantly
        transmitByte('X');
        transmitByte('\r');
        transmitByte('\n');

        // 2. Blink the LED
        blinkLED();

        // 3. WAIT HERE until the button is released (prevents spamming)
        while (bit_is_clear(BUTTON_PIN, BUTTON)) {
          _delay_ms(10);
        }
      }
    }

  } /* End event loop */
  return 0;
}