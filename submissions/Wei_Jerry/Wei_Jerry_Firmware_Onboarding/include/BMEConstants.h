#pragma once
#include <Arduino.h>

namespace BMEConstants {

constexpr uint8_t LED_PIN = 13;

constexpr uint32_t FAST_BLINK_MS = 100;
constexpr uint32_t SLOW_BLINK_MS = 1000;

constexpr float MIN_TEMP = 20.0f;
constexpr float MAX_TEMP = 40.0f;
} // namespace BMEConstants