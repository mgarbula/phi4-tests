# PHI4 test

For now not much a phi4 model. Currently it calculates c01 (corona01). Lattice is initialized with the same numbers for testing. Field is calculated as a simple sum.

Current implementation aim was to remind C++ and OMP.

## Run
First run the program like this
```bash
g++ -o main *.cpp
./main
```
You'll see the information about time of calculating `calculateCoronas()` function with one thread (on my machine around 20k ms).

Then run with OMP
```bash
export OMP_NUM_THREADS=8
g++ -o main -fopenmp *.cpp
./main
```
Same here, you'll see time (on my machine around 7k ms).

Coronas are printed into the file. To see if one-threaded and OMP version calculate it as the same run
```bash
diff coronas.txt coronas_openmp.txt
```
Contents of the files should be the same.