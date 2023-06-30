#include <iostream>
#include <list>
#include <vector>

#include "wav.h"
#include "note.h"
#include "frequencies.h"
#include "util.h"

int main() {

  WAV_File f(20);

  // fair warning, this will probably distort speakers heavily until some smoothing is implemented
  bool left = true;
  for (float i = 0; i < 20; i+= 0.15) {
    auto n = Sounds::Note(D3, 20 - i).set_volume(2000).slide(B0);
    if (left) {
      left = false;
      f.add_note(n, i, Channel::LEFT);
    } else {
      left = true;
      f.add_note(n, i, Channel::RIGHT);
    }
  }

  f.write_file();

  return 0;
}