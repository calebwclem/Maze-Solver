#include "Maze.h"
#include <iostream>
#include <fstream>
#include <string>
#include <tuple>
#include <stack>
#include <vector> // added

int main() {

    //Initialize the maze object to be used
    Maze maze;

    // For now, use the hardcoded file path
    const std::string path = "maze0-1_input.txt";

    if (!maze.loadFromFile(path)) {
        std::cerr << "Failed to load maze file: " << path << '\n';
        return 1;
    }

    // Echo the parsed maze to verify input
    maze.printRaw();

    // Detect the Entrances and store them
    if (!maze.detectEntrances()) {
        std::cerr << "Failed to detect exactly two entrances.\n";
        return 1;
    }

    // Echo the stored entrance and exit for debugging purposes.
    std::cout << "Start: " << maze.startCell().r << ',' << maze.startCell().c << '\n';
    std::cout << "Goal: " << maze.goalCell().r << ',' << maze.goalCell().c << '\n';

    // Attempt to solve and print the path
    std::stack<Maze::Cell> pathStack;
    if (maze.solve(pathStack)) {
        std::cout << "Solution found! Steps: " << pathStack.size() << '\n';

        // Visualize the solution directly on the maze
        maze.printSolution(pathStack);

    } else {
        std::cout << "No solution found.\n";
    }

    return 0;
}