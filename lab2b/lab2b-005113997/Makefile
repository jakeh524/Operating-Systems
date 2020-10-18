# Jake Herron
# 005113997
# jakeh524@gmail.com

default: lab2_list.c SortedList.h SortedList.c
	gcc -Wall -Wextra -g -lpthread -lprofiler lab2_list.c SortedList.c -o lab2_list
	
graphs: tests
	chmod +x lab2_list.gp
	./lab2_list.gp
	
clean: default
	rm lab2_list
	rm lab2b-005113997.tar.gz
	
dist: graphs
	tar -cvzf lab2b-005113997.tar.gz SortedList.h SortedList.c lab2_list.c Makefile lab2b_list.csv profile.out lab2b_1.png lab2b_2.png lab2b_3.png lab2b_4.png lab2b_5.png lab2_list.gp README
	
	
tests: default
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
	
	# no sync sublists
	./lab2_list --threads=1 --iterations=1 --yield=id --lists=4 >> lab2b_list.csv
	./lab2_list --threads=1 --iterations=2 --yield=id --lists=4 >> lab2b_list.csv
	./lab2_list --threads=1 --iterations=4 --yield=id --lists=4 >> lab2b_list.csv
	./lab2_list --threads=1 --iterations=8 --yield=id --lists=4 >> lab2b_list.csv
	./lab2_list --threads=1 --iterations=16 --yield=id --lists=4 >> lab2b_list.csv
	./lab2_list --threads=4 --iterations=1 --yield=id --lists=4 >> lab2b_list.csv
	- ./lab2_list --threads=4 --iterations=2 --yield=id --lists=4 >> lab2b_list.csv
	- ./lab2_list --threads=4 --iterations=4 --yield=id --lists=4 >> lab2b_list.csv
	- ./lab2_list --threads=4 --iterations=8 --yield=id --lists=4 >> lab2b_list.csv
	- ./lab2_list --threads=4 --iterations=16 --yield=id --lists=4 >> lab2b_list.csv
	- ./lab2_list --threads=8 --iterations=1 --yield=id --lists=4 >> lab2b_list.csv
	- ./lab2_list --threads=8 --iterations=2 --yield=id --lists=4 >> lab2b_list.csv
	- ./lab2_list --threads=8 --iterations=4 --yield=id --lists=4 >> lab2b_list.csv
	- ./lab2_list --threads=8 --iterations=8 --yield=id --lists=4 >> lab2b_list.csv
	- ./lab2_list --threads=8 --iterations=16 --yield=id --lists=4 >> lab2b_list.csv
	- ./lab2_list --threads=12 --iterations=1 --yield=id --lists=4 >> lab2b_list.csv
	- ./lab2_list --threads=12 --iterations=2 --yield=id --lists=4 >> lab2b_list.csv
	- ./lab2_list --threads=12 --iterations=4 --yield=id --lists=4 >> lab2b_list.csv
	- ./lab2_list --threads=12 --iterations=8 --yield=id --lists=4 >> lab2b_list.csv
	- ./lab2_list --threads=12 --iterations=16 --yield=id --lists=4 >> lab2b_list.csv
	- ./lab2_list --threads=16 --iterations=1 --yield=id --lists=4 >> lab2b_list.csv
	- ./lab2_list --threads=16 --iterations=2 --yield=id --lists=4 >> lab2b_list.csv
	- ./lab2_list --threads=16 --iterations=4 --yield=id --lists=4 >> lab2b_list.csv
	- ./lab2_list --threads=16 --iterations=8 --yield=id --lists=4 >> lab2b_list.csv
	- ./lab2_list --threads=16 --iterations=16 --yield=id --lists=4 >> lab2b_list.csv
	
	#mutex sublists
	./lab2_list --threads=1 --iterations=10 --yield=id --lists=4 --sync=m >> lab2b_list.csv
	./lab2_list --threads=1 --iterations=20 --yield=id --lists=4 --sync=m >> lab2b_list.csv
	./lab2_list --threads=1 --iterations=40 --yield=id --lists=4 --sync=m >> lab2b_list.csv
	./lab2_list --threads=1 --iterations=80 --yield=id --lists=4 --sync=m >> lab2b_list.csv
	./lab2_list --threads=4 --iterations=10 --yield=id --lists=4 --sync=m >> lab2b_list.csv
	./lab2_list --threads=4 --iterations=20 --yield=id --lists=4 --sync=m >> lab2b_list.csv
	./lab2_list --threads=4 --iterations=40 --yield=id --lists=4 --sync=m >> lab2b_list.csv
	./lab2_list --threads=4 --iterations=80 --yield=id --lists=4 --sync=m >> lab2b_list.csv
	./lab2_list --threads=8 --iterations=10 --yield=id --lists=4 --sync=m >> lab2b_list.csv
	./lab2_list --threads=8 --iterations=20 --yield=id --lists=4 --sync=m >> lab2b_list.csv
	./lab2_list --threads=8 --iterations=40 --yield=id --lists=4 --sync=m >> lab2b_list.csv
	./lab2_list --threads=8 --iterations=80 --yield=id --lists=4 --sync=m >> lab2b_list.csv
	./lab2_list --threads=12 --iterations=10 --yield=id --lists=4 --sync=m >> lab2b_list.csv
	./lab2_list --threads=12 --iterations=20 --yield=id --lists=4 --sync=m >> lab2b_list.csv
	./lab2_list --threads=12 --iterations=40 --yield=id --lists=4 --sync=m >> lab2b_list.csv
	./lab2_list --threads=12 --iterations=80 --yield=id --lists=4 --sync=m >> lab2b_list.csv
	./lab2_list --threads=16 --iterations=10 --yield=id --lists=4 --sync=m >> lab2b_list.csv
	./lab2_list --threads=16 --iterations=20 --yield=id --lists=4 --sync=m >> lab2b_list.csv
	./lab2_list --threads=16 --iterations=40 --yield=id --lists=4 --sync=m >> lab2b_list.csv
	./lab2_list --threads=16 --iterations=80 --yield=id --lists=4 --sync=m >> lab2b_list.csv
	./lab2_list --threads=1 --iterations=5 --yield=id --lists=4 --sync=m >> lab2b_list.csv
	./lab2_list --threads=1 --iterations=15 --yield=id --lists=4 --sync=m >> lab2b_list.csv
	./lab2_list --threads=1 --iterations=35 --yield=id --lists=4 --sync=m >> lab2b_list.csv
	./lab2_list --threads=1 --iterations=75 --yield=id --lists=4 --sync=m >> lab2b_list.csv
	./lab2_list --threads=4 --iterations=5 --yield=id --lists=4 --sync=m >> lab2b_list.csv
	./lab2_list --threads=4 --iterations=15 --yield=id --lists=4 --sync=m >> lab2b_list.csv
	./lab2_list --threads=4 --iterations=35 --yield=id --lists=4 --sync=m >> lab2b_list.csv
	./lab2_list --threads=4 --iterations=75 --yield=id --lists=4 --sync=m >> lab2b_list.csv
	./lab2_list --threads=8 --iterations=5 --yield=id --lists=4 --sync=m >> lab2b_list.csv
	./lab2_list --threads=8 --iterations=15 --yield=id --lists=4 --sync=m >> lab2b_list.csv
	./lab2_list --threads=8 --iterations=35 --yield=id --lists=4 --sync=m >> lab2b_list.csv
	./lab2_list --threads=8 --iterations=75 --yield=id --lists=4 --sync=m >> lab2b_list.csv
	./lab2_list --threads=12 --iterations=5 --yield=id --lists=4 --sync=m >> lab2b_list.csv
	./lab2_list --threads=12 --iterations=15 --yield=id --lists=4 --sync=m >> lab2b_list.csv
	./lab2_list --threads=12 --iterations=35 --yield=id --lists=4 --sync=m >> lab2b_list.csv
	./lab2_list --threads=12 --iterations=75 --yield=id --lists=4 --sync=m >> lab2b_list.csv
	./lab2_list --threads=16 --iterations=5 --yield=id --lists=4 --sync=m >> lab2b_list.csv
	./lab2_list --threads=16 --iterations=15 --yield=id --lists=4 --sync=m >> lab2b_list.csv
	./lab2_list --threads=16 --iterations=35 --yield=id --lists=4 --sync=m >> lab2b_list.csv
	./lab2_list --threads=16 --iterations=75 --yield=id --lists=4 --sync=m >> lab2b_list.csv
	
	#spin lock sublists
	./lab2_list --threads=1 --iterations=10 --yield=id --lists=4 --sync=s >> lab2b_list.csv
	./lab2_list --threads=1 --iterations=20 --yield=id --lists=4 --sync=s >> lab2b_list.csv
	./lab2_list --threads=1 --iterations=40 --yield=id --lists=4 --sync=s >> lab2b_list.csv
	./lab2_list --threads=1 --iterations=80 --yield=id --lists=4 --sync=s >> lab2b_list.csv
	./lab2_list --threads=4 --iterations=10 --yield=id --lists=4 --sync=s >> lab2b_list.csv
	./lab2_list --threads=4 --iterations=20 --yield=id --lists=4 --sync=s >> lab2b_list.csv
	./lab2_list --threads=4 --iterations=40 --yield=id --lists=4 --sync=s >> lab2b_list.csv
	./lab2_list --threads=4 --iterations=80 --yield=id --lists=4 --sync=s >> lab2b_list.csv
	./lab2_list --threads=8 --iterations=10 --yield=id --lists=4 --sync=s >> lab2b_list.csv
	./lab2_list --threads=8 --iterations=20 --yield=id --lists=4 --sync=s >> lab2b_list.csv
	./lab2_list --threads=8 --iterations=40 --yield=id --lists=4 --sync=s >> lab2b_list.csv
	./lab2_list --threads=8 --iterations=80 --yield=id --lists=4 --sync=s >> lab2b_list.csv
	./lab2_list --threads=12 --iterations=10 --yield=id --lists=4 --sync=s >> lab2b_list.csv
	./lab2_list --threads=12 --iterations=20 --yield=id --lists=4 --sync=s >> lab2b_list.csv
	./lab2_list --threads=12 --iterations=40 --yield=id --lists=4 --sync=s >> lab2b_list.csv
	./lab2_list --threads=12 --iterations=80 --yield=id --lists=4 --sync=s >> lab2b_list.csv
	./lab2_list --threads=16 --iterations=10 --yield=id --lists=4 --sync=s >> lab2b_list.csv
	./lab2_list --threads=16 --iterations=20 --yield=id --lists=4 --sync=s >> lab2b_list.csv
	./lab2_list --threads=16 --iterations=40 --yield=id --lists=4 --sync=s >> lab2b_list.csv
	./lab2_list --threads=16 --iterations=80 --yield=id --lists=4 --sync=s >> lab2b_list.csv
	
	# mutex sublists no yield
	./lab2_list --threads=1 --iterations=1000 --lists=4 --sync=m >> lab2b_list.csv
	./lab2_list --threads=1 --iterations=1000 --lists=8 --sync=m >> lab2b_list.csv
	./lab2_list --threads=1 --iterations=1000 --lists=16 --sync=m >> lab2b_list.csv
	./lab2_list --threads=2 --iterations=1000 --lists=4 --sync=m >> lab2b_list.csv
	./lab2_list --threads=2 --iterations=1000 --lists=8 --sync=m >> lab2b_list.csv
	./lab2_list --threads=2 --iterations=1000 --lists=16 --sync=m >> lab2b_list.csv
	./lab2_list --threads=4 --iterations=1000 --lists=4 --sync=m >> lab2b_list.csv
	./lab2_list --threads=4 --iterations=1000 --lists=8 --sync=m >> lab2b_list.csv
	./lab2_list --threads=4 --iterations=1000 --lists=16 --sync=m >> lab2b_list.csv
	./lab2_list --threads=8 --iterations=1000 --lists=4 --sync=m >> lab2b_list.csv
	./lab2_list --threads=8 --iterations=1000 --lists=8 --sync=m >> lab2b_list.csv
	./lab2_list --threads=8 --iterations=1000 --lists=16 --sync=m >> lab2b_list.csv
	./lab2_list --threads=12 --iterations=1000 --lists=4 --sync=m >> lab2b_list.csv
	./lab2_list --threads=12 --iterations=1000 --lists=8 --sync=m >> lab2b_list.csv
	./lab2_list --threads=12 --iterations=1000 --lists=16 --sync=m >> lab2b_list.csv
	
	# spin lock sublists no yield
	./lab2_list --threads=1 --iterations=1000 --lists=4 --sync=s >> lab2b_list.csv
	./lab2_list --threads=1 --iterations=1000 --lists=8 --sync=s >> lab2b_list.csv
	./lab2_list --threads=1 --iterations=1000 --lists=16 --sync=s >> lab2b_list.csv
	./lab2_list --threads=2 --iterations=1000 --lists=4 --sync=s >> lab2b_list.csv
	./lab2_list --threads=2 --iterations=1000 --lists=8 --sync=s >> lab2b_list.csv
	./lab2_list --threads=2 --iterations=1000 --lists=16 --sync=s >> lab2b_list.csv
	./lab2_list --threads=4 --iterations=1000 --lists=4 --sync=s >> lab2b_list.csv
	./lab2_list --threads=4 --iterations=1000 --lists=8 --sync=s >> lab2b_list.csv
	./lab2_list --threads=4 --iterations=1000 --lists=16 --sync=s >> lab2b_list.csv
	./lab2_list --threads=8 --iterations=1000 --lists=4 --sync=s >> lab2b_list.csv
	./lab2_list --threads=8 --iterations=1000 --lists=8 --sync=s >> lab2b_list.csv
	./lab2_list --threads=8 --iterations=1000 --lists=16 --sync=s >> lab2b_list.csv
	./lab2_list --threads=12 --iterations=1000 --lists=4 --sync=s >> lab2b_list.csv
	./lab2_list --threads=12 --iterations=1000 --lists=8 --sync=s >> lab2b_list.csv
	./lab2_list --threads=12 --iterations=1000 --lists=16 --sync=s >> lab2b_list.csv
	
profile: default
	LD_PRELOAD=/u/cs/ugrad/herron/lib/libprofiler.so.0
	CPUPROFILE=./raw.gperf ./lab2_list --threads=12 --iterations=1000 --sync=s
	pprof --text ./lab2_list ./raw.gperf > profile.out
	pprof --list=list_thread_func ./lab2_list ./raw.gperf >> profile.out
	rm ./raw.gperf profile.gperf
