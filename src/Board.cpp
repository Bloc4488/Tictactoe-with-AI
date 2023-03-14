#include "Board.hpp"
Board::Board()
{

}

Board::~Board()
{

}

Board::Board(int Size)
{
    BoardToPlay = new int*[Size];
    for (int i = 0; i < Size; i++)
    {
        BoardToPlay[i] = new int[Size];
    }
    for (int i = 0; i < Size; i++)
    {
        for (int j = 0; j < Size; j++) BoardToPlay[i][j] = 0;
    }
}

void Board::PrintBoard(int Size)
{
    std::cout << "  ";
    for (int i = 0; i < Size; i++)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < Size; i++)
    {
        std::cout << i << " ";
        for (int j = 0; j < Size; j++)
        {
            if (BoardToPlay[j][i] == 0) std::cout << "- ";
            else if (BoardToPlay[j][i] == 1) std::cout << "x ";
            else if (BoardToPlay[j][i] == 2) std::cout << "o ";
        }
        std::cout << std::endl;
    }
}

bool Board::CheckWin(int Size, int Row, int PlayerMove)
{
    //Horizontal
    for (int i = 0; i < Size; i++)
    {
        for (int j = 0; j < (Size - Row + 1); j++)
        {
            if (BoardToPlay[j][i] == PlayerMove)
            {
                int Elements = 0;
                bool Win = false;
                while (Elements < Row)
                {
                    if (BoardToPlay[j][i] == BoardToPlay[j + Elements][i]) Win = true;
                    else {Win = false; break;}
                    Elements++;
                }
                if (Win) return true;
            }

        }
    }
    //Vertical
    for (int i = 0; i < Size; i++)
    {
        for (int j = 0; j < (Size - Row + 1); j++)
        {
            if (BoardToPlay[i][j] == PlayerMove)
            {
                int Elements = 0;
                bool Win = false;
                while (Elements < Row)
                {
                    if (BoardToPlay[i][j] == BoardToPlay[i][j + Elements]) Win = true;
                    else {Win = false; break;}
                    Elements++;
                }
                if (Win) return true;
            }

        }
    }
    //Diag
    for (int i = 0; i < (Size - Row + 1); i++)
    {
        for (int j = 0; j < (Size - Row + 1); j++)
        {
            if (BoardToPlay[j][i] == PlayerMove)
            {
                int Elements = 0;
                bool Win = false;
                while (Elements < Row)
                {
                    if (BoardToPlay[j][i] == BoardToPlay[j + Elements][i + Elements]) Win = true;
                    else {Win = false; break;}
                    Elements++;
                }
                if (Win) return true;
            }

        }
    }
    for (int i = Row - 1; i < Size; i++)
    {
        for (int j = 0; j < (Size - Row + 1); j++)
        {
            if (BoardToPlay[j][i] == PlayerMove)
            {
                int Elements = 0;
                bool Win = false;
                while (Elements < Row)
                {
                    if (BoardToPlay[j][i] == BoardToPlay[j + Elements][i - Elements]) Win = true; 
                    else {Win = false; break;}
                    Elements++;
                }
                if (Win) return true;
            }

        }
    }
    return false;
}

bool Board::CheckTie(int Size)
{
    for (int i = 0; i < Size; i++)
    {
        for (int j = 0; j < Size; j++)
        {
            if (BoardToPlay[i][j] == 0) return false;
        }
    }
    return true;
}

BotMove Board::Minimax(int Size, int Row, int BotXO, int PlayerXO, int depth)
{
    int tmp;
    int MaxPoint = 1000;
    for (int i = 0; i < Size; i++)
    {
        for (int j = 0; j < Size; j++)
        {
            if (BoardToPlay[j][i] == 0)
            {
                BoardToPlay[j][i] = BotXO;
                depth--;
                tmp = Max(depth, PlayerXO, BotXO, Size, Row);
                if (tmp < MaxPoint)
                {
                    Movebot.Movex = j;
                    Movebot.Movey = i;
                    MaxPoint = tmp;
                }
                BoardToPlay[j][i] = 0;
                depth++;
            }
        }
    }
    return Movebot;
}

int Board::Max(int depth, int PlayerXO, int BotXO, int Size, int Row)
{
    if (CheckWin(Size, Row, PlayerXO)) return FreeMoves(Size) + 1;
    else if (CheckWin(Size, Row, BotXO)) return -(FreeMoves(Size) + 1);
    else if (CheckTie(Size)) return 0;
    int tmp = -1000;
    if (depth > 0){
        for (int i = 0; i < Size; i++)
        {
            for (int j = 0; j < Size; j++)
            {
                if (BoardToPlay[j][i] == 0)
                {
                    depth--;
                    BoardToPlay[j][i] = PlayerXO;
                    tmp = std::max(tmp, Min(depth, PlayerXO, BotXO, Size, Row));
                    BoardToPlay[j][i] = 0;
                    depth++;
                }
            }
        }
    }
    return tmp;
}

int Board::Min(int depth, int PlayerXO, int BotXO, int Size, int Row)
{
    if (CheckWin(Size, Row, PlayerXO)) return FreeMoves(Size) + 1;
    else if (CheckWin(Size, Row, BotXO)) return -(FreeMoves(Size) + 1);
    else if (CheckTie(Size)) return 0;
    int tmp = 1000;
    if (depth > 0){
        for (int i = 0; i < Size; i++)
        {
            for (int j = 0; j < Size; j++)
            {
                if (BoardToPlay[j][i] == 0)
                {
                    depth--;
                    BoardToPlay[j][i] = BotXO;
                    tmp = std::min(tmp, Max(depth, PlayerXO, BotXO, Size, Row));
                    BoardToPlay[j][i] = 0;
                    depth++;
                }
            }
        }
    }
    return tmp;
}

int Board::FreeMoves(int Size)
{
    int count = 0;
    for (int i = 0; i < Size; i++)
    {
        for (int j = 0; j < Size; j++)
        {
            if (BoardToPlay[i][j] == 0) count++;
        }
    }
    return count;
}
