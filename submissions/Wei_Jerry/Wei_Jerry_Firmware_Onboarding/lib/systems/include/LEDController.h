#include "Arduino.h"
#include "BMEConstants.h"
#include <etl/singleton.h>
#include <math.h>

class LEDController {
public:
  LEDController() = default;

  void begin();
  void update(float temperature);

private:
  unsigned long lastT;
  bool ledState;
};

using LEDControllerInstance = etl::singleton<LEDController>;