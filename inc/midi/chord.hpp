#ifndef __CHORD_HPP__
#define __CHORD_HPP__
#include <vector>

#if 0
The NOTE ON message is structured as follows:
Status byte : 1001 CCCC
Data byte 1 : 0PPP PPPP
Data byte 2 : 0VVV VVVV

The NOTE OFF message is structured as follows:
Status byte : 1000 CCCC
Data byte 1 : 0PPP PPPP
Data byte 2 : 0VVV VVVV

"CCCC" is the MIDI channel (from 0 to 15)
"PPP PPPP" is the pitch value (from 0 to 127)
"VVV VVVV" is the velocity value (from 0 to 127)

The pitch value determines the frequency of the note to be played. It goes from 0 to 127, with the middle C note being represented by the value of 60

ex
t=0 : 0x90 - 0x43 - 0x40 (Start of G3 note, pitch= 67)

ex 
start of note, pitch=57, velocity=89
Byte 0 = 0x90, Byte 1 = 0x59, Byte 2 = 0x39
Byte 0 = 0x90, Byte 1 = 89, Byte 2 = 57

#endif 

#define MESSAGE_TYPE_OFFSET   4
#define MESSAGE_TYPE_MASK     (0xF << MESSAGE_TYPE_OFFSET) // 0xF0
#define MESSAGE_NOTE_ON       0x90
#define MESSAGE_NOTE_OFF      0x80

class ChordClass
{
  public:
    ChordClass(){};
    void print_note(std::vector<unsigned char> &message);

//  private:
    /* There are TWO conventions for numbering keys (notes) in MIDI. The most common is the one below where MIDDLE C
     * (note #60; $3C) is C3 (C in the 3rd octave). However, another convention was adopted by Yamaha Corp. for their
     * synthesizer products which parallels the Octave Designation System used in Music Education formulated by the
     * Acoustical Society of America. In that convention, Middle C is designated "C4". The "C3 Convention" is the most
     * commonly used octave designation system on standard MIDI keyboards */

    // Middle C4 = 60
    // G3 = 67
    // A | A# | B | C | C# | D | D# | E | F | F# | G | G#
};

#endif // __CHORD_HPP__
