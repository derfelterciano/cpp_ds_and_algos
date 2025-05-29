#pragma once

#include <functional>

#include "Maze.hpp"

void gen_maze_dfs(Maze& maze, int start_row = 0, int start_col = 0,
                  std::function<void(const Maze&)> on_step = {});
