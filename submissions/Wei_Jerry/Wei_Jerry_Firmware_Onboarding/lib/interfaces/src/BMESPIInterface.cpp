#include "BMESPIInterface.h"

bool BMESPIInterface::begin() { return bme.begin(); }

float BMESPIInterface::readTemperature() { return bme.readTemperature(); }