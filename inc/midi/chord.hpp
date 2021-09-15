#ifndef __CHORD_HPP__
#define __CHORD_HPP__
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class ChordClass
{
  public:
    ChordClass();
    getChordName(std::vector<char> keys);
};

#endif // __CHORD_HPP__
