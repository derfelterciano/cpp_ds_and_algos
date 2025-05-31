#include <ds/Vector.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>

#include "cxxopts.hpp"
#include "lib/Maze.hpp"
#include "lib/MazeGen.hpp"
#include "lib/MazeSolver.hpp"
#include "lib/Visualizer.hpp"

namespace {
std::string print_path(const ds::Vector<vrtx>& vec) {
    std::ostringstream oss;
    oss << "[";
    for (std::size_t i = 0; i < vec.len(); ++i) {
        const vrtx pair = vec[i];
        oss << "(" << pair.first << ", " << pair.second << ")";
        if (i + 1 < vec.len()) oss << ", ";
    }
    oss << "]";
    return oss.str();
}

};  // namespace

int main(int argc, char* argv[]) {
    /*
    Maze        maze;
    SolveMethod solve_method = SolveMethod::DFS;
    maze.load("/Users/dterciano/Desktop/GitRepos/cpp_ds_and_algos/out.maze");
    std::cout << "Maze loaded!" << std::endl;
    auto path = solve_maze(maze, solve_method);
    std::cout << "Maze path length: " << path.len() << std::endl;

    std::cout << "path: " << print_path(path) << std::endl;
    */
    Maze maze{20, 20};
    visualize_maze_generation(maze);

    // gen_maze_dfs(maze);
    //
    // visualize_maze(maze);

    return 0;
}
