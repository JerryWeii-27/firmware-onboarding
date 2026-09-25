#include "BMEConstants.h"
#include "BMEI2CInterface.h"
#include "LEDController.h"
#include <Arduino.h>

void setup() {
  Serial.begin(115200);

  BMEI2CInterfaceInstance::create();
  if (!BMEI2CInterfaceInstance::instance().begin()) {
    Serial.println("main_i2c.cpp: Failed to initialize.");
  }

  LEDControllerInstance::create();
  LEDControllerInstance::instance().begin();
}
void loop() {
  LEDControllerInstance::instance().update(
      BMEI2CInterfaceInstance::instance().readTemperature());
}