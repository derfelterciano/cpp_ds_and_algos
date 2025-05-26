#include "Maze.hpp"

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
