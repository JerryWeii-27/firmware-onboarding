#include "BMEI2CInterface.h"

bool BMEI2CInterface::begin() { return bme.begin(BMEConstants::BME_ADDR); }

float BMEI2CInterface::readTemperature() { return bme.readTemperature(); }