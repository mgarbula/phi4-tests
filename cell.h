#include <fstream>

class Cell {
    public:
        /**
         * Constructs cell with value and number of lattice element
         * @param int v - value
         * @param int s - lattice element
         */
        Cell(int v, int s) : value(v), subNum(s), corona01(0) {}
        Cell(const Cell& c) : value(c.value), subNum(c.subNum) {}
        Cell& operator=(const Cell& c) {
            if (this != &c) {
                value = c.value;
                subNum = c.subNum;
            }
            return *this;
        }

        int getValue() { return this->value; }
        int getNum() { return this->subNum; }
        int getCorona() { return this->corona01; }
        void setCorona01(int c) { this->corona01 = c; }
        friend std::ostream& operator<<(std::ostream& str, Cell const& c) {
            str << c.value;
            return str;
        }
    private:
        int value;
        int corona01;
        int subNum;
};