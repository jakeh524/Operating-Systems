#! /usr/local/bin/gnuplot
#
# purpose:
#	 generate data reduction graphs for the multi-threaded list project
#
# input: lab2b_list.csv
#	1. test name
#	2. # threads
#	3. # iterations per thread
#	4. # lists
#	5. # operations performed (threads x iterations x (ins + lookup + delete))
#	6. run time (ns)
#	7. run time per operation (ns)
#
# output:
#	lab2b_1.png ... threads vs throughput for m and s

# general plot parameters
set terminal png
set datafile separator ","

# number of threads and throughput for mutex and spin-lock
set title "List-1: Number of Threads vs Throughput"
set xlabel "Number of Threads"
set logscale x 2
set xrang [0.75:32]
set ylabel "Throughput (ns)"
set logscale y 10
set output 'lab2b_1.png'

# grep out only mutex and spin-lock, 1000 iterations, non-yield, un-partitioned results
plot \
     "< grep -e 'list-none-m,[0-9]*,1000,1,' lab2b_list.csv" using ($2):(1000000000)/($7) \
	title 'mutex' with linespoints lc rgb 'red', \
     "< grep -e 'list-none-s,[0-9]*,1000,1,' lab2b_list.csv" using ($2):(1000000000)/($7) \
	title 'spin-lock' with linespoints lc rgb 'green'
 
 # number of threads and wait-for-lock and avg op time for mutex
 set title "List-2: Number of Threads vs Operation and Wait-For-Lock Time"
 set xlabel "Number of Threads"
 set logscale x 2
 set xrang [0.75:32]
 set ylabel "Operation Time (ns)"
 set logscale y 10
 set output 'lab2b_2.png'

 # grep out only mutex, 1000 iterations, non-yield, un-partitioned results
 plot \
      "< grep -e 'list-none-m,[0-9]*,1000,1,' lab2b_list.csv" using ($2):($7) \
     title 'average operation time' with linespoints lc rgb 'red', \
      "< grep -e 'list-none-m,[0-9]*,1000,1,' lab2b_list.csv" using ($2):($8) \
     title 'wait-for-lock time' with linespoints lc rgb 'blue'
