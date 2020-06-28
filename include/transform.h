#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <bitset>
#include <functional>
#include <iostream>
#define SIZE 9 
#define TRAN_TOTAL 7

typedef std::bitset<SIZE> BoardType;

class Transform{
    public:
        Transform(){

            transformation_map[kRotate90] = &Transform::rotate90;
            transformation_map[kRotate180] = &Transform::rotate180;
            transformation_map[kRotate270] = &Transform::rotate270;
            transformation_map[kReflectHorizontal] = &Transform::reflectHorizontal;
            transformation_map[kReflectVertical] = &Transform::reflectVertical;
            transformation_map[kReflectBackSlash] = &Transform::reflectBackSlash;
            transformation_map[kReflectForwardSlash] = &Transform::reflectForwardSlash;

            inverse_transformation_map[kRotate90] = &Transform::invertRotate90;
            inverse_transformation_map[kRotate180] = &Transform::invertRotate180;
            inverse_transformation_map[kRotate270] = &Transform::invertRotate270;
            inverse_transformation_map[kReflectHorizontal] = &Transform::invertReflectHorizontal;
            inverse_transformation_map[kReflectVertical] = &Transform::invertReflectVertical;
            inverse_transformation_map[kReflectBackSlash] = &Transform::invertReflectBackSlash;
            inverse_transformation_map[kReflectForwardSlash] = &Transform::invertReflectForwardSlash;
        }

        enum eTransformation {
            kRotate90 = 0,
            kRotate180,
            kRotate270,
            kReflectHorizontal,
            kReflectVertical,
            kReflectBackSlash,
            kReflectForwardSlash,
        };

        struct QueryResult{
            BoardType move;
            eTransformation transformation;
        };

        QueryResult makeMove(BoardType, BoardType);

    private: 

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
