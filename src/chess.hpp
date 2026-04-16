#pragma once

#include <iostream>
#include <string>
#include <sstream>

class Chess
{
private:
    const short sideSize = 8;
    bool canDoEnPassant, turn;
    short enPassantAt, board[64];

public:
    bool gameOn;
    std::string PGN;
    const char pairs[16];
    const char coordsX[8];
    const char coordsY[8];
    static const short black = 0b1000,
          white = 0b0000, // created for clarity
          diffColor = 0b1000, // created for clarity
          empty = 0b0000, // created for clarity
          king = 0b111,
          queen = 0b110,
          rook = 0b100,
          bishop = 0b011,
          knight = 0b010,
          pawn = 0b001;
    Chess();

    bool checkChessMovement(short piece, short from, short x, short y);
    bool checkIfHorizontalMove(short x, short y);
    bool checkIfDiagonalMove(short x, short y);
    bool checkKnightMove(short x, short y);
    bool checkPawnMove(short from, short x, short y);
    bool checkSpaceEmpty(short from, short x, short y);
    void moveChess(short from, short to);
    void printBoard();
    void convertToCoords(short pos, short& x, short& y);
    void convertToPos(short x, short y, short& pos);
    std::string coords(short from, short end);
};