#pragma once
#include "Arduino.h"
#include "BMEConstants.h"
#include <etl/singleton.h>
#include <math.h>

class LEDController {
public:
  LEDController() = default;

  void begin();
  void updateBlinkInterval(float temperature);
  void updateLEDState(unsigned long now);
  unsigned long getBlinkIntervalMs() const;

private:
  static unsigned long mapTemperatureToIntervalMs(float temperature);

  unsigned long lastT;
  unsigned long blinkIntervalMs;
  bool ledState;
};

using LEDControllerInstance = etl::singleton<LEDController>;