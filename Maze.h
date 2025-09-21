#ifndef MAZE_BACKTRACKING_MAZE_H
#define MAZE_BACKTRACKING_MAZE_H

#include <string>
#include <vector>
#include <stack>

class Maze {
public:

    // Accessor struct
    struct Cell {
        int r = -1, c = -1;
    };

    // Load a 0/1 grid from a file (each line is a row of '0' and '1').
    // Returns true on success.
    bool loadFromFile(const std::string& path);

    // Print the grid as 0/1 characters.
    void printRaw() const;

    //Detect two openings on the border and store them as
    // start and goal. Returns true if EXACTLY 2 entrances are found.
    bool detectEntrances();

    // Function to attempt to solve the maze. Returns true if a solution is found
    //      otherwise returns false;
    bool solve(std::stack<Cell>& path);

    //startCell/goalCell accessors
    [[nodiscard]] Cell startCell() const {return start;}
    [[nodiscard]] Cell goalCell() const {return goal;}

    // Print the maze with the solution path overlaid.
    // Cells in 'path' are printed as a red '*', others as original '0' or '1'.
    void printSolution(const std::stack<Cell>& path) const;

    //Number of rows/cols accessors
    [[nodiscard]] int rows() const { return static_cast<int>(grid.size()); }
    [[nodiscard]] int cols() const { return grid.empty() ? 0 : static_cast<int>(grid[0].size()); }


private:
    std::vector<std::vector<int>> grid; // 0=open, 1=wall
    Cell start{-1,-1};
    Cell goal{-1,-1};

    // Helpers to keep solve clean and modular
    [[nodiscard]] bool inBounds(int r, int c) const;
    [[nodiscard]] bool isOpen(int r, int c) const;
    // Depth-First Search: explores in order of ~ Right, Down, Up, Left.
    // Pushes cells onto 'path' on entry; pops on backtrack.
    bool dfs(int r, int c, std::stack<Cell>& path, std::vector<std::vector<bool>>& visited);
};

#endif // MAZE_BACKTRACKING_MAZE_H