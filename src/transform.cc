#include "../include/transform.h"

// Custom implementation of bit rotate right
// !USES #DEFINED SIZE
// @param: input: bitset to rotate
// @param: rotate_by: number of places to rotate by
std::bitset<SIZE> rotateRight(std::bitset<SIZE> input, int rotate_by){
    return (input >> rotate_by | input << (SIZE - rotate_by));
}

// Function that takes a board and rotates it by 90 degrees ccw
// !USES #DEFINED SIZE
// @param: board: input board to rotate
std::bitset<SIZE> rotate_90(std::bitset<SIZE> board){
    // Initialise variables   
    std::bitset<SIZE> rotated_board(0);
    std::bitset<SIZE> current(0);
    std::bitset<SIZE> mask(0);
   
    // Encoder[i] = number of places to bitrotate i'th place on board
    int encoder[SIZE] = {2, 4, 6, 7, 0, 2, 3, 5, 7};

    for(int i = 0; i < SIZE; ++i){
        // Mask to obtain i'th place on board
        mask.reset();
        mask.set(i);

        // Obtain i'th place on board
        current = board&mask;

        // ! Board representation is 123456789, but bitset uses 987654231
        current = rotateRight(current, encoder[SIZE - i - 1]);
        rotated_board |= current;
    }
    
    return rotated_board;
}

// Temporary main function
int main(){
   
    // Sample board
    std::bitset<SIZE> board("011100001");
    // Rotate by 90 degrees ccw
    board = rotate_90(board);

    return 0;
}