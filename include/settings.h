#pragma once
#include <cstdint>

namespace Settings {
  constexpr uint32_t SampleRate = 44100;
  constexpr uint16_t NumChannels = 2;
  constexpr double STEP = static_cast<double>(1) / static_cast<double>(SampleRate);
}