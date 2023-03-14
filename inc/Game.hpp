#pragma once

#include "Board.hpp"
#include "Player.hpp"
#include "math.h"

class Game{
    protected:
    Board BoardPlay;
    Player player;
    Player Bot;
    public:
    Game();
    ~Game();
    void StartGame();
    void PlayerMove(int Size);
    bool CheckMove(int x, int y, int Size);
    void BotMoveMake(int Size, int Row, int Difficalty);
};