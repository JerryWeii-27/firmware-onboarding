#pragma once

#include "BMEConstants.h"
#include <Adafruit_BME280.h>
#include <etl/singleton.h>

class BMESPIInterface {
public:
  BMESPIInterface();

  bool begin();
  float readTemperature();

private:
  Adafruit_BME280 bme;
};
using BMESPIInterfaceInstance = etl::singleton<BMESPIInterface>;