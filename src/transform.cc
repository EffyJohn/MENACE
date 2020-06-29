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

// Function that applies a suitable transformation to the game state to call the hash table
// Returns a struct containing transformation applied, and the move chosen
// @param: noughts: game board for noughts
// @param: crosses: game board for crosses
Transform::QueryResult Transform::makeMove(BoardType noughts, BoardType crosses){

    QueryResult query_result = QueryResult();   // return packet
    
    BoardKeyType minimum_id = -1;               // minimum id of all resulting boards
    BoardKeyType current_id = 0;                // current id of board
    BoardType current_board(0);             // board for iteration purposes

    // checking original state board
    // shift 9 bits for creation of ID w/o transformation
    current_board = noughts;
    current_id += current_board.to_ulong();
    current_id *= std::pow(2, SIZE);
    

    // create ID w/o transformation
    current_board = crosses;
    current_id += current_board.to_ulong();
    
    if (current_id < minimum_id){
        minimum_id = current_id;
        query_result.transformation = (eTransformation)(-1);
    }

    // apply transformations to bring to standard state
    for (int i = 0; i < TRAN_TOTAL; ++i){
        current_id = 0;
        current_board.reset();

        // apply transformation to noughts and shift 9 bits for creation of ID
        current_board = (this->*(transformation_map[i]))(noughts);
        current_id += current_board.to_ulong();
        current_id *= std::pow(2, SIZE);
    
        // apply transformation to crosses and create ID
        current_board = (this->*(transformation_map[i]))(crosses);
        current_id += current_board.to_ulong();
        
        if (current_id < minimum_id){
            minimum_id = current_id;
            query_result.transformation = (eTransformation)i;
        }
    }
    
    // query hash table to get move
    query_result.move = this->database_ptr->getMove(minimum_id);
    query_result.move = (this->*(inverse_transformation_map[query_result.transformation]))(query_result.move);
    return query_result;
}


