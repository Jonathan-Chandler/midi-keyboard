// midiprobe.cpp
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <windows.h>
#include <iostream>
#include <cstdlib>
#include <signal.h>
#define __WINDOWS_MM__
#include "RtMidi.h"
#include <chrono>
#include <thread>
#include "note.hpp"

NoteClass *noteConvert;

void readMessageWrapper( double deltatime, std::vector< unsigned char > *message, void *userData )
{
  noteConvert->readMessage( deltatime, message, userData );
}

int main()
{
  sf::RenderWindow window;
  RtMidiIn  *midiin = 0;
  std::vector<unsigned char> message;
  std::string input;

  try 
  {
    noteConvert = new NoteClass();
  }
  catch (std::exception& e)
  {
    std::cerr << "Error creating note class" << e.what() << std::endl;
    return 0;
    exit( EXIT_FAILURE );
  }

  // RtMidiIn constructor
  try 
  {
    midiin = new RtMidiIn(RtMidi::Api::WINDOWS_MM);
  }
  catch ( RtMidiError &error ) {
    error.printMessage();
    exit( EXIT_FAILURE );
  }

  // Check inputs.
  unsigned int nPorts;
  nPorts = midiin->getPortCount();
  if (nPorts == 0)
  {
    return 0;
  }

  std::cout << "\nThere are " << nPorts << " MIDI input sources available.\n";
  std::string portName;
  for ( unsigned int i=0; i<nPorts; i++ ) {
    try {
      portName = midiin->getPortName(i);
    }
    catch ( RtMidiError &error ) {
      error.printMessage();
      goto cleanExit;
    }
    std::cout << "  Input Port #" << i+1 << ": " << portName << '\n';
  }
  
  try 
  {
    midiin->openPort( 0 );
  }
  catch ( RtMidiError &error ) {
    error.printMessage();
    goto cleanExit;
  }

  // Don't ignore sysex, timing, or active sensing messages.
  midiin->ignoreTypes( false, false, false );

  // callback for midi messages
  midiin->setCallback( readMessageWrapper );

  // create display
  try 
  {
    window.create(sf::VideoMode(800, 600), "Notes");
  }
  catch (std::exception& e)
  {
    std::cerr << "Error creating window" << e.what() << std::endl;
    return 0;
    exit( EXIT_FAILURE );
  }

  while (window.isOpen())
  {
    // check all the window's events that were triggered since the last iteration of the loop
    sf::Event event;
    while (window.pollEvent(event))
    {
      // close with escape
      if (event.type == sf::Event::KeyPressed)
      {
        if (event.key.code == sf::Keyboard::Escape)
          window.close();
      }

      // "close requested" event: we close the window
      if (event.type == sf::Event::Closed)
        window.close();
    }

    // clear the window with black color
    window.clear(sf::Color::White);

    //window.draw(noteConvert->drawNotes());
    noteConvert->drawToWindow(&window);

    // end the current frame
    window.display();
  }

 cleanExit:
  delete midiin;
  delete noteConvert;
  return 0;
}
