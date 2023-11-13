// Generate an interrupt based on a wire connecting an input to ground (use the internal pull-up resistor to avoid floating input).
// Recall the I/O pin – it too has an interrupt possibility so check the data sheet.

void setup(){
  // Turn interrupt off, so we can run setup code.
  cli();  
  Serial.begin(115200); // Set serial Baud

  pinMode(2, INPUT_PULLUP); // Set pin to read from.

  attachInterrupt(digitalPinToInterrupt(2), ISR_func, FALLING); // Set interrupt pin to listen for.
  sei();  // Enable interrupts.
}

void loop(){
}

void ISR_func(){
  cli();  // Set cli, to avoid interrupts during code
  Serial.println("Hello world!");  // Print "Hello World"
  sei();  // Enable interrupts again.
}