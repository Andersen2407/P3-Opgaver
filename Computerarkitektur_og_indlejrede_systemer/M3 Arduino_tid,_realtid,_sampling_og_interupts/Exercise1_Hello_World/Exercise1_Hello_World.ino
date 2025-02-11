void setup(){
  // Turn interrupt off, so we can run setup code.
  cli();  
  Serial.begin(115200); // Set serial Baud

  TCCR1A = 0; // Set register A to 0.
  TCCR1B = 0; // Set register B to 0.

  /*
   * [Clock / (Prescaler * Desired Freq)] - 1 = Compare match value
   * (16_000_000) / (1024*0.5) -1 = 31249
   * 
   * This value will be what the timer is intially set to, and when it reaches its 16-bit maximum of 65000
   *   it "overflows" and goes back to zero (generating the interrupt).
   * TCNT1 is the value in which the timer "starts" counting from. For the timer to count 31249, we use the value
   * 65565 - 31249 = 34285
   */
  TCNT1 = 34285; // Set preloaded time,
  TCCR1B |= B00000101;  // Set prescaler, ...101 = 1024
  TIMSK1 |= B00000001;  // Enable Timer Overflow Interrupt, so when 34285 becomes 0 it interrupts
  
  pinMode(LED_BUILTIN, OUTPUT); // Setup LED, output.

  sei();  // Enable interrupts again
}

// Time 1, overflow vect, interrupts on overflow of the timer set using the prescaler and TCNT1.
ISR(TIMER1_OVF_vect) {
  cli();  // Set cli, to avoid interrupts during code (Not really necessary in this code.)

  TCNT1 = 34285;  // Reset preloaded time.
  Serial.println("Hello world");  // Print "Hello World"

  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN)); // switch LED output.
  sei();  // Enable interrupts again.
}

void loop(){}