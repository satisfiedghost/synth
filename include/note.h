#pragma once
#include <cstddef>
#include <cstdint>

#include "internal/tone.h"

namespace Sounds {

// Higher level note concept
class Note {
  public:
    Note(uint32_t fundamental, float length)
      : m_tone(fundamental)
      , m_length_s(length)
      {}
    Note& slide(uint32_t frequency_to);
    Note& set_volume(uint16_t volume);
    Note& set_phase(double phase_deg);

    float get_length_s() const { return m_length_s; };
    int16_t get_sample() { return m_tone.get_sample(); };
  private:
    Tone m_tone;
    float m_length_s;
};

} // Sounds