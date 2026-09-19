#include "BMEConstants.h"
#include "BMEI2CInterface.h"
#include "LEDController.h"
#include <Arduino.h>

void setup() {
  BMEI2CInterface &bmeInterface = BMEI2CInterfaceInstance::instance();
  if (!bmeInterface.begin()) {
    Serial.println("main_i2c.cpp: Failed to initialize.");
  }

  LEDController &ledController = LEDControllerInstance::instance();
  ledController.begin();
}
void loop() {
  LEDControllerInstance::instance().update(
      BMEI2CInterfaceInstance::instance().readTemperature());
}