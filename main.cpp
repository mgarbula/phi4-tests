#include <iostream>
#include <fstream>
#include <chrono>
#include "lattice.h"
#include <omp.h>

#define SIZE 10000 // lattice size
#define ITERS 5

int main() {
    // std::ofstream coronasFile;
    // std::string coronasDirectory = "/hac/storage/mgarbula/phi4-pliki/";
    // std::string coronasFileName;
    int chunkSize;
    #ifdef _OPENMP
        std::cout << "using number of threads: " << std::getenv("OMP_NUM_THREADS") << std::endl;
        chunkSize = int(SIZE / (2 * atoi(std::getenv("OMP_NUM_THREADS"))));
        // coronasFileName = "coronas_openmp.txt";
    #else
        chunkSize = 0;
        // coronasFileName = "coronas.txt";
    #endif
    // coronasFile.open(coronasDirectory + coronasFileName);

    auto sum = 0;
    std::cout << "Initialization of lattice ...\n";
    Lattice l(SIZE, chunkSize);
    std::cout << "Lattice initialized.\nCalculate coronas " << ITERS << " times\n";

    std::cout << "chunkSize = " << chunkSize << std::endl;

    for (int i = 0; i < ITERS; i++) {
        auto t1 = std::chrono::high_resolution_clock::now();
        l.calculateCoronas(chunkSize);
        auto t2 = std::chrono::high_resolution_clock::now();
        auto ms_int = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
        std::cout << ms_int.count() << std::endl;
        sum += ms_int.count();
    }
    auto avg_time = sum / ITERS;

    std::cout << "avg_time = " << avg_time << std::endl;
    // std::cout << "Printing to file...\n";
    // l.print_coronas(coronasFile);
}