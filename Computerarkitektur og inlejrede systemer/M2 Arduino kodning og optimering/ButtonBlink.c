/* 
NB! Most registers and bits are already named to match the datasheet names,
often just replacing an x with a proper value e.g. DDRx -> DDRB for DDR register for Port B
*/

const int ledPin = 13;
void setup()
{
   // Set digital pin 7 (port 7) as an input
   pinMode(7, INPUT);


   // Onboard LED
   pinMode(ledPin, OUTPUT);
}


void loop()
{
   // Read the state of digital pin 7
   int pin7State = digitalRead(7);
   if (pin7State == HIGH)
   {
       digitalWrite(ledPin, HIGH);
   }
   else
   {
       digitalWrite(ledPin, LOW);
   }
}
