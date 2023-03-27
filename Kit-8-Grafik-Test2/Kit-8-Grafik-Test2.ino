// from https://github.com/ThingPulse/esp8266-oled-ssd1306/issues/158
// Arduino IDE: use as "NodeMCU 0.9"
// Grafik-Test2
#include <Arduino.h>
#include "oled.h"
#include <ArduinoOTA.h>  // programming over Wlan

OLED display=OLED(4,5,16); //  sda, scl, reset

static const uint8_t bitmap[] =
{
  1,2,4,8,16,32,64,128,128,128,192,192,128,128,128,64,32,16,8,4,2,1, // first page (8 vertical bits, 22 columns)
  255,255,255,255,15,15,15,15,15,15,15,15,15,15,15,15,15,15,255,255,255,255 // second page (8 vertical bits, 22 columns)
};

void setup()
{
  Serial.begin(115200);
  // Ohne Wifi kein OTA!
  WiFi.mode(WIFI_STA);
  WiFi.begin("hubbellwifi","Hubbell1905Incorporated");
  while (WiFi.waitForConnectResult() != WL_CONNECTED)
  {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }

	Serial.print("WiFi now connected at address: ");
	// Print the IP address
	Serial.println(WiFi.localIP());

  delay(1000);
  display.init();
  ArduinoOTA.setHostname("kit8");
  ArduinoOTA.begin();
  // From now on we cannot use any long lasting delay(), as the
  // OTA handling must be done very often..
}

// Instead we us an own Delay function, which waits and serves OTA
void Delay(int Zeit)
{
  ArduinoOTA.handle();
  for (int i=1; i<=Zeit; i+=20)
  {
    delay(20);
    ArduinoOTA.handle();
  }
}

void DisplayIt() // Even updating the contents of the display is better done with OTA test.
{
  display.display();
  ArduinoOTA.begin();
}

void loop()
{
  ArduinoOTA.handle();
  // Draw pixels in the outer edges
  display.draw_pixel(0,0);
  display.draw_pixel(127,0);
  display.draw_pixel(127,31);
  display.draw_pixel(0,31);
  DisplayIt();

  // Draw hollow circles
  for (uint_least8_t radius=3; radius<62; radius+=3)
  {
    Delay(50);
    display.draw_circle(64,16,radius);
    if (radius>15)
    {
      display.draw_circle(64,16,radius-15,OLED::SOLID,OLED::BLACK);
    }
    DisplayIt();
  }

  // Draw solid circles
  Delay(500);
  display.draw_circle(36,16,14,OLED::SOLID);
  DisplayIt();
  delay(500);
  display.draw_circle(36,16,7,OLED::SOLID,OLED::BLACK);
  DisplayIt();

  // Draw rectangles
  Delay(500);
  display.draw_rectangle(64,0,98,31);
  DisplayIt();
  Delay(500);
  display.draw_rectangle(69,5,93,26,OLED::SOLID);
  DisplayIt();

  // scroll up
  Delay(1000);
  display.scroll_up(32,20);

  // Draw text with normal size
  display.draw_string(4,2,"Hello");
  DisplayIt();

  // Draw a line
  Delay(1000);
  display.draw_line(4,10,34,10);
  DisplayIt();

  // Draw text from program memory with double size
  Delay(1000);
  display.draw_string_P(16,15,PSTR("World!"),OLED::DOUBLE_SIZE);
  DisplayIt();

  // Draw a cross
  Delay(1000);
  display.draw_line(16,31,88,15);
  display.draw_line(16,15,88,31);
  DisplayIt();

  // Draw a raw bitmap
  Delay(1000);
  display.draw_bitmap_P(100,8,22,16,bitmap);
  DisplayIt();

  // Demonstrate scrolling
  Delay(1000);
  display.set_scrolling(OLED::HORIZONTAL_RIGHT);
  Delay(3000);
  display.set_scrolling(OLED::HORIZONTAL_LEFT);
  Delay(3000);
  display.set_scrolling(OLED::NO_SCROLLING);

  // Redraw after scrolling to get the original picture
  DisplayIt();

  // Flash the display
  Delay(1000);
  for (int i=0; i<10; i++)
  {
    display.set_invert(true);
    Delay(200);
    display.set_invert(false);
    Delay(200);
  }

  // Show contrast values
  contrast(128);
  contrast(64);
  contrast(32);
  contrast(16);
  contrast(8);
  contrast(4);
  contrast(2);
  contrast(1);
  contrast(2);
  contrast(4);
  contrast(8);
  contrast(16);
  contrast(32);
  contrast(64);
  contrast(128);
  contrast(255);
  contrast(128);
  Delay(3000);

  display.clear();
}


void contrast(int value)
{
  char buffer[4];
  display.clear();
  ArduinoOTA.handle();
  display.draw_string(0,0,"Contrast:");
  itoa(value,buffer,10);
  ArduinoOTA.handle();
  display.draw_string(64,0,buffer);
  display.draw_rectangle(0,20,value/2,31,OLED::SOLID);
  DisplayIt();
  display.set_contrast(value);
  Delay(500);
}
