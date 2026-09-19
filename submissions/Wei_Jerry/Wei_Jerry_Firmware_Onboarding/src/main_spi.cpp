#include "BMEConstants.h"
#include "BMESPIInterface.h"
#include "LEDController.h"
#include <Arduino.h>

void setup() {
  BMESPIInterface &bmeInterface = BMESPIInterfaceInstance::instance();
  if (!bmeInterface.begin()) {
    Serial.println("main_spi.cpp: Failed to initialize.");
  }

  LEDController &ledController = LEDControllerInstance::instance();
  ledController.begin();
}
void loop() {
  LEDControllerInstance::instance().update(
      BMESPIInterfaceInstance::instance().readTemperature());
}