#include <iostream>
#include <vector>
#include <fstream>
#include <iterator>
#include <limits>

std::vector<std::vector<std::size_t>> board;
constexpr std::size_t initValue = 0;

bool solution(std::size_t y, std::size_t x, std::size_t step = 1)
{
    board[y][x] = step;
    
    if (step >= board.size() * board.size())
        return true;

    const int steps[]  {-2, -1, -2, +1,         // top
                        -1, +2, +1, +2,         // right
                        +2, +1, +2, -1,         // bottom
                        +1, -2, -1, -2          // left
                        };
    
    for (unsigned char i = 0; i + 1 < 16; i += 2)
    {
        const auto nextY = y + steps[i];
        const auto nextX = x + steps[i + 1];
        if (board.size() > nextY && board.size() > nextX &&
            board[nextY][nextX] == initValue && 
            solution(nextY, nextX, step + 1))
        {
            return true;
        }
    }

    board[y][x] = initValue;

    return false;
}

int main(int argc, char** argv)
{
    if (argc < 4)
    {
        std::cout << "Using: <board size> <y> <x>;";
        return EXIT_FAILURE;
    }

    std::size_t size {};
    std::size_t y {};
    std::size_t x {};
    try
    {
        size = std::stoull(argv[1]);
        y = std::stoull(argv[2]);
        x = std::stoull(argv[3]);

        if (size < y || size < x)
            throw std::invalid_argument("Start pos must be less than board size.");
    }
    catch(const std::exception& e)
    {
        std::cerr << "Invalid args:\n";
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }
    
    board = std::vector<std::vector<std::size_t>>(size, std::vector<std::size_t>(size));

    std::ofstream output("knight.log");

    if (solution(y, x))
    {
        output << "Solution:\n";
        for (const auto& row: board)
        {
            std::copy(row.begin(), row.end(), std::ostream_iterator<std::size_t>(output, "\t"));
            output << '\n';
        }
    }
    else
    {
        output << "No solution.";
    }
    return EXIT_SUCCESS;
}