#include "BMESPIInterface.h"

BMESPIInterface::BMESPIInterface() : bme(BMEConstants::CS_PIN) {}

bool BMESPIInterface::begin() { return bme.begin(); }

float BMESPIInterface::readTemperature() { return bme.readTemperature(); }