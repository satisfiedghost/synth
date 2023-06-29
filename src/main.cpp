#include <iostream>
#include <list>
#include <vector>

#include "wav.h"
#include "note.h"
#include "frequencies.h"

int main() {

  WAV_File f(20);

  // fair warning, this will probably distort speakers heavily until some smoothing is implemented
  //for (float i = 0; i < 10; i+= 1) {
    //auto n = Sounds::Note(D3, 10 - i).set_volume(5000).slide(B0);
    //f.add_note(n, i);
  //}
  auto n = Sounds::Note(D3, 3).set_volume(5000);
  f.add_note(n, 0);
  n = Sounds::Note(D3 * 2, 3).set_volume(3000);
  f.add_note(n, 0);
  n = Sounds::Note(D3 * 3, 3).set_volume(1000);
  f.add_note(n, 0);


  f.write_file();

  return 0;
}