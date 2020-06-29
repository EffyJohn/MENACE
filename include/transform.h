#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <bitset>
#include <functional>
#include <iostream>
#include <math.h>
#include <stdint.h>
#include "param.h"
#include "data.h"


// Tranform class, handles all interaction between game and hash table
class Transform{
    public:
        Transform(Data *database_ptr){
            // Initialise internal reference to database
            this->database_ptr = database_ptr; 
            
            // Initialise the transformation map w/ transformation function pointers
            transformation_map[kRotate90] = &Transform::rotate90;
            transformation_map[kRotate180] = &Transform::rotate180;
            transformation_map[kRotate270] = &Transform::rotate270;
            transformation_map[kReflectHorizontal] = &Transform::reflectHorizontal;
            transformation_map[kReflectVertical] = &Transform::reflectVertical;
            transformation_map[kReflectBackSlash] = &Transform::reflectBackSlash;
            transformation_map[kReflectForwardSlash] = &Transform::reflectForwardSlash;

            // Initialize the inverse transformation map w/ inverse transformation function pointers
            inverse_transformation_map[kRotate90] = &Transform::invertRotate90;
            inverse_transformation_map[kRotate180] = &Transform::invertRotate180;
            inverse_transformation_map[kRotate270] = &Transform::invertRotate270;
            inverse_transformation_map[kReflectHorizontal] = &Transform::invertReflectHorizontal;
            inverse_transformation_map[kReflectVertical] = &Transform::invertReflectVertical;
            inverse_transformation_map[kReflectBackSlash] = &Transform::invertReflectBackSlash;
            inverse_transformation_map[kReflectForwardSlash] = &Transform::invertReflectForwardSlash;
        }

        // enum for transformation ID's
        // Game class would communicate with transform class using these id's
        // TODO: Move to appropriate class
        enum eTransformation {
            kNoTransformation = -1,
            kRotate90 = 0,
            kRotate180 = 1,
            kRotate270 = 2,
            kReflectHorizontal = 3,
            kReflectVertical = 4,
            kReflectBackSlash = 5,
            kReflectForwardSlash = 6,
        };

        // Structure encapsulating the 'packet' that would be sent between game and transform class
        // A board for move chosen, and the transformation ID applied
        struct QueryResult{
            BoardType move;
            eTransformation transformation;
        };

        // Main callable function for transform class
        QueryResult makeMove(BoardType noughts, BoardType crosses);


    private: 
        Data *database_ptr;
        // Datatype encapsulating a pointer to member function
        typedef BoardType (Transform::*transformation_ptr)( BoardType);

        transformation_ptr transformation_map[TRAN_TOTAL];
        transformation_ptr inverse_transformation_map[TRAN_TOTAL];

        BoardType bitRotateRight(BoardType input, int rotate_by);

        BoardType rotate90(BoardType board);
        BoardType rotate180(BoardType board);
        BoardType rotate270(BoardType board);
        BoardType reflectHorizontal(BoardType board);
        BoardType reflectVertical(BoardType board);
        BoardType reflectBackSlash(BoardType board);
        BoardType reflectForwardSlash(BoardType board);

        BoardType invertRotate90(BoardType board);
        BoardType invertRotate180(BoardType board);
        BoardType invertRotate270(BoardType board);
        BoardType invertReflectHorizontal(BoardType board);
        BoardType invertReflectVertical(BoardType board);
        BoardType invertReflectBackSlash(BoardType board);
        BoardType invertReflectForwardSlash(BoardType board);


};

#endif
