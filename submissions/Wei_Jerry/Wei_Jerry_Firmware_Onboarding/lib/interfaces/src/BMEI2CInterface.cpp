#include "BMEI2CInterface.h"

bool BMEI2CInterface::begin() {
  // The BME280 sits at 0x76 (SDO low) or 0x77 (SDO high) — try both.
  if (bme.begin(BMEConstants::BME_ADDR)) {
    return true;
  }
  return bme.begin(BMEConstants::BME_ADDR_ALTERNATE);
}

float BMEI2CInterface::readTemperature() { return bme.readTemperature(); }