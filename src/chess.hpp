#pragma once

#include <iostream>
#include <string>
#include <sstream>

class Chess
{
private:
    const int sideSize = 8;
    bool canDoEnPassant, turn;
    int enPassantAt, board[64];

public:
    bool gameOn;
    std::string PGN;
    const char pairs[16];
    const char coordsX[8];
    const char coordsY[8];
    static const short black = 0b1000,
          white = 0b0000, // created for clarity
          empty = 0b0000, // created for clarity
          king = 0b111,
          queen = 0b110,
          rook = 0b100,
          bishop = 0b011,
          knight = 0b010,
          pawn = 0b001;
    Chess();

    bool checkChessMovement(int piece, int from, int x, int y);
    bool checkIfHorizontalMove(int x, int y);
    bool checkIfDiagonalMove(int x, int y);
    bool checkKnightMove(int x, int y);
    bool checkPawnMove(int from, int x, int y);
    bool checkSpaceEmpty(int from, int x, int y);
    void moveChess(int from, int to);
    void printBoard();
    void convertToCoords(int pos, int& x, int& y);
    void convertToPos(int x, int y, int& pos);
    std::string coords(int from, int end);
};