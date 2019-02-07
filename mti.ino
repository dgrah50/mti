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
}

void gesture(unsigned char type){
  switch (type){
    case SW_FLICK_WEST_EAST:
      Serial.print("FLICK_WEST_EAST")
      break;

    case SW_FLICK_EAST_WEST:
      Serial.print("FLICK_EAST_WEST")
      break;

    case SW_FLICK_SOUTH_NORTH:
      Serial.print("FLICK_SOUTH_NORTH")
      break;

    case SW_FLICK_NORTH_SOUTH:
      Serial.print("FLICK_NORTH_SOUTH")
      break;
  }
}

void airwheel(int delta){
  Serial.print("AIRWHEEL"+delta);
}

void touch(unsigned char type){
  Serial.println("TOUCH");
}
