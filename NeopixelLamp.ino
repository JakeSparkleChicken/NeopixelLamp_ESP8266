#include <Adafruit_NeoPixel.h>

#include "ESP8266WiFi.h"
#define PIN 05
const char* ssid     = "SSID";
const char* password = "PASSWORD";
const char* host = "IP address or FQDN";

Adafruit_NeoPixel strip = Adafruit_NeoPixel(5, PIN, NEO_GRB + NEO_KHZ800);
uint8_t ledred;
uint8_t ledgreen;
uint8_t ledblue;

void setup() {
  Serial.begin(9600);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  strip.begin();
  strip.show();
}

void loop() {
  String colortype;
  WiFiClient client;
  const int httpPort = 80;
  client.connect(host, httpPort);
  client.print(String("GET /color/color.txt ") + "HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  delay(10);
  while(client.available()){
    colortype = client.readStringUntil('\n');
    Serial.println(colortype);
  }
  String colorval = colortype.substring(1,7);
  char colorvalchar[6];
  strcpy(colorvalchar, colorval.c_str());
  char greenchar[] = {colorvalchar[2], colorvalchar[3], NULL};
  char redchar[] = {colorvalchar[0], colorvalchar[1], NULL};
  char bluechar[] = {colorvalchar[4], colorvalchar[5], NULL};
  ledgreen = (int)strtol(greenchar, NULL, 16);;
  ledblue = (int)strtol(bluechar, NULL, 16);;
  ledred = (int)strtol(redchar, NULL, 16);
  Serial.println(strip.Color(ledred, ledblue, ledgreen));
  colorCheck(strip.Color(ledred, ledgreen, ledblue), ledred, ledgreen, ledblue);

  
  //colorFlowDown(ledred, ledgreen, ledblue, 100);
  
}



void colorFade(uint8_t r, uint8_t g, uint8_t b, uint8_t wait) {
  Serial.println("Display");
  Serial.println(r);
  Serial.println(g);
  Serial.println(b);
  for(uint16_t i = 0; i < strip.numPixels(); i++) {
      uint8_t curr_r, curr_g, curr_b;
      uint32_t curr_col = strip.getPixelColor(i); // get the current colour
      curr_b = curr_col & 0xFF; curr_g = (curr_col >> 8) & 0xFF; curr_r = (curr_col >> 16) & 0xFF;  // separate into RGB components

      while ((curr_r != r) || (curr_g != g) || (curr_b != b)){  // while the curr color is not yet the target color
        if (curr_r < r) curr_r++; else if (curr_r > r) curr_r--;  // increment or decrement the old color values
        if (curr_g < g) curr_g++; else if (curr_g > g) curr_g--;
        if (curr_b < b) curr_b++; else if (curr_b > b) curr_b--;
        strip.setPixelColor(i, curr_r, curr_g, curr_b);  // set the color
        strip.show();
        delay(wait);  // add a delay if its too fast
      }
      //delay(1000);
  }
}



void colorCheck(uint32_t setcolor, uint8_t r, uint8_t g, uint8_t b)
{
  Serial.println(setcolor);
  Serial.println(strip.getPixelColor(0));
  if (!setcolor)
  {
    Serial.println("Off");
    colorFade(0,0,0,20);
  }
  else if (setcolor == strip.getPixelColor(0))
  
  {
    Serial.println("Same");
    colorChange(r, g, b);
  }
  else
  {
    Serial.println("Different");
    colorFade(r, g, b, 10);
   }
}

void colorChange(uint8_t r, uint8_t g, uint8_t b)
{
  if(r<225)
    {
      r=r+25;
    }
    else
    {
      r=r-25;
    }
    if(g<225)
    {
      g=g+25;
    }
    else
    {
      g=g-25;
    }
    if(b<225)
    {
      b=b+25;
    }
    else
    {
      b=b-25;
    }
    Serial.println(r);
    Serial.println(g);
    Serial.println(b);
    colorFade(r, g, b, 10);
    
}
