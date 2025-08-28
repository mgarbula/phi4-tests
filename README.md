# PHI4 test

For now not much a phi4 model. Currently it calculates c01 (corona01). Lattice is initialized with the same numbers for testing. Field is calculated as a simple sum.

Current implementation aim was to remind C++ and OMP.
Current version runs `calculateCoronas()` 5 times and calculates avg time.

## Run

First run single threaded version
```bash
g++ -o main *.cpp
./main
```
You'll see the information about time of calculating `calculateCoronas()` function.

Then run with OMP
```bash
export OMP_NUM_THREADS=8
g++ -o main -fopenmp *.cpp
./main
```
Same here, you'll see time.

For OMP version set those variables for best performance
```
export OMP_PLACES=cores
export OMP_PROC_BIND=close
```

Coronas are printed into the file (currently commented out). To see if one-threaded and OMP version calculate it as the same run
```bash
diff coronas.txt coronas_openmp.txt
```
Contents of the files should be the same.

## Testing
There is testing script `run.sh` prepared. It runs program on 
2, 4, 5, 8, 10, 15, 16, 17, 20, 23, 25, 30 and 32 threads.
It was tested on machine with 2 sockets, each with 16 threads (32 hyperthreads).

To run use
```
chmod +x run.sh
./run.sh
```
