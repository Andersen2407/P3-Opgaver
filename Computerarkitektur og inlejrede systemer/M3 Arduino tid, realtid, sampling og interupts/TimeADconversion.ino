// Get an AD conversion of the temperature triggered by time

float read_temperature(){
  // enable conversion
  ADCSRA |= 1<<ADSC;

  while (ADCSRA & (1<<ADSC)) {}; // Wait until we are ready.
  uint16_t temperature = ADCL;
  temperature += ADCH<<8;

  return (float(temperature)/10);
}

void setup(){
    cli();  
    Serial.begin(115200); // Set serial Baud

    ADMUX = (1<<REFS1) | (1<<REFS0) | (1<<MUX3);

    TCCR1A = 0; // Set register A to 0.
    TCCR1B = 0; // Set register B to 0.

    TCNT1 = 49910; // Set preloaded time,
    TCCR1B |= B00000101;  // Set prescaler, ...011 = 64, ...101 = 1024
    TIMSK1 |= B00000001;

    sei();
}

void loop(){
}

ISR(TIMER1_OVF_vect){
  cli(); // disable interrupts
  TCNT1 = 49910;
  Serial.println(read_temperature(), DEC);
  sei();  // enable interrupts
}