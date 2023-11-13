#define __SFR_OFFSET 0
#include "avr/io.h"
.global myInit
.global myLoop

// Port is configured to use internal pull-up resistor
// Read the value of the ”button” and flip the lamp state {on/off} for each ”press” of the button
myInit:
  SBI DDRB, 5             ; Set PB5 (the built in LED on Arduino Uno) as output (Pin 13)

  CBI DDRB, 2             ; Set pull-up resistor
  SBI PORTB, 2           ; pin 10 
  RET

myLoop:
  SBIS PINB, 2            ; Skip next instruction if bit in I/O is set.
  SBI PORTB, 5            ; Set PB5 HIGH

  SBIC PINB, 2            ; Skip next instruction if bit in I/O is not set.    
  CBI PORTB, 5            ; Set PB5 LOW