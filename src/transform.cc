#include "../include/transform.h"

// Custom implementation of bit rotate right
// @param: input: bitset to rotate
// @param: rotate_by: number of places to rotate by
BoardType Transform::bitRotateRight(BoardType input, int rotate_by){
    return (input >> rotate_by | input << (SIZE - rotate_by));
}

// Function that takes a board and returns a board that is rotated by 90 degrees ccw
// @param: board: input board to rotate
BoardType Transform::rotate90(BoardType board){
    // Initialise variables   
    BoardType rotated_board(0);
    BoardType current(0);
    BoardType mask(0);
   
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
BoardType Transform::reflectVertical(BoardType board){
    // Initialize variables   
    BoardType reflected_board(0);
    BoardType current(0);
    BoardType mask(0);
   
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
BoardType Transform::reflectBackSlash(BoardType board){
    // Initialize variables   
    BoardType reflected_board(0);
    BoardType current(0);
    BoardType mask(0);
   
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
BoardType Transform::rotate180(BoardType board){
    return rotate90(rotate90(board));
}

// Function that takes a board and returns a board that is rotated by 270 degrees ccw
// @param: board: input board to rotate
BoardType Transform::rotate270(BoardType board){
    return rotate180(rotate90(board));
}

// Function that takes a board and returns a board that is reflected about the forwardslash (\) axis
// @param: board: input board to reflect 
BoardType Transform::reflectForwardSlash(BoardType board){
    return reflectBackSlash(rotate180(board));
}

// Function that takes a board and returns a board that is reflected about the horizontal axis
// @param: board: input board to reflect 
BoardType Transform::reflectHorizontal(BoardType board){
    return reflectVertical(rotate180(board));
}

// Function that takes a board and returns a board that is inverse of reflection about the horizontal axis
// @param: board: input board to reflect 
BoardType Transform::invertReflectHorizontal(BoardType board){
    return reflectHorizontal(board);
}

// Function that takes a board and returns a board that is inverse of reflection about the vertical axis
// @param: board: input board to reflect 
BoardType Transform::invertReflectVertical(BoardType board){
    return reflectVertical(board);
}

// Function that takes a board and returns a board that is inverse of reflection about the backslash (/) axis
// @param: board: input board to reflect 
BoardType Transform::invertReflectBackSlash(BoardType board){
    return reflectBackSlash(board);
}

// Function that takes a board and returns a board that is inverse of reflection about the forwardslash (\) axis
// @param: board: input board to reflect 
BoardType Transform::invertReflectForwardSlash(BoardType board){
    return reflectForwardSlash(board);
}

// Function that takes a board and returns a board that is inverse of 90 degree rotation ccw
// @param: board: input board to reflect 
BoardType Transform::invertRotate90(BoardType board){
    return rotate270(board);
}

// Function that takes a board and returns a board that is inverse of 180 degree rotation ccw
// @param: board: input board to reflect 
BoardType Transform::invertRotate180(BoardType board){
    return rotate180(board);
}

// Function that takes a board and returns a board that is inverse of 2700 degree rotation ccw
// @param: board: input board to reflect 
BoardType Transform::invertRotate270(BoardType board){
    return rotate90(board);
}

// Function that takes the game board and applies a suitable transformation to it to call the hash table
// Returns a struct containing transformation applied, and the move chosen
// @param: board: game board
Transform::QueryResult Transform::makeMove(BoardType board){

    QueryResult query_result = QueryResult();

    

    return query_result;
}

// Temporary main function
int main(){   
    // Sample board
    BoardType board("011100001");
    Transform t = Transform();
    t.makeMove(board);
    return 0;
}
