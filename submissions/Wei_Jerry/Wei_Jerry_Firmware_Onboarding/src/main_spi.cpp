#include "BMEConstants.h"
#include "BMESPIInterface.h"
#include "LEDController.h"
#include <Arduino.h>

static unsigned long lastReadMs = 0;

void setup() {
  Serial.begin(115200);

  LEDControllerInstance::create();
  LEDControllerInstance::instance().begin();

  BMESPIInterfaceInstance::create();
  if (!BMESPIInterfaceInstance::instance().begin()) {
    Serial.println("main_spi.cpp: BME280 not found - check wiring/CS pin");
    while (true) {
      digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
      delay(100);
    }
  }
  Serial.println("main_spi.cpp: BME280 ready (SPI)");
}

void loop() {
  const unsigned long now = millis();

  if (now - lastReadMs >= BMEConstants::SENSOR_READ_INTERVAL_MS) {
    lastReadMs = now;
    const float temperature =
        BMESPIInterfaceInstance::instance().readTemperature();
    LEDControllerInstance::instance().updateBlinkInterval(temperature);

    Serial.print("temperature = ");
    Serial.print(temperature);
    Serial.print(" C, blink interval = ");
    Serial.print(LEDControllerInstance::instance().getBlinkIntervalMs());
    Serial.println(" ms");
  }

  LEDControllerInstance::instance().updateLEDState(now);
}