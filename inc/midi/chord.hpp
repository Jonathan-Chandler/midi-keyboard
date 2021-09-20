#ifndef __CHORD_HPP__
#define __CHORD_HPP__
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class ChordClass
{
  private:
  enum intervals
  {
    MINOR_SECOND,                           //  1 semitone
    MAJOR_SECOND,                           //  2 semitones
    MINOR_THIRD,                            //  3 semitones
    MAJOR_THIRD,                            //  4 semitones
    PERFECT_FOURTH,                         //  5 semitones
    AUGMENTED_FOURTH,                       //  6 semitones
    DIMINISHED_FIFTH = AUGMENTED_FOURTH,    //  6 semitones
    PERFECT_FIFTH,                          //  7 semitones
    AUGMENTED_FIFTH,                        //  8 semitones
    MINOR_SIXTH = AUGMENTED_FIFTH,          //  8 semitones
    MAJOR_SIXTH,                            //  9 semitones
    MINOR_SEVENTH,                          // 10 semitones
    MAJOR_SEVENTH,                          // 11 semitones
    PERFECT_OCTAVE,                         // 12 semitones
    INTERVAL_TYPE_COUNT
  };

  enum shorthand
  {
    m2 = MINOR_SECOND,
    M2 = MAJOR_SECOND,
    m3 = MINOR_THIRD,
    M3 = MAJOR_THIRD,
    P4 = PERFECT_FOURTH,
    A4 = AUGMENTED_FOURTH,
    d5 = DIMINISHED_FIFTH,
    P5 = PERFECT_FIFTH,
    A5 = MINOR_SIXTH,
    m6 = MINOR_SIXTH,
    M6 = MAJOR_SIXTH,
    m7 = MINOR_SEVENTH,
    M7 = MAJOR_SEVENTH,
    P8 = PERFECT_OCTAVE,
  };

  // inversions
  //    perfect -> perfect
  //    major -> minor
  //    aug -> dim

  //    second -> seventh
  //    third -> sixth
  //    fourth -> fifth
  enum triads
  {
    ROOT_POSITION,
    MAJOR = ROOT_POSITION,
    MINOR,
    AUGMENTED,
    DIMINISHED,

    FIRST_INVERSION,
    MAJOR_1 = FIRST_INVERSION,
    MINOR_1,
    DIMINISHED_1,

    SECOND_INVERSION,
    MAJOR_2 = SECOND_INVERSION,
    MINOR_2,
    DIMINISHED_2,
    TRIAD_TYPE_COUNT
  };

  enum sevenChords
  {
    ROOT_7_POSITION,
    MAJOR_7 = ROOT_7_POSITION,
    MINOR_7,
    DOMINANT_7,
//    AUGMENTED_7,
//    DIMINISHED_7,
//
//    FIRST_INVERSION,
//    MAJOR_1_7 = FIRST_INVERSION,
//    MINOR_1_7,
//    DIMINISHED_1_7,
//
//    SECOND_INVERSION,
//    MAJOR_2_7 = SECOND_INVERSION,
//    MINOR_2_7,
//    DIMINISHED_2_7,
    SEVEN_CHORD_TYPE_COUNT
  };

  static const std::string intervalName[INTERVAL_TYPE_COUNT];
  static const std::string triadName[TRIAD_TYPE_COUNT];
  static const std::string sevenChordName[SEVEN_CHORD_TYPE_COUNT];
  static const int16_t intervalBitmask[];
  static const int16_t triadBitmask[];
  static const int16_t sevenChordBitmask[SEVEN_CHORD_TYPE_COUNT];

  public:
    ChordClass();

    //getChordName(std::vector<char> keys);
    void printChordName(std::string rootNote, int16_t chordBitmask);
    void printTriadName(std::string rootNote, int16_t chordBitmask);
    void printSevenChordName(std::string rootNote, int16_t chordBitmask);
    
    //void printChordName(std::vector<std::string> notes, int16_t chordBitmask)
    void printIntervalNames(int16_t chordBitmask);
};

#endif // __CHORD_HPP__
