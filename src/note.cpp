#include <cmath>
#include "note.h"
#include "settings.h"


Sounds::Note& Sounds::Note::slide(uint32_t frequency_to) {
  // Calculate the fx and fn factors, given the initial frequency and a final frequency
  // Only supports linear for now

  // TODO handle case where "to" is the same
  int32_t freq_diff = static_cast<int32_t>(frequency_to) - static_cast<int32_t>(m_tone.get_fundamental());

  // m = (y2 - y1) / (x2 - x1)
  double m = static_cast<double>(freq_diff) / m_length_s;
  m_tone.set_slide_function(m); // linear only

  return *this;
}

Sounds::Note& Sounds::Note::set_volume(uint16_t volume) {
  m_tone.set_volume(volume);
  return *this;
}

Sounds::Note& Sounds::Note::set_phase(double phase_deg) {
  double phase_rad = (phase_deg * M_PI) / 180.;
  m_tone.set_phase(phase_rad);

  return *this;
}