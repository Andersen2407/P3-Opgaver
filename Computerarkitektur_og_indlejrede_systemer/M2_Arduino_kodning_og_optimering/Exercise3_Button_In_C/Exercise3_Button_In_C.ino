/* 
NB! Most registers and bits are already named to match the datasheet names,
often just replacing an x with a proper value e.g. DDRx -> DDRB for DDR register for Port B
*/

const int ledPin = 13;
void setup()
{
   // Set digital pin 10 (port 10) as an input
   pinMode(10, INPUT_PULLUP);


   // Onboard LED
   pinMode(ledPin, OUTPUT);
}


void loop()
{
   // Read the state of digital pin 10
   int pin10State = digitalRead(10);
   if (pin10State == HIGH)
   {
       digitalWrite(ledPin, HIGH);
   }
   else
   {
       digitalWrite(ledPin, LOW);
   }
}
