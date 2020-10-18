# Jake Herron
# 005113997
# jakeh524@gmail.com

default: lab2_list.c SortedList.h SortedList.c
	gcc -Wall -Wextra -g -lpthread -lprofiler lab2_list.c SortedList.c -o lab2_list

tests:
	# mutex
	./lab2_list --iterations=1000 --threads=1 --sync=m >> lab2b_list.csv
	./lab2_list --iterations=1000 --threads=2 --sync=m >> lab2b_list.csv
	./lab2_list --iterations=1000 --threads=4 --sync=m >> lab2b_list.csv
	./lab2_list --iterations=1000 --threads=8 --sync=m >> lab2b_list.csv
	./lab2_list --iterations=1000 --threads=12 --sync=m >> lab2b_list.csv
	./lab2_list --iterations=1000 --threads=16 --sync=m >> lab2b_list.csv
	./lab2_list --iterations=1000 --threads=24 --sync=m >> lab2b_list.csv
	
	# spin lock
	./lab2_list --iterations=1000 --threads=1 --sync=s >> lab2b_list.csv
	./lab2_list --iterations=1000 --threads=2 --sync=s >> lab2b_list.csv
	./lab2_list --iterations=1000 --threads=4 --sync=s >> lab2b_list.csv
	./lab2_list --iterations=1000 --threads=8 --sync=s >> lab2b_list.csv
	./lab2_list --iterations=1000 --threads=12 --sync=s >> lab2b_list.csv
	./lab2_list --iterations=1000 --threads=16 --sync=s >> lab2b_list.csv
	./lab2_list --iterations=1000 --threads=24 --sync=s >> lab2b_list.csv

profile: default
	LD_PRELOAD=/u/cs/ugrad/herron/lib/libprofiler.so.0
	CPUPROFILE=./raw.gperf ./lab2_list --threads=12 --iterations=1000 --sync=s
	pprof --text ./lab2_list ./raw.gperf > profile.out
	pprof --list=list_thread_func ./lab2_list ./raw.gperf >> profile.out
	rm ./raw.gperf profile.gperf
