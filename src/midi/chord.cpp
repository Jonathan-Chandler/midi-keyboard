#include "chord.hpp"
#include <iostream>

void ChordClass::print_note(std::vector<unsigned char> &message)
{
  static const char note[][3] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};
  int octave;
  int note_index; 

  if (message.size() != 3)
  {
    std::cout << "Unknown note" << std::endl;
    return;
  }
  if (message[2])
  {
    std::cout << "Unknown note" << std::endl;
  }

#if 0
  switch (message[0])
  {
    case MESSAGE_NOTE_ON:
      std::cout << "Start ";
      break;
    case MESSAGE_NOTE_OFF:
      std::cout << "Stop ";
      break;
    default:
      std::cout << "Unknown message" << std::endl;
      return;
  }
#endif

  if (message[2])
    std::cout << "Start ";
  else
    std::cout << "Stop ";

  // Data byte 1 : 0PPP PPPP
  octave = (message[1] / 12) - 1;
  note_index = message[1] % 12;
  std::cout << note[note_index] << octave << std::endl;

#if 0
  std::cout << int(message[0]) << " " << int(message[1]) << " " << int(message[2]) << std::endl;
#endif
}
