#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <bitset>
#include <functional>
#include <iostream>
#define SIZE 9 

typedef std::bitset<SIZE> BoardType;

class Transform{
    public:
        struct QueryResult{
            BoardType move;
            std::function<BoardType(BoardType)> transformation_ptr;
        };

        QueryResult makeMove(BoardType);

    private: 

        BoardType bitRotateRight(BoardType input, int rotate_by);

        BoardType rotate90(BoardType board);
        BoardType rotate180(BoardType board);
        BoardType rotate270(BoardType board);
        BoardType reflectVertical(BoardType board);
        BoardType reflectHorizontal(BoardType board);
        BoardType reflectForwardSlash(BoardType board);
        BoardType reflectBackSlash(BoardType board);

        BoardType invertRotate90(BoardType board);
        BoardType invertRotate180(BoardType board);
        BoardType invertRotate270(BoardType board);
        BoardType invertReflectVertical(BoardType board);
        BoardType invertReflectHorizontal(BoardType board);
        BoardType invertReflectForwardSlash(BoardType board);
        BoardType invertReflectBackSlash(BoardType board);

};

#endif
