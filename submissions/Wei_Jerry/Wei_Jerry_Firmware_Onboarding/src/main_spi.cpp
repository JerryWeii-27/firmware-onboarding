#include "BMEConstants.h"
#include "BMESPIInterface.h"
#include "LEDController.h"
#include <Arduino.h>

void setup() {
  Serial.begin(115200);

  BMESPIInterfaceInstance::create();
  if (!BMESPIInterfaceInstance::instance().begin()) {
    Serial.println("main_spi.cpp: Failed to initialize.");
  }

  LEDControllerInstance::create();
  LEDControllerInstance::instance().begin();
}
void loop() {
  LEDControllerInstance::instance().update(
      BMESPIInterfaceInstance::instance().readTemperature());
}