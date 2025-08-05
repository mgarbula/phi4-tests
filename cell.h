#include <fstream>
#include <complex>

class Cell {
    public:
        /**
         * Constructs cell with value and number of lattice element
         * @param int v - value
         * @param int s - lattice element
         */
        Cell(std::complex<double> v, std::complex<double> s) : value(v), subNum(s), corona01(0) {}
        Cell(const Cell& c) : value(c.value), subNum(c.subNum) {}
        Cell& operator=(const Cell& c) {
            if (this != &c) {
                value = c.value;
                subNum = c.subNum;
            }
            return *this;
        }

        std::complex<double> getValue() { return this->value; }
        std::complex<double> getNum() { return this->subNum; }
        std::complex<double> getCorona() { return this->corona01; }
        void setCorona01(std::complex<double> c) { this->corona01 = c; }
        friend std::ostream& operator<<(std::ostream& str, Cell const& c) {
            str << c.value;
            return str;
        }
    private:
        std::complex<double> value;
        std::complex<double> corona01;
        std::complex<double> subNum;
};