#include "Maze.h"
#include<iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>
#include <stack>


bool Maze::inBounds(int r, int c) const {
    return r >= 0 && c >= 0 && r < rows() && c < cols();
}

bool Maze::isOpen(int r, int c) const {
    return inBounds(r, c) && grid[r][c] == 0;
}

// DFS helper: Right, Down, Up, Left
bool Maze::dfs(int r, int c, std::stack<Cell>& path, std::vector<std::vector<bool>>& visited) {
    visited[r][c] = true;
    path.push({r, c});

    if (r == goal.r && c == goal.c) {
        return true; // found goal
    }

    // Explore neighbors in desired order
    // I chose Right, Down, Up, Left.
    const int dr[4] = { 0,  1, -1,  0};
    const int dc[4] = { 1,  0,  0, -1};

    for (int k = 0; k < 4; ++k) {
        int nr = r + dr[k];
        int nc = c + dc[k];
        if (isOpen(nr, nc) && !visited[nr][nc]) {
            if (dfs(nr, nc, path, visited)) {
                return true;
            }
        }
    }
    // backtrack if no neighbor leads to goal
    path.pop();
    return false;
}

//Solver method that utilizes DFS function using algorithm described
//in the assignment. Accepts a pointer to a stack of Cells to be used as the
//solution path if there is one.
bool Maze::solve(std::stack<Cell>& path) {

    const int R = rows();
    const int C = cols();
    if (R == 0 || C == 0) return false;

    // Minimal checks (you can expand later if you wish)
    if (!inBounds(start.r, start.c) || !inBounds(goal.r, goal.c)) return false;
    if (!isOpen(start.r, start.c) || !isOpen(goal.r, goal.c)) return false;

    std::vector<std::vector<bool>> visited(R, std::vector<bool>(C, false));
    return dfs(start.r, start.c, path, visited);
}

// Print maze overlaying the solution path with red '*'
// Assumes 'path' only contains valid cells within the maze.
void Maze::printSolution(const std::stack<Cell>& path) const {
    const int R = rows();
    const int C = cols();

    // Build a mask of path cells (copy the stack to iterate without modifying caller)
    std::vector<std::vector<bool>> onPath(R, std::vector<bool>(C, false));
    std::stack<Cell> copy = path;
    while (!copy.empty()) {
        Cell p = copy.top();
        copy.pop();
        onPath[p.r][p.c] = true; // no defensive bounds checks by design
    }

    // ANSI escape sequences for red and reset
    constexpr const char* RED = "\x1b[31m";
    constexpr const char* RESET = "\x1b[0m";

    for (int r = 0; r < R; ++r) {
        for (int c = 0; c < C; ++c) {
            if (onPath[r][c]) {
                std::cout << RED << '*' << RESET;
            } else {
                std::cout << (grid[r][c] ? '1' : '0');
            }
        }
        std::cout << '\n';
    }
}


bool Maze::loadFromFile(const std::string& path) {
    std::ifstream in(path);
    if (!in) {
        std::cerr << "Failed to open: " << path << std::endl;
        return false;
    }

    std::vector<std::vector<int>> tmp;
    std::string line;
    std::size_t width = 0;

    while (std::getline(in, line)) {
        if (line.empty()) continue;

        std::vector<int> row;
        row.reserve(line.size());
        for (char ch : line) {
            if (ch == '0') row.push_back(0);
            else if (ch == '1') row.push_back(1);
            else {
                std::cerr << "Invalid character in maze file: '" << ch << "'\n";
                return false;
            }
        }

        if (row.empty()) continue;

        if (width == 0) width = row.size();
        if (row.size() != width) {
            std::cerr << "Non-rectangular maze: row width mismatch\n";
            return false;
        }

        tmp.push_back(std::move(row));
    }

    if (tmp.empty()) {
        std::cerr << "Empty maze file\n";
        return false;
    }

    grid = std::move(tmp);
    return true;
}

void Maze::printRaw() const {
    for (const auto& row : grid) {
        for (int v : row) {
            std::cout << (v ? '1' : '0');
        }
        std::cout << '\n';
    }
}

bool Maze::detectEntrances() {
    if (grid.empty()) return false;
    const int R = static_cast<int>(grid.size());
    const int C = static_cast<int>(grid[0].size());

    std::vector<Cell> openings;

    auto maybeAdd = [&](int r, int c) {
        if (r >= 0 && c >= 0 && r < R && c < C && grid[r][c] == 0) {
            openings.push_back({r, c});
        }
    };

    // Top and bottom rows
    for (int c = 0; c < C; ++c) {
        maybeAdd(0, c);
        maybeAdd(R - 1, c);
    }
    // Left and right columns (avoid duplicating corners)
    for (int r = 1; r < R - 1; ++r) {
        maybeAdd(r, 0);
        maybeAdd(r, C - 1);
    }

    if (openings.size() != 2) {
        start = {-1, -1};
        goal = {-1, -1};
        return false;
    }
    start = openings[0];
    goal  = openings[1];
    return true;
}

