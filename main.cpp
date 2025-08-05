#include <iostream>
#include <fstream>
#include <chrono>
#include "lattice.h"
#include <omp.h>

#define SIZE 10000 // lattice size

int main() {
    std::ofstream coronasFile;
    std::string coronasDirectory = "/hac/storage/mgarbula/phi4-pliki/";
    std::string coronasFileName;
    std::string pathToDir = 
    #ifdef _OPENMP
        std::cout << "using number of threads: " << std::getenv("OMP_NUM_THREADS") << std::endl;
        coronasFileName = "coronas_openmp.txt";
    #else
        coronasFileName = "coronas.txt";
    #endif
    coronasFile.open(coronasDirectory + coronasFileName);

    std::cout << "Initialization of lattice ...\n";
    Lattice l(SIZE);
    std::cout << "Lattice initialized.\nCalculate coronas\n";


    auto t1 = std::chrono::high_resolution_clock::now();
    l.calculateCoronas();
    auto t2 = std::chrono::high_resolution_clock::now();
    auto ms_int = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);

    #ifdef _OPENMP
        std::cout << "Duration of calculateCoronas() with OMP " << ms_int.count() << std::endl;
    #else
        std::cout << "Duration of calculateCoronas() with one thread " << ms_int.count() << std::endl;
    #endif
    std::cout << "Printing to file...\n";
    l.print_coronas(coronasFile);
    // l.print_nums();
    // printf("num = %d\n", l.lattice[3][5].getValue());
    // printf("cor = %d\n", l.lattice[3][5].getCorona());
}