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

// Function that stores the database to a file
// !SPECIFY FILE
void Data::saveDatabase(){
    
    // Open filestream
    std::ofstream tf_stream("./data/database.txt");

    // First line is number of database entries
    tf_stream << this->database.size() << std::endl;
   
    DatabaseType::iterator iter;    // iterator for database

    for(iter = this->database.begin(); iter != this->database.end(); ++iter){
        tf_stream << iter->first << std::endl;              // Store key
        for(int i = 0; i < SIZE; ++i){
            tf_stream << (iter->second)[i] << std::endl;    // Store number of beads
        }
    }

    tf_stream.close();
}

// Function that reads the database from a file
// !SPECIFY FILE
void Data::readDatabase(){

    // Open filestream
    std::ifstream tf_stream("./data/database.txt");

    int no_entries = 0;
    BoardKeyType key;
    MatchBoxType match_box;
    uint32_t no_beads;
    
    tf_stream >> no_entries;                // Number of entries in database

    for(int i = 0; i < no_entries; ++i){
        match_box.clear();
        tf_stream >> key;                   // Key for entry
        for(int j = 0; j < SIZE; ++j){
            tf_stream >> no_beads;          // Store number of beads
            match_box.push_back(no_beads);
        }
 
        this->database.insert(make_pair(key, match_box));
    }
    tf_stream.close();
}

// Function that updates the number of beads for the game
// @param: key: key for database entry
// @param: move: move that was made (db layout)
// @param: result: result of game
// !HARDCODED BEAD CHANGES
void Data::updateEntry(BoardKeyType key, BoardType move, eWinCondition result){
    
    // Calculate change in beads
    int32_t change = 0;
    if (result == klose)
        change = -1;
    else if (result == kdraw)
        change = 1;
    else
        change = 3;

    // Calculate integer representation of move played
    u_int32_t position_index = log2(move.to_ulong());
    position_index = SIZE - 1 - position_index;         // Convert indexing to L to R
    
    // Update number of beads in the matchbox
    DatabaseType::iterator database_iter = database.find(key);
    (database_iter->second)[position_index] += change;

}