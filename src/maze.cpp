#include "lib/Maze.hpp"

#include <iostream>
#include <string>

#include "cxxopts.hpp"
#include "lib/MazeGen.hpp"
#include "lib/MazeSolver.hpp"
#include "lib/Visualizer.hpp"

int main(int argc, char* argv[]) {
    try {
        cxxopts::Options options("Maze",
                                 "Generates, Solves, and Visualizes Mazes.");
        options.add_options()("g,generate", "Generate a maze.")(
            "s,solve", "Solve a maze.")(
            "rows", "Number of rows",
            cxxopts::value<int>()->default_value("20"))(
            "cols", "Number of cols",
            cxxopts::value<int>()->default_value("20"))(
            "i,input", "Input a maze file!", cxxopts::value<std::string>())(
            "o,output", "Output maze file", cxxopts::value<std::string>())(
            "solve-method", "Solve method (dfs,bfs,dijkstra [default: dfs])",
            cxxopts::value<std::string>()->default_value("dfs"))(
            "vg, visualize-gen", "Visualizes maze generation")(
            "vs,visual-solve", "Visualizes solving")("h,help", "Print usage");

        auto result = options.parse(argc, argv);
        if (result.count("help")) {
            std::cout << options.help() << std::endl;
            return 0;
        }

        Maze        maze;
        SolveMethod solve_method = SolveMethod::DFS;

        std::cerr << "No valid command provided. Use --help for usage."
                  << std::endl;
        return 1;
    } catch (const cxxopts::exceptions::exception& e) {
        std::cerr << "Error parsing options: " << e.what() << std::endl;
        return 1;
    }
}
