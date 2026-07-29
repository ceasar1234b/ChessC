//
// Created by hanne on 7/28/2026.
//

#include "piece.h"

using namespace Chess;

namespace {
    constexpr int sign(const int x) {
        return x > 0 ? 1 : -1;
    }
    constexpr char getRepresentation(PieceType type) noexcept {
        switch (type) {
        case PieceType::PAWN:
            return 'P';
        case PieceType::KNIGHT:
            return 'N';
        case PieceType::BISHOP:
            return 'B';
        case PieceType::ROOK:
            return 'R';
        case PieceType::QUEEN:
            return 'Q';
        case PieceType::KING:
            return 'K';
        default:
            return ' ';
        }
    }
}



void Board::print() const noexcept{
    for (int i = 7; i != -1; i--) {
        for (int j = 0; j < 8; j++) {
            std::cout << "| " << getRepresentation(board[i][j].type) << " ";
        }
        std::cout << "|" << std::endl;
        for (int j = 0; j < 8; j++) {
            std::cout << "+---";
        }
        std::cout << '+' << std::endl;
    }
}

Board::Board() noexcept {
    createPiece(Piece(PieceType::PAWN, PieceColor::WHITE), 0, 1);
    createPiece(Piece(PieceType::PAWN, PieceColor::WHITE), 1, 1);
    createPiece(Piece(PieceType::PAWN, PieceColor::WHITE), 2, 1);
    createPiece(Piece(PieceType::PAWN, PieceColor::WHITE), 3, 1);
    createPiece(Piece(PieceType::PAWN, PieceColor::WHITE), 4, 1);
    createPiece(Piece(PieceType::PAWN, PieceColor::WHITE), 5, 1);
    createPiece(Piece(PieceType::PAWN, PieceColor::WHITE), 6, 1);
    createPiece(Piece(PieceType::PAWN, PieceColor::WHITE), 7, 1);

    createPiece(Piece(PieceType::ROOK, PieceColor::WHITE), 0, 0);
    createPiece(Piece(PieceType::KNIGHT, PieceColor::WHITE), 1, 0);
    createPiece(Piece(PieceType::BISHOP, PieceColor::WHITE), 2, 0);
    createPiece(Piece(PieceType::QUEEN, PieceColor::WHITE), 3, 0);
    createPiece(Piece(PieceType::KING, PieceColor::WHITE), 4, 0);
    createPiece(Piece(PieceType::BISHOP, PieceColor::WHITE), 5, 0);
    createPiece(Piece(PieceType::KNIGHT, PieceColor::WHITE), 6, 0);
    createPiece(Piece(PieceType::ROOK, PieceColor::WHITE), 7, 0);

    createPiece(Piece(PieceType::PAWN, PieceColor::BLACK), 0, 6);
    createPiece(Piece(PieceType::PAWN, PieceColor::BLACK), 1, 6);
    createPiece(Piece(PieceType::PAWN, PieceColor::BLACK), 2, 6);
    createPiece(Piece(PieceType::PAWN, PieceColor::BLACK), 3, 6);
    createPiece(Piece(PieceType::PAWN, PieceColor::BLACK), 4, 6);
    createPiece(Piece(PieceType::PAWN, PieceColor::BLACK), 5, 6);
    createPiece(Piece(PieceType::PAWN, PieceColor::BLACK), 6, 6);
    createPiece(Piece(PieceType::PAWN, PieceColor::BLACK), 7, 6);

    createPiece(Piece(PieceType::ROOK, PieceColor::BLACK), 0, 7);
    createPiece(Piece(PieceType::KNIGHT, PieceColor::BLACK), 1, 7);
    createPiece(Piece(PieceType::BISHOP, PieceColor::BLACK), 2, 7);
    createPiece(Piece(PieceType::QUEEN, PieceColor::BLACK), 3, 7);
    createPiece(Piece(PieceType::KING, PieceColor::BLACK), 4, 7);
    createPiece(Piece(PieceType::BISHOP, PieceColor::BLACK), 5, 7);
    createPiece(Piece(PieceType::KNIGHT, PieceColor::BLACK), 6, 7);
    createPiece(Piece(PieceType::ROOK, PieceColor::BLACK), 7, 7);

    kingPositions[static_cast<int>(PieceColor::BLACK)].x = 4;
    kingPositions[static_cast<int>(PieceColor::BLACK)].y = 7;

    kingPositions[static_cast<int>(PieceColor::WHITE)].x = 4;
    kingPositions[static_cast<int>(PieceColor::WHITE)].y = 0;
}

// it is assumed that the coordinates are valid
bool Board::CheckMoveRook(const move &m) const noexcept {
    const int dx = m.toX - m.fromX;
    const int dy = m.toY - m.fromY;

    if ((dx != 0 && dy != 0)
        || (board[m.toY][m.toX].type != PieceType::NO_TYPE && board[m.toY][m.toX].color == m.color)) {
        return false;
    }

    if (dx) {
        for (int i = m.fromX + sign(dx); i != m.toX; i += sign(dx)) {
            if (board[m.fromY][i].type != PieceType::NO_TYPE) {
                return false;
            }
        }
    } else {
        for (int i = m.fromY + sign(dy); i != m.toY; i += sign(dy)) {
            if (board[i][m.fromX].type != PieceType::NO_TYPE) {
                return false;
            }
        }
    }

    return true;
};
bool Board::CheckMoveKnight (const move &m) const noexcept{
    const int dx = m.toX - m.fromX;
    const int dy = m.toY - m.fromY;

    if (!((std::abs(dx) == 1 && std::abs(dy) != 2)
        || (std::abs(dx) == 2 && std::abs(dy) != 1))
        || (board[m.toY][m.toX].type != PieceType::NO_TYPE && board[m.toY][m.toX].color == m.color)) {
        return false;
    }

    return true;
};
bool Board::CheckMoveBishop (const move &m) const noexcept {
    const int dx = m.toX - m.fromX;
    const int dy = m.toY - m.fromY;

    if (std::abs(dx) != std::abs(dy)
        || (board[m.toY][m.toX].type != PieceType::NO_TYPE && board[m.toY][m.toX].color == m.color)) {
        return false;
    }

    for (int i = 1; i != std::abs(dx); i++) {
        if (board[m.fromY + i * sign(dy)][m.fromY + i * sign(dx)].type != PieceType::NO_TYPE) {
            return false;
        }
    }

    return true;
};
bool Board::CheckMoveQueen (const move & m) const noexcept {
    return CheckMoveBishop(m) || CheckMoveRook(m);
};
bool Board::CheckMoveKing (const move &m)const noexcept {
    const int dx = m.toX - m.fromX;
    const int dy = m.toY - m.fromY;

    if (std::abs(dx) > 1
        || std::abs(dy) > 1
        || (board[m.toY][m.toX].type != PieceType::NO_TYPE && board[m.toY][m.toX].color == m.color)) {
        return false;
    }

    return true;
};
bool Board::CheckMovePawn (const move &m) const noexcept {
    const int dx = m.toX - m.fromX;
    const int dy = m.toY - m.fromY;

    if (std::abs(dx) > 1
        || std::abs(dy) > 2
        || (board[m.toY][m.toX].type != PieceType::NO_TYPE && board[m.toY][m.toX].color == m.color)
        || std::abs(dx) == 2 && std::abs(dy) == 1) {
        return false;
    }

    if (std::abs(dy) == 2) {
        if (board[m.toY][m.toX].type != PieceType::NO_TYPE
            || board[m.toY + sign(dy)][m.toX].color == m.color) {
            return false;
        }
    } else if (dx == 0) {
        if (board[m.toY][m.toX].type != PieceType::NO_TYPE) {
            return false;
        }
    }

    return true;
};

constexpr bool Board::createPiece(Piece piece, int x, int y) noexcept {
    if (x < 0
        || y < 0
        || x > 7
        || y > 7) {
        return false;
    }

    board[y][x] = piece;
    return true;
}

bool Board::CheckMove(const move &m) const noexcept {
    switch (m.type) {
        case PieceType::NO_TYPE:
            return false;
        case PieceType::KING:
            return CheckMoveKing(m);
        case PieceType::QUEEN:
            return CheckMoveQueen(m);
        case PieceType::ROOK:
            return CheckMoveRook(m);
        case PieceType::BISHOP:
            return CheckMoveBishop(m);
        case PieceType::KNIGHT:
            return CheckMoveKnight(m);
        case PieceType::PAWN:
            return CheckMovePawn(m);
        default:
            return false;
    }
}
constexpr void Board::pushMove(const move &m) const noexcept { moveBuffer[pos++] = m; }

void Board::getMovesRook(int x, int y, PieceColor c) const noexcept{
    constexpr std::array<std::pair<int, int>, 4> directions = {
        {
            {1, 0},
            {-1, 0},
            {0, 1},
            {0, -1}
        }
    };

    move m = {
        .fromX = x,
        .fromY = y,
        .color = c
    };

    for (int i = x + 1; i <= 7; i++) {
        m.toX = i;
        m.toY = y;
        if (board[y][i].type == PieceType::NO_TYPE) {
            pushMove(m);
        } else if (board[y][i].color != c) {
            pushMove(m);
            break;
        } else {
            break;
        }
    }
    for (int i = x - 1; i >= 0; i--) {
        m.toX = i;
        m.toY = y;
        if (board[y][i].type == PieceType::NO_TYPE) {
            pushMove(m);
        } else if (board[y][i].color != c) {
            pushMove(m);
            break;
        } else {
            break;
        }
    }

    for (int i = y + 1; i <= 7; i++) {
        m.toX = x;
        m.toY = i;
        if (board[i][x].type == PieceType::NO_TYPE) {
            pushMove(m);
        } else if (board[i][x].color != c) {
            pushMove(m);
            break;
        } else {
            break;
        }
    }
    for (int i = y - 1; i >= 0; i--) {
        m.toX = x;
        m.toY = i;
        if (board[i][x].type == PieceType::NO_TYPE) {
            pushMove(m);
        } else if (board[i][x].color != c) {
            pushMove(m);
            break;
        } else {
            break;
        }
    }
}

void Board::getMovesKnight(int x, int y, PieceColor c) const noexcept{
    constexpr std::array<std::pair<int, int>, 8> directions = {
        {
            {1, 2},{1, -2},
            {-1, -2},{-1, 2},
            {2, 1},{2, -1},
            {-2, 1},{-2, -1}
        }
    };

    move m = {
        .fromX = x,
        .fromY = y,
        .color = c
    };

    for (auto [dx, dy] : directions) {
        m.toX = x + dx;
        m.toY = y + dy;
        if ((m.toX) >= 0
            && (m.toX) <= 7
            && (m.toY) >= 0
            && (m.toY) <= 7
            && (board[m.toY][m.toX].type == PieceType::NO_TYPE || board[m.toY][m.toX].color != c)) {

            pushMove(m);
        }
    }
}

void Board::getMovesBishop(int x, int y, PieceColor c) const noexcept {
    constexpr std::array<std::pair<int, int>, 4> directions = {{
            {1, 1},{-1, 1},
            {1, -1},{-1, -1}
    }};
    move m = {
        .fromX = x,
        .fromY = y,
        .color = c
    };

    for (auto [dx, dy] : directions) {
        for (int i = 1; (x + dx * i >= 0) && (x + dx * i <= 7) && (y + dy * i >= 0) && (y + dy * i <= 7); i++) {
            m.toX = x + i * dx;
            m.toY = y + i * dy;

            if (board[m.toY][m.toX].type == PieceType::NO_TYPE) {
                pushMove(m);
            } else if (board[m.toY][m.toX].color != c) {
                pushMove(m);
                break;
            } else {
                break;
            }
        }
    }
}

void Board::getMovesQueen(int x, int y, PieceColor c) const noexcept {
    getMovesBishop(x, y, c);
    getMovesRook(x, y, c);
}

void Board::getMovesKing(int x, int y, PieceColor c) const noexcept {
    constexpr std::array<std::pair<int, int>, 8> directions = {
        {
            {1, 1},{1, 0},
            {1, -1},{0, 1},
            {0, -1},{-1, 1},
            {-1, 0},{-1, -1},
        }};
    move m = {
        .fromX = x,
        .fromY = y,
        .color = c
    };

    for (auto [dx, dy] : directions) {
        m.toX = x + dx;
        m.toY = y + dy;

        if (m.toX <= 0 || m.toY <= 0 || m.toX > 8 || m.toY > 8) {
            continue;
        }

        if (board[m.toY][m.toX].type == PieceType::NO_TYPE || board[m.toY][m.toX].color != c) {
            pushMove(m);
        }
    }
}

void Board::getMovesPawn(int x, int y, PieceColor c) const noexcept {
    move m = {
        .fromX = x,
        .fromY = y,
        .color = c
    };

    if (c == PieceColor::WHITE) {
        if (board[y + 1][x].type == PieceType::NO_TYPE) {
            m.toX = x;
            m.toY = y + 1;
            pushMove(m);
            if (y == 1 && board[y + 2][x].type == PieceType::NO_TYPE) {
                m.toX = x;
                m.toY = y + 2;
                pushMove(m);
            }
        }
        if (x != 7) {
            if (board[y + 1][x + 1].type != PieceType::NO_TYPE && board[y + 1][x + 1].color != c) {
                m.toX = x + 1;
                m.toY = y + 1;
                pushMove(m);
            }
        }
        if (x != 0) {
            if (board[y + 1][x - 1].type != PieceType::NO_TYPE && board[y + 1][x - 1].color != c) {
                m.toX = x - 1;
                m.toY = y + 1;
                pushMove(m);
            }
        }
    } else {
        if (board[y - 1][x].type == PieceType::NO_TYPE) {
            m.toX = x;
            m.toY = y - 1;
            pushMove(m);
            if (y == 6 && board[y - 2][x].type == PieceType::NO_TYPE) {
                m.toX = x;
                m.toY = y - 2;
                pushMove(m);
            }
        }
        if (x != 7) {
            if (board[y - 1][x + 1].type != PieceType::NO_TYPE && board[y - 1][x + 1].color != c) {
                m.toX = x + 1;
                m.toY = y - 1;
                pushMove(m);
            }
        }
        if (x != 0) {
            if (board[y - 1][x - 1].type != PieceType::NO_TYPE && board[y - 1][x - 1].color != c) {
                m.toX = x - 1;
                m.toY = y - 1;
                pushMove(m);
            }
        }
    }
}

void Board::getMoves(int x, int y, PieceType type, PieceColor c) const noexcept {
    switch (type) {
    case PieceType::NO_TYPE:
        return;
    case PieceType::ROOK:
        getMovesRook(x, y, c);
        break;
    case PieceType::KNIGHT:
        getMovesKnight(x, y, c);
        break;
    case PieceType::BISHOP:
        getMovesBishop(x, y, c);
        break;
    case PieceType::QUEEN:
        getMovesQueen(x, y, c);
        break;
    case PieceType::KING:
        getMovesKing(x, y, c);
        break;
    case PieceType::PAWN:
        getMovesPawn(x, y, c);
        break;
    default:
        break;
    }
}

bool Board::checkForCheck(PieceColor c) const noexcept{
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board[i][j].color != c) {
                const move m = {
                    .toX = kingPositions[static_cast<int>(c)].x,
                    .toY = kingPositions[static_cast<int>(c)].y,
                    .fromX = j,
                    .fromY = i,
                };
                if (CheckMove(m)) {
                    return true;
                }
            }
        }
    }
    return false;
}

void Board::showMoves(Piece p, int x, int y) const noexcept{
    getMoves(x, y, p.type, p.color);

    for (int i = 0; i < pos; i++) {
        moveBuffer[i].print();
    }
}

bool Board::makeMove(const move &m) noexcept {
    if (!CheckMove(m)) {
        return false;
    }

    if (m.type == PieceType::KING) {
        board[m.toY][m.toX].type = m.type;
        board[m.toY][m.toX].color = m.color;

        board[m.fromY][m.fromX].type = PieceType::NO_TYPE;

        kingPositions[static_cast<int>(m.color)].x = m.toX;
        kingPositions[static_cast<int>(m.color)].y = m.toY;

    } else if (m.type == PieceType::ROOK) {}
}