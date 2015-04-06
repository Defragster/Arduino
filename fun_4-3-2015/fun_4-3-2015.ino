#include <Adafruit_NeoPixel.h>

#include <chainPixels.h>
#include <liteLine.h>
#include <neoPixel.h>

#include <blinker.h>
#include <colorObj.h>
#include <idlers.h>
#include <lists.h>
#include <mapper.h>
#include <multiMap.h>
#include <PulseOut.h>
#include <runningAvg.h>
#include <servo.h>
#include <timeObj.h>

#include "shakeNTinkle.h"
#include "sparkle.h"

#define BEEP_ON_MS        .1
#define BEEP_MIN_PEROID   .3
#define BEEP_MAX_PERIOD  4.55

blinker aBlinker(13, BEEP_ON_MS, 1, false);
mapper aToBeep(0, 1023, BEEP_MIN_PEROID, BEEP_MAX_PERIOD);

timeObj  readTimer(10);
timeObj  writeTimer(1000);
timeObj  lightTimer(20);

#define SENS1_SWITCH_PIN  2
#define SENS2_SWITCH_PIN  3

shakeNTinkle sensors(SENS1_SWITCH_PIN,SENS2_SWITCH_PIN);

neoPixel lightStick(8, 4);

sparkle* sparkles = NULL;

void setup() {
  //Serial.begin(9600);
  lightStick.begin();
  aBlinker.setBlink(true);  // This starts the blinking..
  sensors.begin();          // Sets up & starts the sensors.
}


void setPixels(colorObj* color) {

  for (int i = 0; i < 8; i++) {
    lightStick.setPixelColor(i, color);
  }
  lightStick.show();
}


void createSparkle(int maxIndex) {
  
  
  
}

WONT WORK, LOOK AT THE LIST STUFF, GOODNIGHT

void checkSparkles(void) {
  
  sparkle* deadSparkle;
  sparkle* trace;
  
  trace = sparkles;
  while(trace) {
    if (!trace->checkSparkle()) {
      deadSparkle = trace;
      trace = trace->next;
      delete(deadSparkle);
    } else {
      trace = trace->next;
    }
}



void loop() {
  float periodMs;

  idle();
  if (lightTimer.ding()) {
    colorObj result = black.blend(&blue,sensors.getTinkle());
    result = result.blend(&green,sensors.getShake()/4);
    setPixels(&result);
    lightTimer.stepTime();
  }
  
  /*
  if (writeTimer.ding()) {
    Serial.print("tSum1 : "); Serial.print(tSum1); Serial.print(" tSum2 : "); Serial.println(tSum2);
    writeTimer.stepTime();
  }
  
  if (readTimer.ding()) {
    periodMs = aToBeep.Map(analogRead(0));
    aBlinker.setTimes(BEEP_ON_MS,periodMs);
    readTimer.stepTime();

    if (writeTimer.ding()) {
      Serial.println(periodMs);
      writeTimer.stepTime();
    }
  }
    */

}
