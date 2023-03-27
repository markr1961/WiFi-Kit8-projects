// example from ebay vendor czb6721960
// https://www.ebay.com/str/czb6721960?_trksid=p2047675.l2563
// https://www.ebay.com/itm/ESP8266-CP2014-0-91-White-Blue-OLED-WiFi-Kit8-Dev-Board-NodeMCU-For-Arduino/143394800436?var=442323948540
/*
  WIFI Kit 8 is a cost-effective Internet development program of things, the main chip using ESP8266, with CP2014 USB to series chip, lithium battery interface and charging and discharging circuit, 32 MByte Flash, WIFI antenna, 0.91 inches OLED display.
  it can be programmed for Arduino and NodeMCU environments. the operation is consistent with NodeMCU.
  leads all the pins of ESP8266
  12 digital pins can be configured to read, write, IIC, SPI, medium, PWM and other functions
  1 AD input
  integrated by 0.91 inches 128 * 32 OLED
  operating voltage: 3.3V ~ 7V
  OLED: 128x32, White
 */
#include <Wire.h>
#include "OLED.h" // <- file not supplied
//0.91s OLED connection:
//SDA -- D4
//SCL -- D5
//RST -- D2
OLED display(SDA, SCL);
void setup()
{
  pinMode(D2, OUTPUT);
  digitalWrite(D2, LOW); // turn D2 low to reset OLED
  delay(50);
  digitalWrite(D2, HIGH); // while OLED is running, must set D2 in high
  Serial.begin(9600);
  Serial.println("OLED test!");
  // Initialize display
  display.begin();
  // Test message
  display.print("Hello ");
  delay(3*1000);
  // Test long message
  display.print("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.");
  delay(3*1000);
  // Test display clear
  display.clear();
  delay(3*1000);
  // Test message positioning
  display.print("TOP-LEFT");
  display.print("4th row", 4);
  display.print("RIGHT-BOTTOM", 7, 4);
  delay(3*1000);
  // Test display OFF
  display.off();
  display.print("3rd row", 3, 8);
  delay(3*1000);
  // Test display ON
  display.on();
  delay(3*1000);
}

int r = 0, c = 0;

void loop()
{
  r = r % 4;
  c = micros() % 6;
  if (r == 0) display.clear();
  display.print("Hello ", r++, c++);
  delay(500);
}
