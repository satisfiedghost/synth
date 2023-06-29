#include <cmath>

#include "settings.h"
#include "internal/tone.h"

Sounds::Tone& Sounds::Tone::set_volume(uint16_t volume) {
  m_amplitude = volume;
  m_ax = volume;
  m_an = 1;
  return *this;
}

Sounds::Tone& Sounds::Tone::gate(float percent) {
  m_gate_percent = percent;
  should_gate = true;

  return *this;
}

int16_t Sounds::Tone::get_sample() {
  // calculate the actual sample value for the tone
  double sample_amplitude = m_amplitude;


  double curr_freq = m_fundamental + (static_cast<double>(m_current_step) * m_fx * Settings::STEP);

  double sample_value = std::sin(2 * M_PI * curr_freq *
                                static_cast<double>(m_current_step) * Settings::STEP + 
                                m_phase_rel);

  double sample = sample_amplitude * sample_value;

  // TODO - master clock
  // if we're sliding, we need to factor a phase angle between two discrete waveforms
  if (m_fx != 0) {
    // modf requires this
    double throwaway;

    // total number of periods which have occurred for the current wave, at the current point in time
    double total_periods_curr = (static_cast<double>(m_current_step + 1) * Settings::STEP) /
                           (1 / (m_fundamental + (static_cast<double>(m_current_step) * m_fx * Settings::STEP)));

    // total number of periods which will have occurred for the next wave, at the next point in time
    double total_periods_next = (static_cast<double>(m_current_step + 1) * Settings::STEP) /
                           (1 / (m_fundamental + (static_cast<double>(m_current_step + 1) * m_fx * Settings::STEP)));

    // we only care about the radians in the current period
    double rad_curr = 2 * M_PI * std::modf(total_periods_curr, &throwaway);
    double rad_next = 2 * M_PI * std::modf(total_periods_next, &throwaway);

    // find the angle between these two waveforms
    // note: this is actually undefined for waves with dissimilar frequencies, but
    // it provides a close enough value here
    double angle = rad_curr - rad_next;

    m_phase_rel += angle;

    if (std::abs(m_phase_rel) > 2 * M_PI) {
      m_phase_rel = (m_phase_rel > 0) ?
                     m_phase_rel - (2 * M_PI) :
                     m_phase_rel + (2 * M_PI);
    }
  }

  if (should_gate) {
    if (std::abs(sample) > sample_amplitude * m_gate_percent) {
      sample *= m_gate_percent;
    }
  }

  m_current_step++;
  return static_cast<int16_t>(sample);
}

Sounds::Tone& Sounds::Tone::set_slide_function(double fx) {
  m_fx = fx;
  //m_fn = fn;
  return *this;
}