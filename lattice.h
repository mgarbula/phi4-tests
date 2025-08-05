#include <vector>
#include <fstream>
#include <iostream>
#include "cell.h"

class Lattice {
    public:
        Lattice(int);
        friend std::ostream& operator<<(std::ostream& str, Lattice const& l);
        void print_nums() {
            for (std::vector<Cell> row : this->lattice) {
                for (Cell el : row) {
                    std::cout << el.getNum() << " ";
                }
                std::cout << std::endl;
            }
        }
        void print_coronas(std::ostream& str) {
            for (int i = 0; i < this->size; i++) {
                for (int j = 0; j < this->size; j++) {
                    str << this->lattice[i][j].getCorona() << " ";
                }
                str << std::endl;
            }
        }
        void calculateCoronas();
    private:
        std::vector<std::vector<Cell>> lattice;
        int size;
        void corona_01(int, int);
        // int field(int, int);
        std::tuple<int, int, int, int> neighoburs_01(int, int);
};