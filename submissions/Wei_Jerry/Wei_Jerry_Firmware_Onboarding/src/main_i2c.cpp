#include "BMEConstants.h"
#include "BMEI2CInterface.h"
#include "LEDController.h"
#include <Arduino.h>

static unsigned long lastReadMs = 0;

void setup() {
  Serial.begin(115200);

  LEDControllerInstance::create();
  LEDControllerInstance::instance().begin();

  BMEI2CInterfaceInstance::create();
  if (!BMEI2CInterfaceInstance::instance().begin()) {
    Serial.println("main_i2c.cpp: BME280 not found - check wiring/address");
    while (true) {
      digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
      delay(100);
    }
  }
  Serial.println("main_i2c.cpp: BME280 ready (I2C)");
}

void loop() {
  const unsigned long now = millis();

  if (now - lastReadMs >= BMEConstants::SENSOR_READ_INTERVAL_MS) {
    lastReadMs = now;
    const float temperature =
        BMEI2CInterfaceInstance::instance().readTemperature();
    LEDControllerInstance::instance().updateBlinkInterval(temperature);

    Serial.print("temperature = ");
    Serial.print(temperature);
    Serial.print(" C, blink interval = ");
    Serial.print(LEDControllerInstance::instance().getBlinkIntervalMs());
    Serial.println(" ms");
  }

  LEDControllerInstance::instance().updateLEDState(now);
}