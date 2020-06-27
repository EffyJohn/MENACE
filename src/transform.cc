#include "../include/transform.h"

// Implementation of bit rotate right
// !USES #DEFINED SIZE
// @param: input: bitset to rotate
// @param: rotate_by: number of places to rotate by
std::bitset<SIZE> rotateRight(std::bitset<SIZE> input, int rotate_by){
    return (input >> rotate_by | input << (SIZE - rotate_by));
}

// Function that takes a board and rotates it by 90 degrees ccw
// Returns a bitset of size = SIZE
std::bitset<SIZE> rotate_90(std::bitset<SIZE> board){
    // initialise variables   
    std::bitset<SIZE> rotated_board(0);
    std::bitset<SIZE> current(0);
    std::bitset<SIZE> mask(0);
   
    // encoder[i] = number of places to bitrotate i'th place on board
    int encoder[SIZE] = {2, 4, 6, 7, 0, 2, 3, 5, 7};

    for(int i = 0; i < SIZE; ++i){
        // mask to obtain i'th place on board
        mask.reset();
        mask.set(i);

        // obtain i'th place on board
        current = board&mask;

        // ! BOARD REPRESENATION IS 123456789, but bitset uses 987654231
        current = rotateRight(current, encoder[SIZE - i - 1]);
        rotated_board |= current;
    }
    
    return rotated_board;
}

// temporaary main function
int main(){
   
    // sample board
    std::bitset<SIZE> board("011100001");
    // rotate by 90 degreed ccw
    board = rotate_90(board);

    return 0;
}