#include <vector>
#include <fstream>
#include <iostream>
#include "cell.h"

class Lattice {
    public:
        Lattice(int, int);
        friend std::ostream& operator<<(std::ostream& str, Lattice const& l);
        void print_nums() {
            for (int i = 0; i < this->size; i++) {
                for (int j = 0; j < this->size; j++) {
                    std::cout << this->lattice[i * size + j].getNum() << " ";
                }
                std::cout << std::endl;
            }
        }
        void print_coronas(std::ostream& str) {
            for (int i = 0; i < this->size; i++) {
                for (int j = 0; j < this->size; j++) {
                    str << this->lattice[i * size + j].getCorona() << " ";
                }
                str << std::endl;
            }
        }
        void calculateCoronas(int);
    private:
        std::vector<Cell> lattice;
        int size;
        void corona_01(int, int);
        // int field(int, int);
        std::tuple<int, int, int, int> neighoburs_01(int, int);
};
