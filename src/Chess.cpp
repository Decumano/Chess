// Chess.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <windows.h>
#include <string>
#include <chrono>

int find(const char arr[], int len, char seek)
{
    for (int i = 0; i < len; ++i)
    {
        if (arr[i] == seek) return i;
    }
    return -1;
}

void ClearScreen()
{
    HANDLE                     hStdOut;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD                      count;
    DWORD                      cellCount;
    COORD                      homeCoords = { 0, 0 };

    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hStdOut == INVALID_HANDLE_VALUE) return;

    /* Get the number of cells in the current buffer */
    if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
    cellCount = csbi.dwSize.X * csbi.dwSize.Y;

    /* Fill the entire buffer with spaces */
    if (!FillConsoleOutputCharacter(
        hStdOut,
        (TCHAR)' ',
        cellCount,
        homeCoords,
        &count
    )) return;

    /* Fill the entire buffer with the current colors and attributes */
    if (!FillConsoleOutputAttribute(
        hStdOut,
        csbi.wAttributes,
        cellCount,
        homeCoords,
        &count
    )) return;

    /* Move the cursor home */
    SetConsoleCursorPosition(hStdOut, homeCoords);
}

int abs(int value)
{
    uint32_t temp = value >> 31;     // make a mask of the sign bit
    value ^= temp;                   // toggle the bits if value is negative
    value += temp & 1;               // add one if value was negative
    return value;
}

class Chess
{
private:
    const int sideSize = 8;
    bool canDoEnPassantWhite, canDoEnPassantBlack, turn;
    int enPassantAt, board[64];

public:
    bool gameOn;
    std::string PGN;
    const char pairs[16];
    const char coordsX[8];
    const char coordsY[8];
    static const short black = 0b1000, // white = 0b0
          king = 0b111,
          queen = 0b110,
          rook = 0b100,
          bishop = 0b011,
          knight = 0b010,
          pawn = 0b001;
    Chess();

    bool checkChessMovement(int piece, int from, int x, int y);
    bool checkHorizontalMove(int x, int y);
    bool checkDiagonalMove(int x, int y);
    bool checkKnightMove(int x, int y);
    bool checkPawnMove(int from, int x, int y);
    bool checkSpaceEmpty(int from, int x, int y);
    void moveChess(int from, int to);
    void printBoard();
    std::string coords(int from, int end);
};

bool Chess::checkHorizontalMove(int x, int y)
{
    return ((x == 0 && abs(y) >= 0) || (y == 0 && abs(x) >= 0));
}

bool Chess::checkDiagonalMove(int x, int y)
{
    return (x == y);
}

bool Chess::checkSpaceEmpty(int from, int x, int y)
{
    int i;
    if (!(((board[from] ^ knight) == 0) || ((board[from] ^ knight) == black)))
        for (i = 1; i < x; i++)
            if (board[from + i * sideSize] != 0) return false;
    if (board[from] & black)
    {
        return board[from + y + x * sideSize] == 0 || !(board[from + y + x * sideSize] & black);
    }
    return board[from + y + x * sideSize] == 0 || board[from + y + x * sideSize] & black;
}

bool Chess::checkKnightMove(int x, int y)
{
    return ((abs(y) == 2 && abs(x) == 1) || (abs(x) == 2 && abs(y) == 1));
}

bool Chess::checkPawnMove(int from, int x, int y) 
{
    if (canDoEnPassantWhite && turn) canDoEnPassantWhite = false;
    if (canDoEnPassantBlack && !turn) canDoEnPassantBlack = false;
    if (board[from] & Chess::black)
    {
        if ((x == y) && (abs(x) == 1) && !(board[from + y + x * sideSize] & black) && (board[from +y + x * sideSize] != 0)) return true;
        if (canDoEnPassantBlack && (x == y) && (abs(x) == 1) && !(board[enPassantAt] & black) && ((from + 1 == enPassantAt) || (from - 1 == enPassantAt)))
        {
            board[enPassantAt] = 0;
            return true;
        }
        if (y != 0) return false;
        if ((from / 8 == 1) && x == 2)
        {
            canDoEnPassantWhite = true;
            enPassantAt = from + y + x * sideSize;
            return true;
        }
        if (x == 1) return true;
    }
    else
    {
        if ((x == y) && (abs(x) == 1) && (board[from + y + x * sideSize] & black)) return true;
        if (canDoEnPassantWhite && (x == y) && (abs(x) == 1) && (board[enPassantAt] & black) && ((from + 1 == enPassantAt) || (from - 1 == enPassantAt)))
        {
            board[enPassantAt] = 0;
            return true;
        }
        if (y != 0) return false;
        if ((from / 8 == 6) && x == -2)
        {
            canDoEnPassantBlack = true;
            enPassantAt = from + y + x * sideSize;
            return true;
        }
        if (x == -1) return true;
    }
    turn != turn;
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
        return ((checkDiagonalMove(x, y) || checkHorizontalMove(x, y)) && checkSpaceEmpty(from, x, y));
    case rook:
    case rook + black:
        return (checkHorizontalMove(x, y) && checkSpaceEmpty(from, x, y));
    case bishop:
    case bishop + black:
        return (checkDiagonalMove(x, y) && checkSpaceEmpty(from, x, y));
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
            std::cout << pairs[board[j + sideSize*i]] << "  |  ";
            if (j == 7)
            {
                std::cout << std::endl << "------------------------------------------------" << std::endl;
            }
        }
    }
    std::cout << std::endl << std::endl;
}

Chess::Chess() : pairs { ' ', 'p', 'n', 'b', 'r', ' ', 'q', 'k', ' ', 'p', 'N', 'B', 'R', ' ', 'Q', 'K'}, coordsX{'1', '2', '3', '4', '5', '6', '7', '8'}, coordsY{'a', 'b', 'c', 'd','e','f', 'g', 'h'}
{
    turn = true;
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
            board[i] = Chess::rook;
            break;
        case 62:
        case 57:
            board[i] = Chess::knight;
            break;
        case 61:
        case 58:
            board[i] = Chess::bishop;
            break;
        case 59:
            board[i] = Chess::queen;
            break;
        case 60:
            board[i] = Chess::king;
            break;
        case 48:
        case 49:
        case 50:
        case 51:
        case 52:
        case 53:
        case 54:
        case 55:
            board[i] = Chess::pawn;
            break;
        default:
            board[i] = 0;
        }
    }
    auto local = std::chrono::zoned_time{ std::chrono::current_zone(), std::chrono::system_clock::now() };
    std::ostringstream stream;
    stream << "[EVENT \"Computer Test\"]\n[Site \"Online\"]\n[Date \"" << local << "]\n[Result \"0-0\"]\n[White \"Computer 1\"]\n[Black \"Computer 2\"]\n";
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
    int x = (to / 8) - (from / 8), y = (to % 8) - (from % 8);
    if (checkChessMovement(board[from], from, x, y))
    {
        PGN += coords(from, to) + (std::string)" ";
        board[to] = board[from];
        board[from] = 0;
    }
}

int main()
{
    Chess chess;
    std::string position;
    int x, y, piece;
    while (chess.gameOn)
    {
        chess.printBoard();
        std::cout << "Choose a movement to do (e3, e4): " << std::endl;
        try
        {
            std::cin >> position;
            y = find(chess.coordsY, sizeof(chess.coordsY)/sizeof(char), position[0]);
            if (y == -1)
            {
                piece = find(chess.pairs, sizeof(chess.pairs) / sizeof(char), position[0]);
                y = find(chess.coordsY, sizeof(chess.coordsY) / sizeof(char), position[1]);
                x = find(chess.coordsX, sizeof(chess.coordsX) / sizeof(char), position[2]);
            }
            else
            {
                piece = chess.pawn;
                x = find(chess.coordsX, sizeof(chess.coordsX) / sizeof(char), position[1]);
            }
        }
        catch(int num)
        {
            std::cout << "Use PGN notation" << std::endl;
        }
    }
    chess.printBoard();
    chess.moveChess(3 + 1 * 8,3 + 3 * 8);
    chess.printBoard();
    Sleep(1000);
    chess.moveChess(3 + 3 * 8, 3 + 4 * 8);
    chess.printBoard();
    Sleep(1000);
    chess.moveChess(4 + 6 * 8, 4 + 4 * 8);
    chess.printBoard();
    Sleep(1000);
    chess.moveChess(3 + 4 * 8, 4 + 5 * 8);
    chess.printBoard();
    Sleep(1000);
    std::cout << chess.PGN;
    return 0;
}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
