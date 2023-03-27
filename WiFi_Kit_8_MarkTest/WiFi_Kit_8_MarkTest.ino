/*
   HelTec Automation(TM) wifi kit 8 factory test code, witch include
   follow functions:

   - Basic OLED function test;

   - Basic serial port test(in baud rate 115200);

   - LED blink test;

   - WIFI join and scan test;

   - Timer test and some other Arduino basic functions.

   by Aaron.Lee from HelTec AutoMation, ChengDu, China
   成都惠利特自动化科技有限公司
   www.heltec.cn

   this project also realess in GitHub:
   https://github.com/HelTecAutomation/Heltec_ESP8266
*/
#include "heltec.h"
#include "ESP8266WiFi.h"

char ssid[] = "hubbellwifi"; //"jutland";     //  your network SSID (name)
char pass[] = "Hubbell1905Incorporated";      // your network password

void WIFISetUp(void)
{
  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.disconnect(true);
  delay(100);
  WiFi.mode(WIFI_STA);
  WiFi.setAutoConnect(true);
  WiFi.begin(ssid, pass);
  delay(100);
  Heltec.display->clear();

  byte count = 0;
  while (WiFi.status() != WL_CONNECTED && count < 10)
  {
    count ++;
    Heltec.display->drawString(0, 0, "Connecting...");
    Heltec.display->display();
    delay(1000);
  }
  //Heltec.display->clear();
  if (WiFi.status() == WL_CONNECTED)
  {
    //Heltec.display->drawString(35, 38, "WIFI SETUP");
    Heltec.display->drawString(13*5, 0, "OK");
  }
  else
  {
    //Heltec.display->clear();
    Heltec.display->drawString(0, 9, "Failed");
  }
  Heltec.display->display();
  delay(1000);
  Heltec.display->clear();
 }

void WIFIScan(void)
{
  unsigned int i;
  WiFi.mode(WIFI_STA);

  Heltec.display->drawString(0, 0, "Scan start...");
  Heltec.display->display();

  int n = WiFi.scanNetworks();
  Heltec.display->drawString(14 * 5 , 0, "Scan done");
  Heltec.display->display();
  delay(1000);

  if (n == 0)
  {
    Heltec.display->drawString(0, 9, "no network found");
    delay(1000);
    Heltec.display->display();
  }
  else
  {
    Heltec.display->drawString(0, 9, (String)n + " nets found");
    Heltec.display->display();
    delay(1000);
    for (int i = 0; i < n; ++i) {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*");
      delay(10);
    }
    Heltec.display->clear();
  }
} // end WIFIScan()

void setup()
{
  //  pinMode(LED_BUILTIN,OUTPUT);
  //  digitalWrite(LED_BUILTIN, HIGH);

  Heltec.begin(true /*DisplayEnable Enable*/, true /*Serial Enable*/);

  WIFISetUp();
}

void loop()
{
  WIFIScan();
}
