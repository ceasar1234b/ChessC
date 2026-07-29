#include <iostream>
#include <ostream>

#include "piece.h"

int main() {
    Chess::Board b;
    b.print();
    Chess::Piece p;
    p.type = Chess::PieceType::KNIGHT;
    p.color = Chess::PieceColor::WHITE;
    b.showMoves(p, 1, 0);

    return 0;
}
