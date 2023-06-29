#pragma once
#include <vector>
#include <cstdint>
#include <cstddef>

namespace Sounds {


// Tone generation functionality
class Tone {
public:
  // TODO - support other ctors
  Tone(uint32_t fundamental)
    : m_amplitude(1)
    , m_fundamental(fundamental)
    //, m_ax(1)
    //, m_an(1)
    , m_fx(0)
    //, m_fn(1)
    , m_gate_percent(1)
    , should_gate(false)
    , m_current_step(0)
    , m_phase_rel(0)
    {}

  Tone& set_volume(uint16_t volume);
  Tone& gate(float percent);
  Tone& set_slide_function(double fx);

  // get a sample from the tone
  // increments an internal counter per the global sample rate
  // TODO, support resetting (will be useful for phasing)
  int16_t get_sample();
//private:

  //𝑥(𝑛) = 𝐴 sin(𝜔𝑛 + 𝜑) = 𝐴 sin(2𝜋𝑓𝑛 + 𝜑)
  // where
  // A is amplitude
  // f is the frequency (Hz)
  // 𝜑 is the phase angle (radians)

  uint16_t m_amplitude;
  double m_fundamental;

  // we store the equations for this wave to support modulations

  // Amplitude
  // we support the following for now:
  // A(x) = a * x^n
  double m_ax;
  double m_an;

  // Frequency
  // F(x) = f + xn
  double m_fx;
  double m_fn;

  // Gating
  // TODO - support absoulte gating
  float m_gate_percent;
  bool should_gate;

  // for sample calculation
  size_t m_current_step;

  // TODO phase
  double m_phase_rel;
};

// Higher level note concept
class Note {
  public:
    Note(uint32_t fundamental, float length)
      : m_tone(fundamental)
      , m_length_s(length)
      {}
    Note& slide(uint32_t frequency_to);
    int16_t get_sample() { return m_tone.get_sample(); };
    Note& set_volume(uint16_t volume);

    float get_length_s() const { return m_length_s; };
  private:
    Tone m_tone;
    float m_length_s;
};

} // Sounds