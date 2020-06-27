#include "../include/transform.h"

// Custom implementation of bit rotate right
// @param: input: bitset to rotate
// @param: rotate_by: number of places to rotate by
std::bitset<SIZE> bitRotateRight(std::bitset<SIZE> input, int rotate_by){
    return (input >> rotate_by | input << (SIZE - rotate_by));
}


// Function that takes a board and returns a board that is rotated by 90 degrees ccw
// @param: board: input board to rotate
std::bitset<SIZE> rotate90(std::bitset<SIZE> board){
    // Initialise variables   
    std::bitset<SIZE> rotated_board(0);
    std::bitset<SIZE> current(0);
    std::bitset<SIZE> mask(0);
   
    // Encoder[i] = number of places to bitrotate i'th place on board
    int encoder[SIZE] = {2, 4, 6, 7, 0, 2, 3, 5, 7};

    for (int i = 0; i < SIZE; ++i){
        // Mask to obtain i'th place on board
        mask.reset();
        mask.set(i);

        // Obtain i'th place on board
        current = board&mask;

        // ! Board representation is 123456789, but bitset uses 987654231
        current = bitRotateRight(current, encoder[SIZE - i - 1]);
        rotated_board |= current;
    }
    return rotated_board;
}

// Function that takes a board and returns a board that is reflected about the vertical axis
// @param: board: input board to reflect 
std::bitset<SIZE> reflectVertical(std::bitset<SIZE> board){
    // Initialize variables   
    std::bitset<SIZE> reflected_board(0);
    std::bitset<SIZE> current(0);
    std::bitset<SIZE> mask(0);
   
    // Encoder[i] = number of places to bitrotate i'th place on board
    int encoder[SIZE] = {2, 0, 7, 2, 0, 7, 2, 0, 7};

    for (int i = 0; i < SIZE; ++i){
        // Mask to obtain i'th place on board
        mask.reset();
        mask.set(i);

        // Obtain i'th place on board
        current = board&mask;

        // ! Board representation is 123456789, but bitset uses 987654231
        current = bitRotateRight(current, encoder[SIZE - i - 1]);
        reflected_board |= current;
    }
    return reflected_board;
}

// Function that takes a board and returns a board that is reflected about the backslash (/) axis
// @param: board: input board to reflect 
std::bitset<SIZE> reflectBackSlash(std::bitset<SIZE> board){
    // Initialize variables   
    std::bitset<SIZE> reflected_board(0);
    std::bitset<SIZE> current(0);
    std::bitset<SIZE> mask(0);
   
    // Encoder[i] = number of places to bitrotate i'th place on board
    int encoder[SIZE] = {8, 4, 0, 4, 0, 5, 0, 5, 1};

    for (int i = 0; i < SIZE; ++i){
        // Mask to obtain i'th place on board
        mask.reset();
        mask.set(i);

        // Obtain i'th place on board
        current = board&mask;

        // ! Board representation is 123456789, but bitset uses 987654231
        current = bitRotateRight(current, encoder[SIZE - i - 1]);
        reflected_board |= current;
    }
    return reflected_board;
}

// Function that takes a board and returns a board that is rotated by 180 degrees ccw
// @param: board: input board to rotate
std::bitset<SIZE> rotate180(std::bitset<SIZE> board){
    return rotate90(rotate90(board));
}

// Function that takes a board and returns a board that is rotated by 270 degrees ccw
// @param: board: input board to rotate
std::bitset<SIZE> rotate270(std::bitset<SIZE> board){
    return rotate180(rotate90(board));
}

// Function that takes a board and returns a board that is reflected about the forwardslash (\) axis
// @param: board: input board to reflect 
std::bitset<SIZE> reflectForwardSlash(std::bitset<SIZE> board){
    return reflectBackSlash(rotate180(board));
}

// Function that takes a board and returns a board that is reflected about the horizontal axis
// @param: board: input board to reflect 
std::bitset<SIZE> reflectHorizontal(std::bitset<SIZE> board){
    return reflectVertical(rotate180(board));
}


// Temporary main function
int main(){   
    // Sample board
    std::bitset<SIZE> board("011100001");
    return 0;
}