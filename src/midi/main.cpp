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
#include "chord.hpp"

ChordClass *chordConvert;

void readMessageWrapper( double deltatime, std::vector< unsigned char > *message, void *userData )
{
  chordConvert->readMessage( deltatime, message, userData );
}

int main()
{
  sf::RenderWindow window;
  RtMidiIn  *midiin = 0;
  std::vector<unsigned char> message;
  std::string input;

  try 
  {
    chordConvert = new ChordClass();
  }
  catch (std::exception& e)
  {
    std::cerr << "Error creating chord class" << e.what() << std::endl;
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
  unsigned int nPorts = midiin->getPortCount();

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
  
  midiin->openPort( 0 );

  // Don't ignore sysex, timing, or active sensing messages.
  midiin->ignoreTypes( false, false, false );

  // callback for midi messages
  midiin->setCallback( readMessageWrapper );

  window.create(sf::VideoMode(800, 600), "Notes");
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

    //window.draw(chordConvert->drawNotes());
    chordConvert->drawToWindow(&window);

    // draw everything here...
    //window.draw(...);

    // end the current frame
    window.display();
  }

  //std::cout << "Press enter to quit" << std::endl;
  //std::getline(std::cin, input);

 cleanExit:
  delete midiin;
  delete chordConvert;
  return 0;
}
