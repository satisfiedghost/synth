#include <fstream>
#include "wav.h"

void WAV_File::write_file() const {
  std::ofstream output_file("audio.wav", std::ios::binary);
  output_file.write(reinterpret_cast<const char*>(&headers), sizeof(headers));

  // write all samples to disk
  for (size_t i = 0; i < headers.get_samples_per_channel(); i++) {
    for(size_t j = 0; j < Settings::NumChannels; j++) {
      output_file.write(reinterpret_cast<const char*>(&channels[j][i]), sizeof(int16_t));
    }
  }

  output_file.close();
}

// TODO support time (full length for now)
void WAV_File::add_tone(Sounds::Tone& tone) {
  size_t samples_needed = m_time_s * Settings::SampleRate;

  // TODO - maybe make tone sampling const?
  // e.g. ask it for a sample at a time instead of ticking forward each time
  for (size_t i = 0; i < samples_needed; i++) {
    auto sample = tone.get_sample();
    for (size_t j = 0; j < Settings::NumChannels; j++) {
      channels[j][i] += sample;
    }
  }
}

void WAV_File::add_note(Sounds::Note& note, float start_time_s, Channel ch) {
  size_t samples_needed = note.get_length_s() * Settings::SampleRate;

  // TODO - maybe make tone sampling const?
  // e.g. ask it for a sample at a time instead of ticking forward each time

  // Calculate offset into file
  size_t offset = Settings::SampleRate * start_time_s;

  for (size_t i = 0; i < samples_needed; i++) {
    auto sample = note.get_sample();

    switch (ch) {
      case Channel::ALL:
        channels[0][i + offset] += sample;
        channels[1][i + offset] += sample;
      break;
      case Channel::LEFT:
        channels[0][i + offset] += sample;
      break;
      case Channel::RIGHT:
        channels[1][i + offset] += sample;
      break;
      default:
      break;
    }
  }
}