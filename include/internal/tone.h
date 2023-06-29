// Tone generation functionality
#include <cstddef>
#include <cstdint>
#include <vector>

namespace Sounds {
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
    , m_phase_abs(0)
    {}

  Tone& set_volume(uint16_t volume);
  Tone& gate(float percent);
  Tone& set_slide_function(double fx);
  Tone& set_phase(double phase_rad);

  // get a sample from the tone
  // increments an internal counter per the global sample rate
  // TODO, support resetting (will be useful for phasing)
  int16_t get_sample();

  double get_fundamental() const { return m_fundamental; };
private:

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

  double m_phase_rel;
  double m_phase_abs;
};
} // Sounds