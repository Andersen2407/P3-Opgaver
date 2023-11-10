void setup(){


  // Turn interrupt off, so we can run setup code.
  cli();  
  Serial.begin(115200); // Set serial Baud


  TCCR1A = 0; // Set register A to 0.
  TCCR1B = 0; // Set register B to 0.


  TCNT1 = 34285; // Set preloaded time,
  TCCR1B |= B00000101;  // Set prescaler, ...011 = 64, ...101 = 1024
  TIMSK1 |= B00000001;  // Enable Timer Overflow Interrupt, so 1024 -> 0


  pinMode(LED_BUILTIN, OUTPUT); // Setup LED, output.


  sei();  // Enable interrupts.
}


void loop(){
}


ISR(TIMER1_OVF_vect){
  cli();  // Set cli, to avoid interrupts during code (Not really necesary in this code.)


  TCNT1 = 34285;  // Reset preloaded time.
  Serial.println("Hello world");  // Print "Hello World"


  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN)); // switch LED output.
  sei();  // Enable interrupts again.
}
