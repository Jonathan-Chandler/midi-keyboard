#ifndef __CHORD_HPP__
#define __CHORD_HPP__
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

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
    ChordClass();
    void readMessage( double deltatime, std::vector< unsigned char > *message, void *userData );
    void setNoteState(unsigned char pitch, unsigned char velocity);

    void drawToWindow(sf::RenderWindow *window);

    void print_note(std::vector<unsigned char> *message);
    void printState();
    void printChord();

  private:
    bool m_noteState[128];
    void drawNotes(sf::RenderWindow *window);
    void drawClef(sf::RenderWindow *window);
};

#endif // __CHORD_HPP__
