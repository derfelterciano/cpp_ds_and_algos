#pragma once

#include <Maze.hpp>
#include <MazeSolver.hpp>
#include <ds/Vector.hpp>
#include <functional>

#define CELL_SIZE 24

// draw a maze, no animation needed
void visualize_maze(const Maze& maze);

// draw the maze generation with animation
void visualize_maze_generation(
    Maze&                                                        maze,
    std::function<void(Maze&, std::function<void(const Maze&)>)> generator = {},
    int start_row = 0, int start_col = 0);

// draw maze solving with animation
void visualize_maze_solving(
    Maze& maze, SolveMethod method,
    std::function<ds::Vector<vrtx>(const Maze&, SolveMethod,
                                   std::function<void(const vrtx&)>)>
        solve_fn = {});

// visualize solution path
void visualize_solution(const Maze& maze, const ds::Vector<vrtx>& path);
