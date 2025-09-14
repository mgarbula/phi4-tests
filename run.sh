#!/bin/bash

export SIZE=10000;

FILE_NAME="plots/${SIZE}x${SIZE}_simd.csv"
PLOT_NAME="plots/${SIZE}x${SIZE}_simd.png"

touch $FILE_NAME
echo "thread_num;time_1;time_2;time_3;time_4;time_5;avg;avg*thread_num" >> $FILE_NAME

export OMP_PLACES=cores;
export OMP_PROC_BIND=close;
threads_nums=(1 2 4 5 8 10 15 16 17 20 23 25 30 32)

for num_threads in "${threads_nums[@]}"
do
    echo "Running with OMP_NUM_THREADS = $num_threads"
    export OMP_NUM_THREADS=$num_threads

    ./main $FILE_NAME
    echo "=================================="
done

echo "Run finished. Creating plot"

gnuplot << EOF
    set datafile separator ";"
    set terminal png size 800,600
    set output "$PLOT_NAME"
    set title "agvTime * threadsNum"
    set xlabel "threadsNum"
    set ylabel "total work"
    plot "$FILE_NAME" using 1:8 with points
EOF

echo "Plot created"