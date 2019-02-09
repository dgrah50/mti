#include <Arduino.h>
#include <HardwareSerial.h>
#include <Wire.h>
#include <skywriter.h>



#define PIN_TRFR  7    // TRFR Pin of Skywriter
#define PIN_RESET 6    // Reset Pin of Skywriter

long touch_timeout = 0;
int air_wheel_counter = 0;

void setup() {
  Serial.begin(9600);
  Skywriter.begin(PIN_TRFR, PIN_RESET);
  // Bind skywriter events
  Skywriter.onTouch(touch);
  Skywriter.onAirwheel(airwheel);
  Skywriter.onGesture(gesture);
}


void loop() {
  Skywriter.poll(); // Poll for any updates from Skywriter
  if( touch_timeout > 0 ) touch_timeout--; 
}

void gesture(unsigned char type){
  switch (type){
    case SW_FLICK_WEST_EAST:
      Serial.println("FLICK_WEST_EAST");
      break;

    case SW_FLICK_EAST_WEST:
      Serial.println("FLICK_EAST_WEST");
      break;

    case SW_FLICK_SOUTH_NORTH:
      Serial.println("FLICK_SOUTH_NORTH");
      break;

    case SW_FLICK_NORTH_SOUTH:
      Serial.println("FLICK_NORTH_SOUTH");
      break;
  }
}

void airwheel(int delta){
  Serial.println(delta);
}

void touch(unsigned char type){
//  if( touch_timeout > 0 ) {
    return;
//  } else {
//    touch_timeout=40000;
//  Serial.println("TOUCH");
//  }
}
