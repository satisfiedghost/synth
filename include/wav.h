#pragma once
#include <array>
#include <vector>
#include "settings.h"
#include "note.h"
#include <iostream>
#include "util.h"

typedef struct wav_headers {
  const char ckID[4];
  uint32_t ckSize;
  const char Fmt[4];
  const char subCk1ID[4];
  uint32_t subCk1Size;
  uint16_t audioFmt;
  uint16_t numChannels;
  uint32_t sampleRate;
  uint32_t byteRate;
  uint16_t blkAlign;
  uint16_t bitsPerSample;
  const char subChk2Id[4];
  uint32_t subChk2Size;

  wav_headers(size_t time_s) :
    ckID{'R', 'I', 'F', 'F'},
    ckSize(0),
    Fmt{'W', 'A', 'V', 'E'},
    subCk1ID{'f', 'm', 't', ' '},
    subCk1Size(16),
    audioFmt(1),
    numChannels(Settings::NumChannels),
    sampleRate(Settings::SampleRate),
    byteRate(sampleRate * numChannels * 16 / 8),
    blkAlign(numChannels * 16 / 8),
    bitsPerSample(16),
    subChk2Id{'d', 'a', 't', 'a'},
    subChk2Size(0)
    {
      size_t num_samples = sampleRate * time_s * numChannels;
      subChk2Size = num_samples * numChannels * bitsPerSample / 8;
      subChk2Size = 36 + subChk2Size;
    };

    size_t get_num_samples() const {
      return subChk2Size * 8 / numChannels / bitsPerSample;
    }

    size_t get_samples_per_channel() const {
      return get_num_samples() / Settings::NumChannels;
    }

} __attribute__((packed)) wav_headers;

class WAV_File {
public:
  WAV_File (size_t time_s)
    : headers(time_s)
    , channels()
    , m_time_s(time_s)
    {
      for (auto& c : channels) {
        for (size_t i = 0; i < headers.get_samples_per_channel(); i++) {
          c.push_back(0);
        }
      }
    }

    void write_file() const;
    // TODO add time
    void add_tone(Sounds::Tone& tone);
    void add_note(Sounds::Note& note, float start_time_s, Channel ch = Channel::ALL);

private:
  wav_headers headers;
  std::array<std::vector<int16_t>, Settings::NumChannels> channels;
  size_t m_time_s;
};