#include <Wire.h>
#include <mpr121.h>

int key = 0;
int red_light_pin= 11;
int green_light_pin = 10;
int blue_light_pin = 9;
void setup() {
  Serial.begin(115200);
  Wire.begin();
  CapaTouch.begin();

  delay(500);
  Serial.println("START"); 
  pinMode(red_light_pin, OUTPUT);
  pinMode(green_light_pin, OUTPUT);
  pinMode(blue_light_pin, OUTPUT);
}
void loop() {
   key=CapaTouch.keyPad();
  /*if (key>=0){
    Serial.print("real key = ");
    Serial.println(key); }*/
  if (key==11)             
  { Serial.println("MIDDLE:");
    RGB_color(255, 0, 0); // Red
  }
  if (key==6)             
  { Serial.print("West:");
    Serial.println("2");
    RGB_color(0, 255, 0); // Green
  }
  if (key==0)             
  { Serial.print("North:");
    Serial.println("4");
    RGB_color(0, 0, 255); // Blue
  }
  if (key==3)
  { Serial.print("North West:");
    Serial.println("3");
    RGB_color(255, 255, 125); // Raspberry
  }
  if (key==9)
  { Serial.print("South West:");
    Serial.println("1");
    RGB_color(0, 255, 255); // Cyan
  }
  if (key==12)
  { Serial.print("South:");
    Serial.println("12");
    RGB_color(255, 0, 255); // Magenta
  }
  if (key==2)
  { Serial.print("South East:");
    Serial.println("7");
    RGB_color(255, 255, 0); // Yellow
  }
  if (key==5)
  { Serial.print("East:");
    Serial.println("6");
    RGB_color(255, 255, 255); // White
  }
  if (key==8)
  { Serial.print("North East:");
    Serial.println("5");
    RGB_color(255, 255, 0); // Yellow
  }

}
void RGB_color(int red_light_value, int green_light_value, int blue_light_value)
 {
  analogWrite(red_light_pin, red_light_value);
  analogWrite(green_light_pin, green_light_value);
  analogWrite(blue_light_pin, blue_light_value);
}