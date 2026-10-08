#include "LEDController.h"

void LEDController::begin() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  lastT = millis();
  blinkIntervalMs = BMEConstants::SLOW_BLINK_MS;
  ledState = 0;
}

unsigned long LEDController::mapTemperatureToIntervalMs(
    const float temperature) {
  // Clamp to [MIN_TEMP, MAX_TEMP], then linearly ramp the blink interval:
  // colder -> slower blink, warmer -> faster blink.
  const float tempClamped =
      constrain(temperature, BMEConstants::MIN_TEMP, BMEConstants::MAX_TEMP);
  const float percentage =
      (tempClamped - BMEConstants::MIN_TEMP) /
      (BMEConstants::MAX_TEMP - BMEConstants::MIN_TEMP);

  const float intervalMs =
      float(BMEConstants::SLOW_BLINK_MS) +
      percentage * (float(BMEConstants::FAST_BLINK_MS) -
                    float(BMEConstants::SLOW_BLINK_MS));
  return static_cast<unsigned long>(intervalMs);
}

void LEDController::updateBlinkInterval(const float temperature) {
  if (isnan(temperature)) {
    return; // keep the last known interval if the sensor read is invalid
  }
  blinkIntervalMs = mapTemperatureToIntervalMs(temperature);
}

void LEDController::updateLEDState(const unsigned long now) {
  if (now - lastT >= blinkIntervalMs) {
    lastT = now;
    ledState = !ledState;
    digitalWrite(LED_BUILTIN, ledState ? HIGH : LOW);
  }
}

unsigned long LEDController::getBlinkIntervalMs() const {
  return blinkIntervalMs;
}