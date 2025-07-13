#include "lattice.h"
#include <random>
#include <chrono>
#include <tuple>
#include <omp.h>

/**
 * Generates random 2D vector (for now its always the same for testing)
 * @param int size - size int both dimensions
 */
Lattice::Lattice(int size) {
    this->size = size;
    this->lattice.resize(size);

    const unsigned int fixedSeed = 12345;
    std::mt19937 rng(fixedSeed);
    std::uniform_int_distribution<int> dist(1, 10);

    int curr_elem = 0;
    for (int i = 0; i < size; i++) {
        this->lattice[i].reserve(size);
        for (int j = 0; j < size; j++) {
            curr_elem = (curr_elem + 1) % 2;
            this->lattice[i].emplace_back(dist(rng), curr_elem);
        }
        if (!(size % 2)) {
            curr_elem += 1;
        }
    }
}

std::ostream& operator<<(std::ostream& str, Lattice const& l) {
    for (const auto& row : l.lattice) {
        for (const auto& el : row) {
            str << el << " ";
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

int Lattice::field(int x, int a) {
    return x + a;
}

// for now dummy calculation to see if paralelization works
// result is 8 * curr
// TODO: calculate field properly
/**
 * Calculates corona 01 at given position
 * @param int row
 * @param int column
 */
void Lattice::corona_01(int row, int column) {
    std::tuple<int, int, int, int> ns = neighoburs_01(row, column);
    int corona = 0;
    int up = std::get<0>(ns);
    int down = std::get<1>(ns);
    int left = std::get<2>(ns);
    int right = std::get<3>(ns);

    int curr = this->lattice[row][column].getValue();
    corona += (field(curr, up) + field(curr, -up));
    corona += (field(curr, down) + field(curr, -down));
    corona += (field(curr, left) + field(curr, -left));
    corona += (field(curr, right) + field(curr, -right));
    this->lattice[row][column].setCorona01(corona);
}

void Lattice::calculateCoronas() {
    int currNum = 0;
    int currEl = 0;
    while (currNum < 2) {
        for (int i = 0; i < this->size; i++) {
            #pragma omp parallel for schedule(static, 10)
            for (int j = currEl; j < this->size; j+=2) {
                this->corona_01(i, j);
            }
            currEl = (currEl + 1) % 2;
        }
        currNum++;
    }
}