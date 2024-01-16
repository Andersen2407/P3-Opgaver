// Get an AD conversion of the temperature by manual trigger e.g. the button press
const int buttonPin = 2;

void enable_temperature_conversion() {
   // Set AD reference to 1.1V (internal) and enable reading the temperature sensor
   // According to Datasheet "23.8 Temperature Measurement"
   ADMUX = (1<<REFS1) | (1<<REFS0) | (1<<MUX3);
   // ADMUX is the ADC (Analog to digital converter) Multiplexer Select (ADMUX).
   // It selects a reference source (REFS pins - 1.1V internal reference)
   // Also selects an analog source (via the MUX pins -> MUX3 -> Selects the interval temperature sensor)
}

void setup() {
   Serial.begin(115200);
   enable_temperature_conversion();

   // Attach blink as interrupt whenever the buttonPin is RISING (trigger when the pin goes from low -> high)
   attachInterrupt( digitalPinToInterrupt(buttonPin), blink, RISING);
   pinMode(buttonPin, INPUT_PULLUP);
}

void blink(){
   // enable fast conversion (spares 13 ticks and doesn't need to set the ADEN bit)
   ADCSRA |= 1<<ADSC;

   // wait for conversion to finish (ADSC will be set to 0 again when conversion is finished)
   while (ADCSRA & (1<<ADSC)) {};

   // Load the results 8 lower bits and 8 upper bits into a variable
   uint16_t temperature = ADCL;
   temperature += ADCH<<8;

   float t = float(temperature) / 10;

   Serial.println(t, DEC); // print it in base 10
}

void loop() {}