#pragma once

#include <ds/Vector.hpp>
#include <functional>
#include <Maze.hpp>
#include <MazeSolver.hpp>

#define CELL_SIZE 24
#define ANIMATION_DELAY 20

// draw a maze, no animation needed
void visualize_maze(const Maze& maze);

// draw the maze generation with animation
void visualize_maze_generation(
    Maze&                                                        maze,
    std::function<void(Maze&, std::function<void(const Maze&)>)> generator = {},
    int start_row = 0, int start_col = 0);

// draw maze solving with animation
ds::Vector<vrtx> visualize_maze_solving(
    Maze& maze, SolveMethod method,
    std::function<ds::Vector<vrtx>(const Maze&, SolveMethod,
                                   std::function<void(const vrtx&)>)>
        solve_fn = {});
