// Get an AD conversion of the temperature triggered by time
void setup(){
    cli();  
    Serial.begin(115200); // Set serial Baud

    // Set AD reference to 1.1V (internal) and enable reading the temperature sensor
    // According to Datasheet "23.8 Temperature Measurement"
    ADMUX = (1<<REFS1) | (1<<REFS0) | (1<<MUX3);
    // ADMUX is the ADC (Analog to digital converter) Multiplexer Select (ADMUX).
    // It selects a reference source (REFS pins - 1.1V internal reference)
    // Also selects an analog source (via the MUX pins -> MUX3 -> Selects the interval temperature sensor)

  
    TCCR1A = 0; // Set register A to 0.
    TCCR1B = 0; // Set register B to 0.

   /*
    * Clock counts up 
    * [Clock / (Prescaler * Desired Freq)] - 1 = Compare match value
    * (16_000_000) / (1024*1.0) -1 = 15624
    * This value will be what the timer is intially set to, and when it reaches its 16-bit maximum of 65565
    *   it "overflows" and goes back to zero (generating the interrupt).
    * TCNT1 is the value in which the timer "starts" counting from. For the timer to count 15624, we use the value
    * The clock will overflow at 2^16 = 65536
    * We calculate the start time: 65565 - 15624 = 49941
    */

    TCNT1 = 49941; // Set preloaded time,
    TCCR1B |= B00000101;  // Set prescaler, ...011 = 64, ...101 = 1024
    TIMSK1 |= B00000001;  // Enable Timer Overflow Interrupt, so when 49941 becomes 0 it interrupts

    sei();
}

float read_temperature(){
  // enable fast conversion (spares 13 ticks and doesn't need to set the ADEN bit)
  ADCSRA |= 1<<ADSC;
  // wait for conversion to finish (ADSC will be set to 0 again when conversion is finished)
  while (ADCSRA & (1<<ADSC)) {}

  uint16_t temperature = ADCL;    // Store the low-bits of the converted value
  temperature += ADCH<<8;         // Store the high-bits of the converted value (because ADCH is a 8-bit register but represents the high-bits of a 16-bit register, shift it 8 places to the left)

  return (float(temperature)/10);
}

// Time 1, overflow vect, interrupts on overflow of the timer set using the pre-scaler and TCNT1.
ISR(TIMER1_OVF_vect){
  cli(); // disable interrupts
  TCNT1 = 49941;
  Serial.println(read_temperature(), DEC);
  sei();  // enable interrupts
}

void loop(){}


