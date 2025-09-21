# Maze-Backtracking

## STUDENT INFORMATION
- Student Name: Caleb Clements
- Student ID: 008878539
- Repository Link: https://github.com/calebwclem/Maze-Solver

## Collaboration & Sources
Used the following sources to help me with this project:
- ChatGPT to discuss my DFS algorithm as well as keeping everything modular
- Used AI Assistant to adjust my main.cpp to properly run given autograder specifications
- Also used AI Assistant to do the 'Implementation Details' section of this README.md

## Implementation Details

- Language/Standard: C++20
- Project: Maze_Backtracking

### Maze representation
- Grid stored as a 2D array-like structure where:
    - 0 = open cell
    - 1 = wall

### Input
- Text file consisting of rows of characters '0' and '1'.
- The loader reads each line, validates characters, and ensures the maze is rectangular (all rows same width).

### Entrance detection
- Scans the entire outer border of the grid.
- Collects all open border cells (value 0).
- Requires exactly two openings; these are stored as:
    - start (row, col)
    - goal (row, col)

### Solving (DFS backtracking)
- Public API: bool solve(std::stack<Cell>& path)
- Explores neighbors in the fixed order: right, down, up, left.
- Uses a visited matrix to prevent revisiting cells.
- Backtracking mechanics:
    - Push current cell onto the path when entering it.
    - If all neighbors fail, pop it (backtrack).
- On success, the output stack contains the path with:
    - bottom = start
    - top = goal

### Output
- printRaw(): Prints the maze as '0' and '1'.
- printSolution(path): Prints the maze and overlays the solution path cells as a red '*' using ANSI escape codes.


## Testing & Status
The program is currently working as intended.