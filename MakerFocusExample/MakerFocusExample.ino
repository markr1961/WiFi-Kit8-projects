/*
Blink8266, based on Arduino Blink
Turns on a message on for one second, then off for one second, repeatedly. .
This example code is in the public domain.
*/
#include <heltec.h>
// the setup routine runs once when you press reset:
void setup()
{
  Heltec.begin(true /*DisplayEnable Enable*/, true /*Serial Enable*/);
}

// the loop routine runs over and over again forever:
void loop()
{
// clear
  Heltec.display- - >clear();
  Heltec.display- - >display();
  delay(1000); // wait for a second
// show message
  Heltec.display- - >drawString(45, 10, "BLINK!");
  Heltec.display- - >drawLine(40,25,84,2 5);
  Heltec.display- - >display();
  delay(1000); // wait for a second
}
