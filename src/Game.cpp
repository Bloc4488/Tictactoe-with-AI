#include "Game.hpp"

Game::Game()
{

}

Game::~Game()
{

}


void Game::BotMoveMake(int Size, int Row, int Difficalty)
{
    BotMove Moveb;
    Moveb = BoardPlay.Minimax(Size, Row, Bot.PlayXO, player.PlayXO, Difficalty);
    std::cout << "Bot made move[x, y]: " << Moveb.Movex << " " << Moveb.Movey << std::endl;
    BoardPlay.Move(Moveb.Movex, Moveb.Movey, Bot.PlayXO);
    player.YourMove = true;
    Bot.YourMove = false;
}


void Game::PlayerMove(int Size)
{
    int x, y;
    std::cout << "Make a move. Enter x[0 - " << Size - 1 << "] and y[0 - " << Size -1 << "]: ";
    std::cin >> x >> y;
    while (!CheckMove(x, y, Size))
    {
        std::cout << "Make a move. Enter x[0 - " << Size - 1 << "] and y[0 - " << Size -1 << "]: ";
        std::cin >> x >> y;
    }
    BoardPlay.Move(x, y, player.PlayXO);
    player.YourMove = false;
    Bot.YourMove = true;
}

bool Game::CheckMove(int x, int y, int Size)
{
    if (x >= Size || y >= Size) return false;
    if (BoardPlay(x, y) == 0) return true;
    else return false;
}

void Game::StartGame()
{
    int SizeOfBoard;
    int ElementsInRow;
    int Difficalty;
    int XO;
    bool exit = true;
    std::cout << "Enter size of the board(Size x Size): ";
    std::cin >> SizeOfBoard;
    std::cout << "Enter amount of elements in row: ";
    std::cin >> ElementsInRow;
    while (ElementsInRow > SizeOfBoard)
    {
        std::cout << "Please, enter amount of elements < size of the board" << std::endl;
        std::cout << "Enter amount of elements in row: ";
        std::cin >> ElementsInRow;
    }
    Difficalty = 5; //floor(1.6 * SizeOfBoard - ElementsInRow); 
    BoardPlay = Board(SizeOfBoard);
    std::cout << "Choose x - 1 or o - 2: ";
    std::cin >> XO;
    if (XO == 1)
    {
        player.YourMove = true;
        player.PlayXO = XO;
        Bot.PlayXO = 2;
    }
    else
    {
        Bot.YourMove = true;
        Bot.PlayXO = 1;
        player.PlayXO = XO;
    }
    BoardPlay.PrintBoard(SizeOfBoard);
    while(exit){
        if (BoardPlay.CheckTie(SizeOfBoard)) 
            {
                exit = false; 
                std::cout << "Tie!" << std::endl; 
                break;
            }
        else if (player.YourMove)
        {
            PlayerMove(SizeOfBoard);
            BoardPlay.PrintBoard(SizeOfBoard);
            if (BoardPlay.CheckWin(SizeOfBoard, ElementsInRow, player.PlayXO)) 
                {
                    exit = false; 
                    std::cout << "Player wins!" << std::endl; 
                    Bot.YourMove = false; 
                    break;
                }
        }
        else if (Bot.YourMove)
        {
            BotMoveMake(SizeOfBoard, ElementsInRow, Difficalty);
            BoardPlay.PrintBoard(SizeOfBoard);
            if (BoardPlay.CheckWin(SizeOfBoard, ElementsInRow, Bot.PlayXO)) 
                {
                    exit = false; 
                    std::cout << "Bot wins!" << std::endl; 
                    player.YourMove = false; 
                    break;
                }
        }
    }
}