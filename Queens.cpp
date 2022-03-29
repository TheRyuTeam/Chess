#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <fstream>

using index_type = long long int;
using board_type = std::vector<std::vector<bool>>;

board_type board =
{
    {0, 0, 0, 0, 0, 0, 0, 0},   //0
    {0, 0, 0, 0, 0, 0, 0, 0},   //1
    {0, 0, 0, 0, 0, 0, 0, 0},   //2
    {0, 0, 0, 0, 0, 0, 0, 0},   //3
    {0, 0, 0, 0, 1, 0, 0, 0},   //4
    {0, 1, 0, 0, 0, 0, 0, 0},   //5
    {0, 0, 0, 0, 0, 0, 0, 0},   //6
    {0, 0, 0, 0, 0, 0, 0, 0},   //7
};

bool hasVerticalCollision(index_type x)
{
    for(index_type y = 0; y < board.size(); ++y)
    {
        if (board[y][x])
            return true;
    }
    return false;
}

bool hasHorizontalCollision(index_type y)
{
    return board[y].end() != std::find(board[y].begin(), board[y].end(), 1);
}

bool hasDiagonalCollision(index_type y, index_type x)
{
    for (auto _y = y, _x = x; _y != -1 && _x != -1; --_y, --_x)
    {
        if (board[_y][_x])
            return true;
    }
    for (auto _y = y, _x = x; _y < board.size() && _x < board[_y].size(); ++_y, ++_x)
    {
        if (board[_y][_x])
            return true;
    }
    for (auto _y = y, _x = x; _y < board.size() && _x != -1; ++_y, --_x)
    {
        if (board[_y][_x])
            return true;
    }
    for (auto _y = y, _x = x; _y != -1 && _x < board[_y].size(); --_y, ++_x)
    {
        if (board[_y][_x])
            return true;
    }
    return false;
}

bool solutionImpl(int nQueen, index_type y)
{
    if (0 == nQueen)
        return true;

    if (board.size() <= y)
        return false;

    if (hasHorizontalCollision(y))
        return solutionImpl(nQueen, y + 1);
    
    for(index_type x = 0; x < board[y].size(); ++x)
    {
        if (!hasVerticalCollision(x) && !hasDiagonalCollision(y, x))
        {
            board[y][x] = 1;

            if (solutionImpl(nQueen - 1, y + 1))
                return true;

            board[y][x] = 0;
        }
    }
    return false;
}

bool isBoardValid()
{
    for(index_type y = 0; y < board.size(); ++y)
    {
        if (board.size() != board[y].size())
            return false;

        std::size_t nCount = 0;
        for(index_type x = 0; x < board[y].size(); ++x)
        {
            if (board[y][x])
            {
                board[y][x] = 0;
                
                if (2 == ++nCount || hasVerticalCollision(x) || hasDiagonalCollision(y, x))
                    return false;

                board[y][x] = 1;
            }
        }
    }
    return true;
}

bool solution(int nQueen)
{
    return isBoardValid() ? solutionImpl(nQueen, 0) : false;
}

int main(int argc, char** argv)
{   
    std::ofstream output("chess-log.txt");
    if (solution(6))
    {
        output << "Solution:\n";
        for(const auto& row: board)
        {
            std::copy(row.begin(), row.end(), std::ostream_iterator<bool>(output, " "));
            output << '\n';
        }
    }
    else
    {
        output << "No solution";
    }
    return EXIT_SUCCESS;
}