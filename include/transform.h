#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <bitset>
#define SIZE 9 

std::bitset<SIZE> rotateRight(std::bitset<SIZE> input, int rotate_by);
std::bitset<SIZE> rotate_90(std::bitset<SIZE> board);

#endif