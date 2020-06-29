#include "../include/transform.h"
#include "../include/data.h"
#include "../include/param.h"


int main(){   
    // Sample board
    BoardType noughts("011100001");
    BoardType crosses("100000100");
    std::random_device rd;
    std::mt19937 gen(rd());
    Data d = Data(&gen);
    d.readDatabase();
    Transform t = Transform(&d);
    Transform::QueryResult q = t.makeMove(noughts, crosses);
    std::cout << q.move << std::endl;
    t.updateEntry(q.move, q.transformation, noughts, crosses, kwin);
    d.saveDatabase();
    return 0;
}
