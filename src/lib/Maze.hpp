#pragma once

#include <ds/Vector.hpp>
#include <string>
#include <utility>

/// Cell representation
struct Cell {
    bool top_wall    = true;
    bool bottom_wall = true;
    bool right_wall  = true;
    bool left_wall   = true;

    /// whether or not we visited the cell
    bool visited = false;
};

class Maze {
   private:
    int                          m_rows = 0;
    int                          m_cols = 0;
    ds::Vector<ds::Vector<Cell>> grid;

    std::pair<int, int> m_start = {0, 0};
    std::pair<int, int> m_end   = {0, 0};

   public:
    // c-tor

    Maze(int rows, int cols);
    Maze();

    // accessors

    int rows() const {
        return m_rows;
    }
    int cols() const {
        return m_cols;
    }
    const Cell& cell(int row, int col) const;
    Cell&       cell(int row, int col);

    // serialization

    void save(const std::string& fp) const;
    void load(const std::string& fp);

    // start and end points

    void set_start(int row, int col);
    void set_end(int row, int col);

    std::pair<int, int> get_start() const {
        return m_start;
    }
    std::pair<int, int> get_end() const {
        return m_end;
    }

    // clear maze

    void reset();

    // maze info

    bool in_bounds(int row, int col) const;
};
