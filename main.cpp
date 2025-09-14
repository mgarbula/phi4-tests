#include <iostream>
#include <fstream>
#include <chrono>
#include "lattice.h"
#include <omp.h>

#include <math.h>

// #define SIZE 1000 // lattice size
#define ITERS 5

int main(int argc, char **argv) {
    // std::ofstream coronasFile;
    // std::string coronasDirectory = "/hac/storage/mgarbula/phi4-pliki/";
    // std::string coronasFileName;
    int SIZE = atoi(std::getenv("SIZE"));
    int chunkSize;
    int threadNum = 1;
    #ifdef _OPENMP
        threadNum = atoi(std::getenv("OMP_NUM_THREADS"));
        std::cout << "using number of threads: " << std::getenv("OMP_NUM_THREADS") << std::endl;
        chunkSize = int(SIZE / (2 * atoi(std::getenv("OMP_NUM_THREADS"))));
        // coronasFileName = "coronas_openmp_simd.txt";
    #else
        chunkSize = 0;
        // coronasFileName = "coronas_simd.txt";
    #endif
    // coronasFile.open(coronasDirectory + coronasFileName);

    std::string plotFileName;
    std::ofstream plotFile;
    if (argc == 2) {
        plotFileName = argv[1];
        plotFile.open(plotFileName, std::ios::app);
        plotFile << threadNum << ";";
    }

    auto sum = 0;
    std::cout << "Initialization of lattice ...\n";
    // auto size = sqrt(SIZE * SIZE * atoi(std::getenv("OMP_NUM_THREADS")));
    // chunkSize = int(size / (2 * atoi(std::getenv("OMP_NUM_THREADS"))));
    // Lattice l(size, chunkSize);
    Lattice l(SIZE, chunkSize);
    std::cout << "Lattice initialized.\nCalculate coronas " << ITERS << " times\n";

    std::cout << "chunkSize = " << chunkSize << std::endl;

    for (int i = 0; i < ITERS; i++) {
        auto t1 = std::chrono::high_resolution_clock::now();
        l.calculateCoronas(chunkSize);
        auto t2 = std::chrono::high_resolution_clock::now();
        auto ms_int = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
        std::cout << ms_int.count() << std::endl;
        if (argc == 2) {
            plotFile << ms_int.count() << ";";
        }
        sum += ms_int.count();
    }
    auto avg_time = sum / ITERS;
    if (argc == 2) {
        plotFile << avg_time << ";" << (avg_time * threadNum) << ";\n";
        plotFile.close();
    }
    std::cout << "avg_time = " << avg_time << std::endl;
    // std::cout << "Printing to file...\n";
    // l.print_coronas(coronasFile);
}