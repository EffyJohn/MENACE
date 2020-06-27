#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <bitset>
#include <iostream>
#define SIZE 9 

std::bitset<SIZE> bitRotateRight(std::bitset<SIZE> input, int rotate_by);
std::bitset<SIZE> rotate90(std::bitset<SIZE> board);
std::bitset<SIZE> reflectVertical(std::bitset<SIZE> board);
std::bitset<SIZE> reflectBackSlash(std::bitset<SIZE> board);

#endif