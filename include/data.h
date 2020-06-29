#ifndef DATA_H
#define DATA_H


#include <unordered_map>
#include <fstream>
#include <math.h>
#include <random>
#include <iostream>
#include "param.h"

typedef std::vector<uint32_t> MatchBoxType;
typedef std::unordered_map<BoardKeyType, MatchBoxType> DatabaseType;

class Data{
    public:

        Data(std::mt19937 *gen){
            this->gen = gen;
        }

        BoardType getMove(BoardKeyType key);
        void updateEntry(BoardKeyType key);         // TODO: Implement
        void saveDatabase();
        void readDatabase();

    private:

        std::mt19937 *gen;
        DatabaseType database;
        
        BoardType choosePlace(DatabaseType::iterator);
        DatabaseType::iterator createEntry(BoardKeyType key);
        
};


#endif