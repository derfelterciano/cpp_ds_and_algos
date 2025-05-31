#include "lib/Maze.hpp"

#include <ds/Vector.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>

#include "cxxopts.hpp"
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
            "G, visualize-gen", "Visualizes maze generation")(
            "S,visual-solve", "Visualizes solving")("h,help", "Print usage");

        auto result = options.parse(argc, argv);
        if (result.count("help")) {
            std::cout << options.help() << std::endl;
            return 0;
        }

        Maze        maze;
        SolveMethod solve_method = SolveMethod::DFS;

        if (result.count("solve-method")) {
            auto m = result["solve-method"].as<std::string>();
            if (m == "dfs") {
                solve_method = SolveMethod::DFS;
            } else if (m == "bfs") {
                solve_method = SolveMethod::BFS;
            } else if (m == "dijkstra") {
                solve_method = SolveMethod::DIJKSTRA;
            } else {
                std::cerr << "Unknown solve method: " << m << std::endl;
                return 1;
            }
        }

        if (result.count("generate")) {
            int rows = result["rows"].as<int>();
            int cols = result["cols"].as<int>();
            maze     = Maze(rows, cols);
            gen_maze_dfs(maze);

            if (!result.count("output")) {
                std::cerr << "Error: --output must be specified!" << std::endl;
                return 1;
            }

            maze.save(result["output"].as<std::string>());
            std::cout << "Maze generates with : (" << rows << " Rows x " << cols
                      << " Cols)! \nFile saved at: "
                      << result["output"].as<std::string>() << std::endl;

            return 0;
        }

        if (result.count("solve")) {
            if (!result.count("input")) {
                std::cerr << "Error: --input file must be specified"
                          << std::endl;
            }
            maze.load(result["input"].as<std::string>());
            std::cout << "Maze loaded!" << std::endl;
            auto path = solve_maze(maze, solve_method);
            std::cout << "Maze path length: " << path.len() << std::endl;

            std::cout << "path: " << print_path(path) << std::endl;
            return 0;
        }

        if (result.count("visualize-gen")) {
            maze = Maze(20, 20);
            gen_maze_dfs(maze);

            visualize_maze(maze);

            return 0;
        }

        std::cerr << "No valid command provided. Use --help for usage."
                  << std::endl;
        return 1;
    } catch (const cxxopts::exceptions::exception& e) {
        std::cerr << "Error parsing options: " << e.what() << std::endl;
        return 1;
    }
}
