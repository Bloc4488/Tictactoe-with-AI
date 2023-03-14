#pragma once

#include <iostream>
#include <fstream>

struct BotMove
{
    int Movex, Movey;
};

class Board {
    public:
    int **BoardToPlay;// 0 = -; 1 = x; 2 = o;
    BotMove Movebot;
    Board();
    Board(int Size);
    ~Board();
    void PrintBoard(int Size);
    bool CheckWin(int Size, int Row, int PlayerMove);
    bool CheckTie(int Size);
    int operator ()(int i, int j) {return BoardToPlay[i][j];};
    void Move(int x, int y, int i) {BoardToPlay[x][y] = i;};
    BotMove Minimax(int Size, int Row, int BotXO, int PlayerXO, int depth);
    int Max(int depth, int PlayerXO, int BotXO, int Size, int Row);
    int Min(int depth, int PlayerXO, int BotXO, int Size, int Row);
    int FreeMoves(int Size);
};