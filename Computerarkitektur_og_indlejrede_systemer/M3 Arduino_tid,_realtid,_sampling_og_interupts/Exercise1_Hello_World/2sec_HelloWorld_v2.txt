//Print every 2’nd second
// Define timer compare match register value
int timer1_compare_match;

void setup() { // put your setup code here, to run once
  // disable interupts
  noInterrupts();
  Serial.begin(9600);

  // Initialize Timer1
  TCCR1A = 0;
  TCCR1B = 0;

  // The value the timer counts up to before interrupting
  timer1_compare_match = 31249; // [Clock/(Prescaler * Desired Frequency)] - 1. Here [16 000 000 /1024 * 0.5] = 31249

  // Sets prescaler timer1 to 1024
  TCCR1B |= B00000101;
  // Preload timer with compare match value
  TCNT1 = timer1_compare_match;
  // Enable timer interrrupt
  TIMSK1 |= B00000010;

  // Enable interrrupt
  interrupts();
}

ISR(TIMER1_COMPA_vect) {
// Interrupt Service Routine for compare mode
  TCNT1 = timer1_compare_match;
  // Prints "Hello world"
  Serial.println("Hello World");
}

void loop() {
}