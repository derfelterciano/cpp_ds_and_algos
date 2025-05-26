#include "Maze.hpp"

#include <fstream>
#include <ios>
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>

#include "ds/Vector.hpp"

// constructors

Maze::Maze(int rows, int cols)
    : m_rows(rows), m_cols(cols), grid(std::size_t(rows)) {
    // initalize cols
    for (auto& c : grid) {
        c = ds::Vector<Cell>(std::size_t(cols));
    }

    m_start = {0, 0};
    m_end   = {rows - 1, cols - 1};
}

Maze::Maze() : m_rows(0), m_cols(0), grid() {
    m_start = {0, 0};
    m_end   = {0, 0};
}

// accessors

const Cell& Maze::cell(int row, int col) const {
    if (!in_bounds(row, col)) {
        throw std::out_of_range("[Maze::cell()] Cell indices out of range!");
    }

    return grid[row][col];
}

Cell& Maze::cell(int row, int col) {
    if (!in_bounds(row, col)) {
        throw std::out_of_range("[Maze::cell()] Cell indices out of range!");
    }

    return grid[row][col];
}

// bounds

bool Maze::in_bounds(int row, int col) const {
    return row >= 0 && row < rows() && col >= 0 && col < cols();
}

// set start and end

void Maze::set_start(int row, int col) {
    if (!in_bounds(row, col))
        throw std::out_of_range("[Maze::set_start()] Start cell out of bounds");

    m_start = {row, col};
}

void Maze::set_end(int row, int col) {
    if (!in_bounds(row, col))
        throw std::out_of_range("[Maze::set_end()] End cell out of bounds");

    m_end = {row, col};
}

// reset

void Maze::reset() {
    for (std::size_t i = 0; i < rows(); ++i) {
        for (std::size_t j = 0; j < cols(); ++j) {
            grid[i][j] = Cell();
        }
    }

    m_start = {0, 0};
    m_end   = {m_rows - 1, m_cols - 1};
}

// serialization

void Maze::save(const std::string& fp) const {
    std::ofstream out(fp);
    if (!out) throw std::runtime_error("Cannot open file: " + fp);

    // maze meta info
    out << m_rows << " " << m_cols << "\n";
    out << m_start.first << " " << m_start.second << "\n";
    out << m_end.first << " " << m_end.second << "\n";

    for (int i = 0; i < rows(); ++i) {
        for (int j = 0; j < cols(); ++j) {
            const Cell& c = cell(i, j);

            out << (c.top_wall ? "1" : "0");
            out << (c.bottom_wall ? "1" : "0");
            out << (c.right_wall ? "1" : "0");
            out << (c.left_wall ? "1" : "0");

            if (j < m_cols - 1) out << " ";
        }
        out << "\n";
    }
}

void Maze::load(const std::string& fp) {
    std::ifstream in(fp);
    if (!in) throw std::runtime_error("[Maze::load()] Cannot open file: " + fp);

    int rows, cols;
    in >> rows >> cols;
    if (!in)
        throw std::runtime_error(
            "[Maze::load()] Invalid file format (rows/cols)");

    m_rows = rows;
    m_cols = cols;
    grid   = ds::Vector<ds::Vector<Cell>>(rows);
    for (auto& v : grid) {
        v = ds::Vector<Cell>(cols);
    }

    in >> m_start.first >> m_start.second;
    in >> m_end.first >> m_end.second;

    // consume new line

    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    for (int i = 0; i < rows; ++i) {
        std::string line;
        std::getline(in, line);
        if (!in)
            throw std::runtime_error(
                "[Maze::load() Unexpected EOL reading maze grid]");

        std::istringstream linestream(line);
        for (int j = 0; j < cols; ++j) {
            std::string cell_str;
            linestream >> cell_str;
            if (cell_str.size() != 4) {
                throw std::runtime_error(
                    "[Maze::load()] Invalid cell encoding at (" +
                    std::to_string(i) + ", " + std::to_string(j) + ")");
            }

            Cell& c       = grid[i][j];
            c.top_wall    = (cell_str[0] == '1');
            c.bottom_wall = (cell_str[1] == '1');
            c.right_wall  = (cell_str[2] == '1');
            c.left_wall   = (cell_str[3] == '1');
        }
    }
}
