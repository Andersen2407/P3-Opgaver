#define __SFR_OFFSET 0
#include "avr/io.h"
.global myInit
.global myLoop

// Make it possible to have a skewed blinking; 2 seconds on, 1 second off
myInit:
  SBI DDRB, 5             ; Set PB5 (the built in LED on Arduino Uno) as output (SET BIT I/O REGISTER)
  RET

myLoop:
  LDI r20, 250            ; Delay for another 250 ms.
  LDI r23, 8              ; Set amount of times the delay should be executed.
  SBI PORTB, 5            ; Set PB5 HIGH (turn on LED)
  CALL Loop_n             ; Loop through x times.
  
  LDI r20, 250            ; Delay for another 250 ms.
  LDI r23, 4              ; Set amount of times the delay should be executed.
  CBI PORTB, 5            ; Set PB5 LOW (CLEAR BIT I/O REGISTER) (turn on LED)
  CALL Loop_n             ; Loop through x times.

  RET         

Loop_n:
  CALL myDelay_ms
  DEC r23                ; DECREMENT by value in register 23.

  CPI r23, 0             ; Compare 8 in r23, with 0, jump if r23 is 0. (Compare Immediate)
  BRNE Loop_n            ; (Branch if not equal)

  RET


myDelay_ms:               ; Used to combine register r30 and r31 to a "16 bit" register to be able to store 4000 in binary ("across" the 2 registers)
  LDI r31, 4000 >> 8      ; high(4000)
  LDI r30, 4000 & 255     ; low(4000)

delaylp:
  SBIW r30, 1             ; (Subtract Immediate from word) (takes 2 cycles)
  BRNE delaylp            ; Takes 2 cycles as long as result is NOT 0 (2 cycles)
                          ; delaylp takes 4 cycles and will loop with a total of 4000 times, giving 4*4000=16000 CPU cycles. As the processor is 16Mhz, this takes roughly 1 ms. 
                          ; By the time the code continues past this comment, there will have passed 1 ms of just looping

  SUBI r20, 1             ; (Subtract immidiate)
  BRNE myDelay_ms         ; r20 stores the number 250, which means that the entire delaylp loop will be delayed for 250 ms in total.

  RET

