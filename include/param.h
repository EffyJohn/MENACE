#ifndef PARAM_H
#define PARAM_H

#include <bitset>
#include <random>
#include <vector>

#define SIZE 9          // Size of game board 
#define TRAN_TOTAL 7    // Total nuber of transformations

typedef std::bitset<SIZE> BoardType;    // Datatype representing board
typedef uint32_t BoardKeyType;          // Datatype representing board key

// Enum encapsulating the result of the game
enum eWinCondition{
    klose = 0,
    kdraw = 1,
    kwin = 2
};

#endif