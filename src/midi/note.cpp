#include "note.hpp"
#include <iostream>
#define C_HEIGHT 7.6f

NoteClass::NoteClass()
  : m_noteCount(0),
    m_lowestNote(-1)
{
  // C B A# A B# G# G F# F E D# D C# 
  static float yOffsetsTreble[] = {C_HEIGHT, 0.f, C_HEIGHT, 0.f, C_HEIGHT, C_HEIGHT, 0.f, C_HEIGHT, 0.f, C_HEIGHT, 0.f, C_HEIGHT};
  // B A# A B# G# G F# F E D# D C# C
  static float yOffsetsBass[] = {C_HEIGHT, 0.f, C_HEIGHT, 0.f, C_HEIGHT, C_HEIGHT, 0.f, C_HEIGHT, 0.f, C_HEIGHT, 0.f, C_HEIGHT};

  for (size_t i = 0; i < sizeof(m_noteState)/sizeof(bool); i++)
  {
    m_noteState[i] = false;
  }

  // set y locations for treble clef
  float y = 122.6f;
  for (size_t i = 60; i < sizeof(m_noteState)/sizeof(bool); i++)
  {
    y -= (yOffsetsTreble[(i - 60) % 12]);
    m_noteY[i] = y;
  }

  // set y locations for bass clef
  y = 168.f;
  for (size_t i = 60; i != 0; i--)
  {
    y += (yOffsetsBass[i % 12]);
    m_noteY[i-1] = y;
  }
}

void NoteClass::printState()
{
  static const char note[][3] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};

  std::cout << m_noteCount << " notes down: " << std::endl;
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

void NoteClass::printNote(std::vector<unsigned char> *message)
{
  static const char noteArray[][3] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};
  int octave;
  int noteIndex; 

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
  noteIndex = (*message)[1] % 12;
  std::cout << noteArray[noteIndex] << octave << std::endl;
}

void NoteClass::readMessage( double deltatime, std::vector< unsigned char > *message, void *userData )
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
  //printNote(message);
  printState();
}

void NoteClass::setNoteState(unsigned char pitch, unsigned char velocity)
{
  // pitch should be 7 bits
  if (pitch > 127)
  {
    std::cout << "Unknown note" << std::endl;
    return;
  }

  if (velocity)
  {
    if (!m_noteState[pitch])
      ++m_noteCount;

    m_noteState[pitch] = true;
  }
  else
  {
    if (m_noteState[pitch])
      --m_noteCount;

    m_noteState[pitch] = false;
  }
}

void NoteClass::drawToWindow(sf::RenderWindow *window)
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

void NoteClass::drawClef(sf::RenderWindow *window)
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

void NoteClass::drawNotes(sf::RenderWindow *window)
{
  sf::CircleShape currentNote(7.f);
  currentNote.setFillColor(sf::Color(0, 0, 0));

  // treble clef
  for (size_t i = 0; i < sizeof(m_noteState)/sizeof(bool); i++)
  {
    if (m_noteState[i])
    {
      // currentNote.setPosition(275.f, 115.f); // middle C
      // currentNote.setPosition(275.f, 45.f);  // E
      currentNote.setPosition(275.f, m_noteY[i]); // middle C
      window->draw(currentNote);
    }
  }

  // bass clef
}

std::string NoteClass::getNoteName(char note)
{
  static const char noteArray[][3] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};
  int note_index; 

  note_index = note % 12;

  return std::string(noteArray[note_index]);
}

std::vector<std::string> NoteClass::getNoteNameVector()
{
  std::vector<std::string> noteNames;

  for (size_t i = 0; i < sizeof(m_noteState)/sizeof(bool); i++)
  {
    if (m_noteState[i])
    {
      noteNames.push_back(getNoteName(i));
    }
  }

  return noteNames;
}

