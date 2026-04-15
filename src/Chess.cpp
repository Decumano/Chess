#include "chess.hpp"
#include "functions.hpp"

void Chess::convertToCoords(int pos, int& x, int& y)
{
    x = pos / sideSize;
    y = pos % sideSize;
}

void Chess::convertToPos(int x, int y, int& pos)
{
    pos = x * sideSize + y;
}

bool Chess::checkIfHorizontalMove(int x, int y)
{
    return ((x == 0 && abs(y) >= 0) || (y == 0 && abs(x) >= 0));
}

bool Chess::checkIfDiagonalMove(int x, int y)
{
    return (x == y);
}

bool Chess::checkSpaceEmpty(int from, int x, int y)
{
    int i, j, xcorr = -1, ycorr = -1;
    if (!((board[from] ^ knight == white) || (board[from] ^ knight == black)))
    {
        int fx, fy, dx, dy;
        convertToCoords(from, fx, fy);

        dx = fx - x;
        dy = fy - y;

        if (dx < 0) dx = -dx;
        else xcorr = 1;
        
        if (dy < 0) dy = -dy;
        else ycorr = 1;

        for (i = 1; i < x; i++)
            for (j = 1; j < y; j++)
                if (board[from + xcorr * i * sideSize + ycorr * j] != empty) return false;
    }

    if (board[from] & black)
        return board[from + y + x * sideSize] == empty || !(board[from + y + x * sideSize] & black);
    
    return board[from + y + x * sideSize] == empty || board[from + y + x * sideSize] & black;
}

bool Chess::checkKnightMove(int x, int y)
{
    return ((abs(y) == 2 && abs(x) == 1) || (abs(x) == 2 && abs(y) == 1));
}

bool Chess::checkPawnMove(int from, int x, int y)
{
    canDoEnPassant = false;
    if (board[from] & Chess::black)
    {
        if ((x == y) && (abs(x) == 1) && !(board[from + y + x * sideSize] & black) && (board[from + y + x * sideSize] != 0)) return true;

        if (canDoEnPassant && (x == y) && (abs(x) == 1) && !(board[enPassantAt] & black) && ((from + 1 == enPassantAt) || (from - 1 == enPassantAt)))
        {
            board[enPassantAt] = 0;
            return true;
        }
        if (y != 0) return false;
        if ((from / 8 == 1) && x == 2)
        {
            canDoEnPassant = true;
            enPassantAt = from + y + x * sideSize;
            return true;
        }
        if (x == 1) return true;
    }
    else
    {
        if ((x == y) && (abs(x) == 1) && (board[from + y + x * sideSize] & black)) return true;
        
        if (canDoEnPassant && (x == y) && (abs(x) == 1) && (board[enPassantAt] & black) && ((from + 1 == enPassantAt) || (from - 1 == enPassantAt)))
        {
            board[enPassantAt] = 0;
            return true;
        }
        if (y != 0) return false;
        if ((from / 8 == 6) && x == -2)
        {
            canDoEnPassant = true;
            enPassantAt = from + y + x * sideSize;
            return true;
        }
        if (x == -1) return true;
    }
    turn = !turn;
    return false;
}

bool Chess::checkChessMovement(int piece, int from, int x, int y)
{
    switch (piece)
    {
    case king:
    case king + black:
        return (abs(x) <= 1 && abs(y) <= 1 && checkSpaceEmpty(from, x, y));
    case queen:
    case queen + black:
        return ((checkIfDiagonalMove(x, y) || checkIfHorizontalMove(x, y)) && checkSpaceEmpty(from, x, y));
    case rook:
    case rook + black:
        return (checkIfHorizontalMove(x, y) && checkSpaceEmpty(from, x, y));
    case bishop:
    case bishop + black:
        return (checkIfDiagonalMove(x, y) && checkSpaceEmpty(from, x, y));
    case knight:
    case knight + black:
        return (checkKnightMove(x, y) && checkSpaceEmpty(from, x, y));
    case pawn:
    case pawn + black:
        return (checkPawnMove(from, x, y) && checkSpaceEmpty(from, x, y));
    }

    return false;
}

void Chess::printBoard()
{
    int i, j;

    ClearScreen();
    std::cout << std::endl << "------------------------------------------------" << std::endl;
    for (i = 0; i < sideSize; i++)
    {
        for (j = 0; j < sideSize; j++)
        {
            if (j == 0)
                std::cout << "  ";
            std::cout << pairs[board[j + sideSize * i]] << "  |  ";
            if (j == 7)
            {
                std::cout << std::endl << "------------------------------------------------" << std::endl;
            }
        }
    }
    std::cout << std::endl << std::endl;
}

Chess::Chess() : pairs{ ' ', 'p', 'n', 'b', 'r', ' ', 'q', 'k', ' ', 'P', 'N', 'B', 'R', ' ', 'Q', 'K' }, coordsX{ '1', '2', '3', '4', '5', '6', '7', '8' }, coordsY{ 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' }
{
    turn = true;
    gameOn = false; // Initialize gameOn, debug on false for specific movements
    canDoEnPassant = false;
    enPassantAt = -1;
    for (int i = 0; i < 64; i++)
    {
        switch (i)
        {
        case 7:
        case 0:
            board[i] = Chess::black + Chess::rook;
            break;
        case 6:
        case 1:
            board[i] = Chess::black + Chess::knight;
            break;
        case 5:
        case 2:
            board[i] = Chess::black + Chess::bishop;
            break;
        case 3:
            board[i] = Chess::black + Chess::queen;
            break;
        case 4:
            board[i] = Chess::black + Chess::king;
            break;
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
            board[i] = Chess::black + Chess::pawn;
            break;
        case 63:
        case 56:
            board[i] = Chess::white + Chess::rook;
            break;
        case 62:
        case 57:
            board[i] = Chess::white + Chess::knight;
            break;
        case 61:
        case 58:
            board[i] = Chess::white + Chess::bishop;
            break;
        case 59:
            board[i] = Chess::white + Chess::queen;
            break;
        case 60:
            board[i] = Chess::white + Chess::king;
            break;
        case 48:
        case 49:
        case 50:
        case 51:
        case 52:
        case 53:
        case 54:
        case 55:
            board[i] = Chess::white + Chess::pawn;
            break;
        default:
            board[i] = 0;
        }
    }
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    std::ostringstream stream;
    stream << "[EVENT \"Computer Test\"]\n[Site \"Online\"]\n[Date \"" << std::ctime(&time) << "]\n[Result \"0-0\"]\n[White \"Computer 1\"]\n[Black \"Computer 2\"]\n";
    PGN = stream.str();
}

std::string Chess::coords(int from, int end)
{
    int temp = board[from] ^ pawn;
    std::string piece = "";
    if (!((temp == 0) || (temp == black)))
        piece = pairs[board[from]];
    if (board[end] != 0)
        piece += (std::string)"x";
    return piece + coordsY[end % 8] + coordsX[end / 8];
}

void Chess::moveChess(int from, int to)
{
    int x = (to / 8) - (from / 8),
        y = (to % 8) - (from % 8);
    
    if (checkChessMovement(board[from], from, x, y))
    {
        PGN += coords(from, to) + (std::string)" ";
        board[to] = board[from];
        board[from] = 0;
    }
}

