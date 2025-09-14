#include "lattice.h"
#include <random>
#include <chrono>
#include <tuple>
#include <omp.h>
#include <complex>
#include <math.h>

// std::vector<Cell> copy_for_15; // threads indexed from 0
// std::vector<Cell> copy_for_16;

inline int getIndex(int row, int col, int size) {
    return row * size + col;
}

/**
 * Generates random 2D vector (for now its always the same for testing)
 * @param int size - size int both dimensions
 */
Lattice::Lattice(int size, int chunkSize) {
    this->size = size;
    this->lattice.resize(size * size);

    int curr_elem = 0;
    #pragma omp parallel for schedule(static, chunkSize)
    for (int i = 0; i < size; i++) {
        const unsigned int fixedSeed = 12345;
        std::mt19937 rng(fixedSeed);
        std::uniform_real_distribution<double> dist(1, 10);
        for (int j = 0; j < size; j++) {
            curr_elem = (i + j) % 2;
            std::complex<double> z(dist(rng), dist(rng));
            this->lattice[getIndex(i, j, size)] = Cell(z, curr_elem);
        }
        if (!(size % 2)) {
            curr_elem += 1;
        }
    }
}

std::ostream& operator<<(std::ostream& str, Lattice const& l) {
    int size = sqrt(l.lattice.size());
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            str << l.lattice[getIndex(i, j, size)] << " ";
        }
        str << std::endl;
    }
    return str;
}

/**
 * Returns indexes of corona 01 neighbours at given position
 * @param int row
 * @param int column
 * @param int size of lattice
 * @return std::tuple<int, int, int, int> tuple of indexes (up, down, left, right)
 */
std::tuple<int, int, int, int> Lattice::neighoburs_01(int row, int column) {
    int up = row > 0 ? row - 1 : this->size - 1;
    int down = row < this->size - 1 ? row + 1 : 0;
    int left = column > 0 ? column - 1 : this->size - 1;
    int right = column < this->size - 1 ? column + 1 : 0;

    std::tuple<int, int, int, int> t;
    t = std::make_tuple(up, down, left, right);
    return t;
}

/**
 * Calculates corona 01 at given position
 * @param int row
 * @param int column
 */
// void Lattice::corona_01(int row, int column) {
//     std::tuple<int, int, int, int> ns = neighoburs_01(row, column);
//     std::complex<double> corona = 0;
//     int up = std::get<0>(ns);
//     int down = std::get<1>(ns);
//     int left = std::get<2>(ns);
//     int right = std::get<3>(ns);

//     std::complex<double> curr = this->lattice[row][column].getValue();
//     corona += this->lattice[row][left].getValue();
//     corona += this->lattice[row][right].getValue();
//     corona += this->lattice[up][column].getValue();
//     corona += this->lattice[up][column].getValue();
//     this->lattice[row][column].setCorona01(corona);
// }

void Lattice::calculateCoronas(int chunkSize) {
    int currNum = 0;
    int currEl = 0;
    while (currNum < 2) {
        #pragma omp parallel for schedule(static, chunkSize)
        for (int i = 0; i < this->size; i++) {
            // #pragma omp simd
            for (int j = currEl; j < this->size; j+=2) {
                int up = i > 0 ? i - 1 : this->size - 1;
                int down = i < this->size - 1 ? i + 1 : 0;
                int left = j > 0 ? j - 1 : this->size - 1;
                int right = j < this->size - 1 ? j + 1 : 0;

                std::complex<double> corona = \
                    this->lattice[getIndex(i, left, size)].getValue() \
                    + this->lattice[getIndex(i, right, size)].getValue() \
                    + this->lattice[getIndex(up, j, size)].getValue() \
                    + this->lattice[getIndex(down, j, size)].getValue();
                this->lattice[getIndex(i, j, size)].setCorona01(corona);
                if (j == this->size - 1) {
                    currEl = (currEl + 1) % 2;
                }
            }
        }
        currNum++;
    }
}