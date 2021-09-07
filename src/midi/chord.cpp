#include "chord.hpp"
#include <iostream>

ChordClass::ChordClass()
{
  for (size_t i = 0; i < sizeof(m_noteState)/sizeof(bool); i++)
  {
    m_noteState[i] = false;
  }
}

void ChordClass::printState()
{
  static const char note[][3] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};

  std::cout << "Notes down:" << std::endl;
  for (size_t i = 0; i < sizeof(m_noteState)/sizeof(bool); i++)
  {
    if (m_noteState[i])
    {
      int octave = (i / 12) - 1;
      int note_index = i % 12;
      std::cout << note[note_index] << octave << std::endl;
    }
  }
  std::cout << std::endl;
}

void ChordClass::print_note(std::vector<unsigned char> *message)
{
  static const char note[][3] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};
  int octave;
  int note_index; 

  if (message->size() != 3)
  {
    return;
  }

  // pitch should be 7 bits
  if ((*message)[1] > 127)
  {
    std::cout << "Unknown note" << std::endl;
    return;
  }

  if ((*message)[2])
    std::cout << "Start ";
  else
    std::cout << "Stop ";

  // Data byte 1 : 0PPP PPPP
  octave = ((*message)[1] / 12) - 1;
  note_index = (*message)[1] % 12;
  std::cout << note[note_index] << octave << std::endl;
}

void ChordClass::readMessage( double deltatime, std::vector< unsigned char > *message, void *userData )
{
  unsigned int nBytes = message->size();

  if ( (*message)[0] != 0x90)
  {
    return;
  }

  if ( nBytes > 3 )
  {
    std::cout << "unknown message" << std::endl;
    return;
  }

  setNoteState((*message)[1], (*message)[2]);
  //print_note(message);
  printState();
}

void ChordClass::setNoteState(unsigned char pitch, unsigned char velocity)
{
  // pitch should be 7 bits
  if (pitch > 127)
  {
    std::cout << "Unknown note" << std::endl;
    return;
  }

  if (velocity)
  {
    m_noteState[pitch] = true;
  }
  else
  {
    m_noteState[pitch] = false;
  }
}

void ChordClass::printChord()
{

}

void ChordClass::drawToWindow(sf::RenderWindow *window)
{
  drawClef(window);
  drawNotes(window);
}
#if 0
  sf::CircleShape currentNote(10.f);
  currentNote.setFillColor(sf::Color(0, 0, 0));

  sf::RectangleShape line(sf::Vector2f(150.f, 5.f));
  line.setFillColor(sf::Color(0, 0, 0));

  window->draw(line);
  window->draw(currentNote);
}
#endif

void ChordClass::drawClef(sf::RenderWindow *window)
{
  sf::Texture texture;
  if (!texture.loadFromFile("img/clef.png"))
  {
    std::cout << "Fail to load image" << std::endl;
    return;
  }

  sf::Sprite sprite(texture);
  window->draw(sprite);
}

void ChordClass::drawNotes(sf::RenderWindow *window)
{
  //static const char note[][3] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};
#define C_HEIGHT 7.6f
  static float yOffsets[] =     {C_HEIGHT, 0.f, C_HEIGHT, 0.f, C_HEIGHT, C_HEIGHT, 0.f, C_HEIGHT, 0.f, C_HEIGHT, 0.f, C_HEIGHT};
  sf::CircleShape currentNote(7.f);
  currentNote.setFillColor(sf::Color(0, 0, 0));

  // treble clef
  float y = 115.f;
  for (size_t i = 60; i < sizeof(m_noteState)/sizeof(bool); i++)
  {
    if (m_noteState[i])
    {
      // currentNote.setPosition(275.f, 115.f); // middle C
      // currentNote.setPosition(275.f, 45.f);  // E
      currentNote.setPosition(275.f, y); // middle C
      window->draw(currentNote);
    }

    y -= (yOffsets[(i - 60) % 12]);
  }

  // bass clef

}
