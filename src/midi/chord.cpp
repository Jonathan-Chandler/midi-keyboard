#include "chord.hpp"
#include <iostream>

const int16_t ChordClass::intervalBitmask[INTERVAL_TYPE_COUNT] = 
{
  (1 << MINOR_SECOND),          // 0x1
  (1 << MAJOR_SECOND),          // 0x2
  (1 << MINOR_THIRD),           // 0x4
  (1 << MAJOR_THIRD),           // 0x8
  (1 << PERFECT_FOURTH),        // 0x10
  (1 << AUGMENTED_FOURTH),      // 0x20
  (1 << PERFECT_FIFTH),         // 0x40
  (1 << MINOR_SIXTH),           // 0x80
  (1 << MAJOR_SIXTH),           // 0x100
  (1 << MINOR_SEVENTH),         // 0x200
  (1 << MAJOR_SEVENTH),         // 0x400
  0                             // 0x0 (octave)
};

const std::string ChordClass::intervalName[INTERVAL_TYPE_COUNT] = 
{
  "m2",
  "M2",
  "m3",
  "M3",
  "P4",
  "A4",
  "P5",
  "m6",
  "M6",
  "m7",
  "M7",
  "P8"
};

const std::string ChordClass::triadName[TRIAD_TYPE_COUNT] = 
{
  "Major",
  "Minor",
  "Aug",
  "Dim",
  "Major (1st)",
  "Minor (1st)",
  "Dim (1st)",
  "Major (2nd)",
  "Minor (2nd)",
  "Dim (2nd)",
};

const std::string ChordClass::sevenChordName[SEVEN_CHORD_TYPE_COUNT] = 
{
  "Major 7",
  "Minor 7",
  "Dominant 7",
//  "Dim",
//  "Major (1st)",
//  "Minor (1st)",
//  "Dim (1st)",
//  "Major (2nd)",
//  "Minor (2nd)",
//  "Dim (2nd)",
};

// major - 48/84/110 - root / 1st / 2nd -> ... / m6|m3 / M6|P4
// minor - 44/108/90 - root / 1st / 2nd -> ... / M6|M3 / m6|P4
// dim - 24/104/120 - root / 1st / 2nd -> ... / M6|m3 / M6|A4
// aug - 88
const int16_t ChordClass::triadBitmask[TRIAD_TYPE_COUNT] = 
{
  (int16_t)((intervalBitmask[MAJOR_THIRD]) | (intervalBitmask[PERFECT_FIFTH])),     // major root
  (int16_t)((intervalBitmask[MINOR_THIRD]) | (intervalBitmask[PERFECT_FIFTH])),     // minor root
  (int16_t)((intervalBitmask[MAJOR_THIRD]) | (intervalBitmask[MINOR_SIXTH])),       // aug
  (int16_t)((intervalBitmask[MINOR_THIRD]) | (intervalBitmask[AUGMENTED_FOURTH])),  // dim
  (int16_t)((intervalBitmask[MINOR_SIXTH]) | (intervalBitmask[MINOR_THIRD])),       // major ist inversion
  (int16_t)((intervalBitmask[MAJOR_SIXTH]) | (intervalBitmask[MAJOR_THIRD])),       // minor 1st inversion
  (int16_t)((intervalBitmask[MAJOR_SIXTH]) | (intervalBitmask[MINOR_THIRD])),       // dim 1st inversion
  (int16_t)((intervalBitmask[MAJOR_SIXTH]) | (intervalBitmask[PERFECT_FOURTH])),    // major 2nd inversion
  (int16_t)((intervalBitmask[MINOR_SIXTH]) | (intervalBitmask[PERFECT_FOURTH])),    // minor 2nd inversion
  (int16_t)((intervalBitmask[MAJOR_SIXTH]) | (intervalBitmask[AUGMENTED_FOURTH])),  // dim 2nd inversion
};

const int16_t ChordClass::sevenChordBitmask[SEVEN_CHORD_TYPE_COUNT] = 
{
  (int16_t)(triadBitmask[MAJOR] | intervalBitmask[MAJOR_SEVENTH]),                  // major7 root
  (int16_t)(triadBitmask[MINOR] | intervalBitmask[MINOR_SEVENTH]),                  // minor7 root
  (int16_t)(triadBitmask[MAJOR] | intervalBitmask[MINOR_SEVENTH]),                  // dominant7 root
  //(int16_t)((intervalBitmask[MAJOR_THIRD]) | (intervalBitmask[MINOR_SIXTH])),       // aug
  //(int16_t)((intervalBitmask[MINOR_THIRD]) | (intervalBitmask[AUGMENTED_FOURTH])),  // dim
  //(int16_t)((intervalBitmask[MINOR_SIXTH]) | (intervalBitmask[MINOR_THIRD])),       // major ist inversion
  //(int16_t)((intervalBitmask[MAJOR_SIXTH]) | (intervalBitmask[MAJOR_THIRD])),       // minor 1st inversion
  //(int16_t)((intervalBitmask[MAJOR_SIXTH]) | (intervalBitmask[MINOR_THIRD])),       // dim 1st inversion
  //(int16_t)((intervalBitmask[MAJOR_SIXTH]) | (intervalBitmask[PERFECT_FOURTH])),    // major 2nd inversion
  //(int16_t)((intervalBitmask[MINOR_SIXTH]) | (intervalBitmask[PERFECT_FOURTH])),    // minor 2nd inversion
  //(int16_t)((intervalBitmask[MAJOR_SIXTH]) | (intervalBitmask[AUGMENTED_FOURTH])),  // dim 2nd inversion
};

ChordClass::ChordClass()
{
}

void ChordClass::printChordName(std::string rootNote, int16_t chordBitmask)
{
  int16_t testBit = 1;
  int noteCount = 1;
  for (size_t i = 0; i < 16; i++)
  {
    if (chordBitmask & testBit)
      noteCount++;
    testBit <<= 1;
  }
  if (noteCount == 3)
  {
    printTriadName(rootNote, chordBitmask);
  }
  else if (noteCount == 4)
  {
    printSevenChordName(rootNote, chordBitmask);
  }
}

void ChordClass::printTriadName(std::string rootNote, int16_t chordBitmask)
{
  std::cout << "chordBitmask = 0x" << std::hex << std::uppercase << chordBitmask << std::nouppercase << std::dec << std::endl;

  for (size_t triadIndex = 0; triadIndex < TRIAD_TYPE_COUNT; triadIndex++)
  {
    if (chordBitmask == triadBitmask[triadIndex])
    {
      std::cout << "chord " << rootNote << " " << triadName[triadIndex] << std::endl;
      break;
    }
  }
}

void ChordClass::printSevenChordName(std::string rootNote, int16_t chordBitmask)
{
  std::cout << "chordBitmask = 0x" << std::hex << std::uppercase << chordBitmask << std::nouppercase << std::dec << std::endl;

  for (size_t sevenIndex = 0; sevenIndex < SEVEN_CHORD_TYPE_COUNT; sevenIndex++)
  {
    if (chordBitmask == sevenChordBitmask[sevenIndex])
    {
      std::cout << "chord " << rootNote << " " << sevenChordName[sevenIndex] << std::endl;
      break;
    }
  }
}

void ChordClass::printIntervalNames(int16_t chordBitmask)
{
  std::cout << "chordBitmask = 0x" << std::hex << std::uppercase << chordBitmask << std::nouppercase << std::dec << std::endl;

  for (size_t i = 0; i < INTERVAL_TYPE_COUNT; i++)
  {
    //if (intervalBitmask[i] & chordBitmask)
    if (chordBitmask == intervalBitmask[i])
    {
      std::cout << "interval: " << intervalName[i] << std::endl;
    }
  }
}

