// midiprobe.cpp
#include <windows.h>
#include <iostream>
#include <cstdlib>
#include <signal.h>
#define __WINDOWS_MM__
#include "RtMidi.h"
#include <chrono>
#include <thread>
#include "chord.hpp"


// SLEEP milliseconds
#define SLEEP(x) std::this_thread::sleep_for(std::chrono::milliseconds(x))

bool done;
static void finish(int ignore){done=true;}

int main()
{
  ChordClass chordConvert;
  RtMidiIn  *midiin = 0;
  std::vector<unsigned char> message;
  int nBytes;
//  int i;
//  double stamp;

  // RtMidiIn constructor
  try {
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
      goto cleanup;
    }
    std::cout << "  Input Port #" << i+1 << ": " << portName << '\n';
  }
  
  midiin->openPort( 0 );

  // Don't ignore sysex, timing, or active sensing messages.
  midiin->ignoreTypes( false, false, false );
  // Install an interrupt handler function.
  done = false;
  (void) signal(SIGINT, finish);
  // Periodically check input queue.
  std::cout << "Reading MIDI from port ... quit with Ctrl-C.\n";
  while ( !done ) 
  {
    midiin->getMessage( &message );
    //stamp = midiin->getMessage( &message );
    nBytes = message.size();

    if (nBytes > 1)
    {
      chordConvert.print_note(message);
      //for ( i=0; i<nBytes; i++ )
      //{
      //  std::cout << "Byte " << i << " = " << std::hex << std::uppercase << (int)message[i] << ", ";
      //}
      //std::cout << "stamp = " << stamp << std::endl;
    }

    // Sleep for 10 milliseconds ... platform-dependent.
    //SLEEP( 10 );
    Sleep(10);
    //std::cout << "test" << std::endl;
  }

 cleanup:
  delete midiin;
  return 0;
}

#if 0
  RtMidiOut *midiout = 0;
  // RtMidiOut constructor
  try {
    midiout = new RtMidiOut();
  }
  catch ( RtMidiError &error ) {
    error.printMessage();
    exit( EXIT_FAILURE );
  }
  // Check outputs.
  nPorts = midiout->getPortCount();
  std::cout << "\nThere are " << nPorts << " MIDI output ports available.\n";
  for ( unsigned int i=0; i<nPorts; i++ ) {
    try {
      portName = midiout->getPortName(i);
    }
    catch (RtMidiError &error) {
      error.printMessage();
      goto cleanup;
    }
    std::cout << "  Output Port #" << i+1 << ": " << portName << '\n';
  }
  std::cout << '\n';
  // Clean up
  delete midiout;
#endif
