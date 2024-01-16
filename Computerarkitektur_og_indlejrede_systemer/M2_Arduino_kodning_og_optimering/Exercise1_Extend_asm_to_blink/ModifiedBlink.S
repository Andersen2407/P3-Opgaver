#define __SFR_OFFSET 0
#include "avr/io.h"
.global myInit
.global myLoop

// Make it possible to have a skewed blinking; 2 seconds on, 1 second off
myInit:
  SBI DDRB, 5             ; Set PB5 (the built in LED on Arduino Uno) as output
  RET

myLoop:

  LDI r30, 250            ; Set the delay duration in ms.
  SBI PORTB, 5            ; Set PB5 HIGH

  LDI r23, 8              ; Set amount of times the delay should be executed.
  CALL Loop_n              ; Loop through x times.
  
  LDI r20, 250            ; Delay for another 250 ms.
  CBI PORTB, 5            ; Set PB5 LOW

  LDI r23, 4              ; Set amount of times the delay should be executed.
  CALL Loop_n              ; Loop through x times.

  RET

Loop_n:
  CALL myDelay_ms
  DEC r23

  CPI r23, 0             ; Compare 8 in r23, with 0, jump if r23 is 0.
  BRNE	Loop_n

  RET


myDelay_ms:
  LDI r31, 4000 >> 8      ; high(4000)
  LDI r30, 4000 & 255     ; low(4000)

delaylp:
  SBIW r30, 1
  BRNE delaylp

  SUBI r20, 1
  BRNE myDelay_ms

  RET
