#ifndef GRID_H
#define GRID_H

#include <vector>
class Grid {
    private:
        unsigned m_nX;
        unsigned m_nY;
        double m_dX;
        double m_dY;

        std::vector<double> m_grid;

    public:
        Grid(unsigned nx, unsigned ny, double dx, double dy) :
            m_nX(nx), m_nY(ny), m_dX(dx), m_dY(dy),
            m_grid(nx * ny, 0.)
        {}

        // extention of grid in x direction (number of columns)
        unsigned nX() const noexcept
        { return m_nX; }
        // extention of grid in y direction (number of rows)
        unsigned nY() const noexcept
        { return m_nY; }

        // grid spacing in x direction
        double dX() const noexcept
        { return m_dX; }
        // grid spacing in y direction
        double dY() const noexcept
        { return m_dY; }


        // raw access to the underlying grid array
        const std::vector<double>& grid() const noexcept
        { return m_grid; }
        // raw access to the underlying grid array
        std::vector<double>& grid() noexcept
        { return m_grid; }
        
        // proxy class for a read-only row
        class ConstRow {
            protected:
                const Grid& m_grid;
                unsigned m_row;
            public:
                ConstRow(const Grid& grid, unsigned row) :
                    m_grid(grid), m_row(row)
                {}
                const double& operator[](unsigned col) const
                { return m_grid.grid()[m_row * m_grid.nX() + col]; }

                using const_iterator = const double*;
                using value_type = double;
                using const_reference = const double&;
                using size_type = unsigned;
                const_iterator begin() const noexcept
                { return &m_grid.grid()[m_row * m_grid.nX()]; }
                const_iterator end() const noexcept
                { return &m_grid.grid()[(m_row + 1) * m_grid.nX()]; }
        };
        // proxy class for a row
        class Row : public ConstRow {
            public:
                Row(Grid& grid, unsigned row) : ConstRow(grid, row) {}
                Row(const Row& other) : ConstRow(other) {}

                double& operator[](unsigned col)
                {
                    return const_cast<double&>(ConstRow::operator[](col));
                }
                using iterator = double*;
                using reference = double&;
                iterator begin() noexcept
                { return &const_cast<double&>(m_grid.grid()[m_row * m_grid.nX()]); }
                iterator end() noexcept
                { return &const_cast<double&>(m_grid.grid()[(m_row + 1) * m_grid.nX()]); }
        };

        // return a row (read-write)
        Row operator[](unsigned i)
        { return Row(*this, i); }
        // return a row (read-only)
        ConstRow operator[](unsigned i) const
        { return ConstRow(*this, i); }
        
        using size_type = unsigned;
        using value_type = Row;
        class const_iterator {
            protected:
                const Grid& m_grid;
                unsigned m_row;
            public:
                const_iterator(const Grid& grid, unsigned row) :
                        m_grid(grid), m_row(row)
                {}
                ConstRow operator*() const
                { return ConstRow(m_grid, m_row); }
                const_iterator& operator++()
                { ++m_row; return *this; }
                const_iterator operator++(int)
                { const_iterator retVal(*this); ++m_row; return retVal; }
                const_iterator& operator--()
                { --m_row; return *this; }
                const_iterator operator--(int)
                { const_iterator retVal(*this); --m_row; return retVal; }
        };
        class iterator : public const_iterator {
            public:
                iterator(Grid& grid, unsigned row) :
                        const_iterator(grid, row)
                {}
                Row operator*()
                { return Row(const_cast<Grid&>(m_grid), m_row); }
                iterator& operator++()
                { ++m_row; return *this; }
                iterator operator++(int)
                { iterator retVal(*this); ++m_row; return retVal; }
                iterator& operator--()
                { --m_row; return *this; }
                iterator operator--(int)
                { iterator retVal(*this); --m_row; return retVal; }
        };
        const_iterator begin() const { return const_iterator(*this, 0); }
        iterator begin() { return iterator(*this, 0); }
        const_iterator end() const { return const_iterator(*this, nY()); }
        iterator end() { return iterator(*this, nY()); }
};

#endif // GRID_H

// vim: sw=4:tw=76:et:ft=cpp 
