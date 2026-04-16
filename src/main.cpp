#include "chess.hpp"
#include "functions.hpp"

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
            y = find(chess.coordsY, sizeof(chess.coordsY) / sizeof(char), position[0]);
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
        catch (int num)
        {
            std::cout << "Use PGN notation" << std::endl;
        }
    }
    /*
    chess.printBoard();
    chess.moveChess(3 + 1 * 8, 3 + 3 * 8);
    chess.printBoard();
    
    CrossSleep(1000);
    chess.moveChess(3 + 3 * 8, 3 + 4 * 8);
    chess.printBoard();

    CrossSleep(1000);
    chess.moveChess(4 + 6 * 8, 4 + 4 * 8);
    chess.printBoard();
    
    CrossSleep(1000);
    chess.moveChess(3 + 4 * 8, 4 + 5 * 8);
    chess.printBoard();
    CrossSleep(1000);
    */
    chess.printBoard();
    chess.moveChess(4 + 6 * 8, 4 + 4 * 8);
    chess.printBoard();
    CrossSleep(1000);
    chess.moveChess(4 + 4 * 8, 4 + 3 * 8);
    chess.printBoard();

    CrossSleep(1000);
    chess.moveChess(3 + 1 * 8, 3 + 3 * 8);
    chess.printBoard();
    
    CrossSleep(1000);
    chess.moveChess(4 + 3 * 8, 3 + 2 * 8);
    chess.printBoard();
    
    CrossSleep(1000);
    chess.moveChess(5 + 6 * 8, 4 + 6 * 8);
    chess.printBoard();
    
    CrossSleep(1000);
    chess.moveChess(5 + 6 * 8, 6 + 7 * 8);
    chess.printBoard();
    
    CrossSleep(1000);
    chess.moveChess(5 + 6 * 8, 4 + 7 * 8);
    chess.printBoard();

    CrossSleep(1000);
    chess.moveChess(3 + 7 * 8, 7 + 3 * 8);
    chess.printBoard();
    
    CrossSleep(1000);
    chess.moveChess(5 + 6 * 8, 5 + 5 * 8);
    chess.printBoard();
    
    CrossSleep(1000);
    chess.moveChess(5 + 5 * 8, 6 + 5 * 8);
    chess.printBoard();

    CrossSleep(1000);
    chess.moveChess(7 + 3 * 8, 3 + 7 * 8);
    chess.printBoard();
    
    CrossSleep(1000);
    
    std::cout << chess.PGN;

    return 0;
}