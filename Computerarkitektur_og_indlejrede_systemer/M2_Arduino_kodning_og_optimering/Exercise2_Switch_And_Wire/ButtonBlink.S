#define __SFR_OFFSET 0
#include "avr/io.h"
.global myInit
.global myLoop

// Port is configured to use internal pull-up resistor
// Read the value of the ”button” and flip the lamp state {on/off} for each ”press” of the button
myInit:
  SBI DDRB, 5             ; Set PB5 (the built in LED on Arduino Uno) as output (Pin ~13)


  ; Set pull-up resistor to pin ~10, PB2 (input with enabled pullup)
  CBI DDRB, 2             ; Set Pin ~10 to 0 to be input
  SBI PORTB, 2            ; Set Pin ~10 (enable pull-up resistor)
  RET

myLoop:
  SBIS PINB, 2            ; Skip next instruction if bit in I/O register is set.
  SBI PORTB, 5            ; Set PB5 HIGH

  SBIC PINB, 2            ; Skip next instruction if bit in I/O register is clear.
  CBI PORTB, 5            ; Set PB5 LOW
  