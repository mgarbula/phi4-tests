#!/bin/bash

threads_nums=(2 4 5 8 10 15 16 17 20 23 25 30 32)

for num_threads in "${threads_nums[@]}"
do
    echo "Running with OMP_NUM_THREADS = $num_threads"
    export OMP_NUM_THREADS=$num_threads

    ./main
    echo "=================================="
done

echo "Run finished"