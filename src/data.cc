#include "../include/data.h"

// Function that returns a board of a randomly selected move from the database entry
// @param: data_iter: iterator to required database entry (ie- board)
BoardType Data::choosePlace(DatabaseType::iterator data_iter){
 
    // Create a cdf from the number of beads for each place
    std::discrete_distribution<uint32_t> dist(data_iter->second.begin(), data_iter->second.end());
 
    // Choose a place from the cdf
    // returns index ie- 0 to 8
    uint32_t place = dist(*(this->gen));

    BoardType move("100000000");
    return (move >> place);
}

// Function that creates a database entry for the key
// @param: key for the current board
DatabaseType::iterator Data::createEntry(BoardKeyType key){
 
    // Create entry with all 0's
    MatchBoxType data_entry(SIZE, 0);

    // Calculate vacant positions available
    // TODO: Eliminate symmetry cases
    BoardType occupied = key;          // Stores lower 9 bits into occupied
    occupied |= (key/pow(2, SIZE));    // Bitwise or of next 9 bits from key into occupied

    // If bit not set, add beads for that position
    for (int i = 0; i < SIZE; ++i){
        if (!occupied[i])
            // TODO: Number of initial beads
            data_entry[SIZE - 1 - i] = 5;   // Bitset indexes R to L
    }

    std::pair<DatabaseType::iterator, bool> stored = database.insert(make_pair(key, data_entry));
    return stored.first;

}

// Function that takes the database key and returns the move
// @param: key: key for the current board 
BoardType Data::getMove(BoardKeyType key){
    
    DatabaseType::iterator data_iter;
    data_iter = database.find(key);

    // If board not in database, create
    if (data_iter == database.end())
        data_iter = createEntry(key);
    
    BoardType move;

    // create board with all occupied places as 1's
    BoardType occupied = key;
    occupied |= (key/pow(2,SIZE));

    // keep calling for moves until valid move is obtained
    do{
        move = choosePlace(data_iter);
    } while((move&occupied).any());
    
    return move;
}
