#include "MazeGen.hpp"

#include <algorithm>
#include <ds/Stack.hpp>
#include <ds/Vector.hpp>
#include <random>
#include <utility>

namespace {

enum Wall { TOP, BOTTOM, RIGHT, LEFT };

struct Dir {
    int  dr, dc;
    Wall curr_wall, nbr_wall;
};

const ds::Vector<Dir> directions = {
    {-1, 0, TOP, BOTTOM},  // Up
    {1, 0, BOTTOM, TOP},   // Down
    {0, 1, RIGHT, LEFT},   // Right
    {0, -1, LEFT, RIGHT}   // Left
};

// Remove wall between two adjacent cells
inline void remove_wall(Cell& current, Cell& neighbor, Wall curr_wall,
                        Wall nbr_wall) {
    switch (curr_wall) {
        case TOP:
            current.top_wall = false;
            break;
        case BOTTOM:
            current.bottom_wall = false;
            break;
        case RIGHT:
            current.right_wall = false;
            break;
        case LEFT:
            current.left_wall = false;
            break;
    }

    switch (nbr_wall) {
        case TOP:
            neighbor.top_wall = false;
            break;
        case BOTTOM:
            neighbor.bottom_wall = false;
            break;
        case RIGHT:
            neighbor.right_wall = false;
            break;
        case LEFT:
            neighbor.left_wall = false;
            break;
    }
}

// get unvisted neighbor directions from (r, c)
ds::Vector<Dir> get_unvisited_dirs(const Maze&                         maze,
                                   const ds::Vector<ds::Vector<bool>>& visited,
                                   int r, int c) {
    ds::Vector<Dir> out;

    for (const auto& dir : directions) {
        int nr = r + dir.dr, nc = c + dir.dc;
        if (maze.in_bounds(nr, nc) && !visited[nr][nc]) {
            out.push_back(dir);
        }
    }

    return out;
}

// pick random item from vector (pick random direction)
template <typename T>
const T& pick_random(const ds::Vector<T>& vec, std::mt19937& rng) {
    if (vec.is_empty()) {
        throw std::runtime_error("[pick_random()] Can't pick from an empty vector!");
    }

    std::uniform_int_distribution<std::size_t> dist(0, vec.len() - 1);
    return vec[dist(rng)];
}

};  // namespace

void gen_maze_dfs(Maze& maze, int start_row, int start_col) {
    int rows = maze.rows(), cols = maze.cols();
    maze.reset();

    ds::Stack<std::pair<int, int>> stack;
    ds::Vector<ds::Vector<bool>>   visited(rows, ds::Vector<bool>(cols, false));
    std::random_device             rd;
    std::mt19937                   rng(rd());

    stack.push({start_row, start_col});
    visited[start_row][start_col] = true;

    while (!stack.is_empty()) {
        auto [r, c]    = stack.top();
        auto unvisited = get_unvisited_dirs(maze, visited, r, c);

        if (!unvisited.is_empty()) {
            const Dir& dir = pick_random(unvisited, rng);
            int        nr = r + dir.dr, nc = c + dir.dc;

            remove_wall(maze.cell(r, c), maze.cell(nr, nc), dir.curr_wall,
                        dir.nbr_wall);

            visited[nr][nc] = true;
            stack.push({nr, nc});
        } else {
            stack.pop();
        }
    }
}
