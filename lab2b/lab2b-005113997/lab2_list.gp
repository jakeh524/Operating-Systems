#! /usr/bin/gnuplot
#
# Jake Herron
# 005113997
# jakeh524@gmail.com
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
#   8. avg wait-for-lock time (ns)
#
# output:
#	lab2b_1.png ... threads vs throughput for m and s

# general plot parameters
set terminal png
set datafile separator ","

# number of threads and throughput for mutex and spin-lock
set title "Number of Threads vs Throughput"
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


# sync options that run without failure with sublists
set title "List-3: Iterations that run without failure for sublists"
set xlabel "Number of Threads"
set logscale x 2
set xrange [0.75:24]
set ylabel "Successful Iterations"
set logscale y 10
set output 'lab2b_3.png'
plot \
    "< grep -e 'list-id-none,[0-9]*,[0-9]*,4,' lab2b_list.csv" using ($2):($3) \
    with points lc rgb "red" title "unprotected", \
    "< grep -e 'list-id-m,[0-9]*,[0-9]*,4,' lab2b_list.csv" using ($2):($3) \
    with points lc rgb "blue" title "mutex", \
    "< grep 'list-id-s,[0-9]*,[0-9]*,4,' lab2b_list.csv" using ($2):($3) \
    with points lc rgb "green" title "spin-lock", \
    

# number of threads and throughput for mutex for sublists
set title "Number of Threads vs Throughput For Sublists With Mutex"
set xlabel "Number of Threads"
set logscale x 2
set xrang [0.75:32]
set ylabel "Throughput (ns)"
set logscale y 10
set output 'lab2b_4.png'

# grep out only mutex, 1000 iterations, non-yield, partitioned results
plot \
     "< grep -e 'list-none-m,[0-9]*,1000,1,' lab2b_list.csv" using ($2):(1000000000)/($7) \
    title 'lists=1' with linespoints lc rgb 'red', \
     "< grep -e 'list-none-m,[0-9]*,1000,4,' lab2b_list.csv" using ($2):(1000000000)/($7) \
    title 'lists=4' with linespoints lc rgb 'green', \
    "< grep -e 'list-none-m,[0-9]*,1000,8,' lab2b_list.csv" using ($2):(1000000000)/($7) \
    title 'lists=8' with linespoints lc rgb 'blue', \
     "< grep -e 'list-none-m,[0-9]*,1000,16,' lab2b_list.csv" using ($2):(1000000000)/($7) \
    title 'lists=16' with linespoints lc rgb 'violet'
    
 
 # number of threads and throughput for spin locks for sublists
 set title "Number of Threads vs Throughput For Sublists With Spin Lock"
 set xlabel "Number of Threads"
 set logscale x 2
 set xrang [0.75:32]
 set ylabel "Throughput (ns)"
 set logscale y 10
 set output 'lab2b_5.png'

 # grep out only spin lock, 1000 iterations, non-yield, partitioned results
 plot \
      "< grep -e 'list-none-s,[0-9]*,1000,1,' lab2b_list.csv" using ($2):(1000000000)/($7) \
     title 'lists=1' with linespoints lc rgb 'red', \
      "< grep -e 'list-none-s,[0-9]*,1000,4,' lab2b_list.csv" using ($2):(1000000000)/($7) \
     title 'lists=4' with linespoints lc rgb 'green', \
     "< grep -e 'list-none-s,[0-9]*,1000,8,' lab2b_list.csv" using ($2):(1000000000)/($7) \
     title 'lists=8' with linespoints lc rgb 'blue', \
      "< grep -e 'list-none-s,[0-9]*,1000,16,' lab2b_list.csv" using ($2):(1000000000)/($7) \
     title 'lists=16' with linespoints lc rgb 'violet'

