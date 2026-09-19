#include "LEDController.h"

void LEDController::begin() { digitalWrite(BMEConstants::LED_PIN, LOW); }

static unsigned long calcInterval(const float temperature) {
  if (temperature < BMEConstants::MIN_TEMP) {
    return BMEConstants::SLOW_BLINK_MS;
  }

  if (temperature > BMEConstants::MAX_TEMP) {
    return BMEConstants::MAX_TEMP;
  }

  const uint32_t tempRange = BMEConstants::MAX_TEMP - BMEConstants::MIN_TEMP;
  const uint32_t blinkRange =
      BMEConstants::SLOW_BLINK_MS - BMEConstants::FAST_BLINK_MS;

  return BMEConstants::FAST_BLINK_MS +
         blinkRange * (temperature - BMEConstants::MIN_TEMP) / tempRange;
}

void LEDController::update(const float temperature) {
  if (isnan(temperature)) {
    Serial.println("Temperature is NaN.");
    return;
  }

  unsigned long deltaT = millis() - lastT;
  if (deltaT > calcInterval(temperature)) {
    ledState = !ledState;
    digitalWrite(BMEConstants::LED_PIN, ledState ? HIGH : LOW);
    lastT = millis();
  }
}