// Get an AD conversion of the temperature by manual trigger e.g. the button press

const int buttonPin = 2;
int buttonState = 0;


uint16_t read_temperature() {
   // enable conversion
   ADCSRA |= 1<<ADSC;


   // wait for conversion to finish 
   while (ADCSRA & (1<<ADSC)) {};


   uint16_t temperature = ADCL;
   temperature += ADCH<<8;


   return temperature;
}


void enable_temperature_conversion() {
   // Set AD reference to 1.1V (internal) and enable reading the temperature sensor
   // According to Datasheet "24.8 Temperature Measurement"
   ADMUX = (1<<REFS1) | (1<<REFS0) | (1<<MUX3);
}


void setup() {
   Serial.begin(115200);
   enable_temperature_conversion();


   // Attach blink as interrupt whenever the buttonPin is RISING (trigger when the pin goes from low -> high)
   attachInterrupt(digitalPinToInterrupt(buttonPin), blink, RISING);
   pinMode(buttonPin, INPUT);
}
void loop() {}


void blink(){
   Serial.println(read_temperature(), DEC); // print it in base 10
}
