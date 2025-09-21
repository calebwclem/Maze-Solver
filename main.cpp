#include "Maze.h"
#include <iostream>
#include <string>
#include <stack>

int main(int argc, char* argv[]) {
    // Expect exactly one argument: the input file name
    if (argc != 2) {
        std::cerr << "Usage: " << (argc > 0 ? argv[0] : "./a.out") << " <maze_file>\n";
        return 1;
    }
    const std::string path = argv[1];

    Maze maze;

    if (!maze.loadFromFile(path)) {
        std::cerr << "Failed to load maze file: " << path << '\n';
        return 1;
    }

    if (!maze.detectEntrances()) {
        std::cerr << "Failed to detect exactly two entrances.\n";
        return 1;
    }

    std::stack<Maze::Cell> pathStack;
    if (maze.solve(pathStack)) {
        // Print the maze with the solution path overlaid
        maze.printSolution(pathStack);
    } else {
        std::cout << "No solution found.\n";
    }

    return 0;
}