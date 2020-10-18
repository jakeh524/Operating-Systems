# Jake Herron
# 005113997
# jakeh524@gmail.com

default: lab2_add.c lab2_list.c SortedList.h SortedList.c
	gcc -Wall -Wextra -g lab2_add.c -o lab2_add -lpthread
	gcc -Wall -Wextra -g lab2_list.c SortedList.c -o lab2_list -lpthread 
	
clean:
	rm lab2_add
	#rm lab2_add-1.png
	#rm lab2_add-2.png
	#rm lab2_add-3.png
	#rm lab2_add-4.png
	#rm lab2_add-5.png
	#rm lab2_add.csv
	rm lab2_list
	#rm lab2_list-1.png
	#rm lab2_list-2.png
	#rm lab2_list-3.png
	#rm lab2_list-4.png
	#rm lab2_list.csv
	rm lab2a-005113997.tar.gz
	
	
graphs: tests
	chmod +x lab2_add.gp
	./lab2_add.gp
	chmod +x lab2_list.gp
	./lab2_list.gp
	
dist: graphs
	tar -cvzf lab2a-005113997.tar.gz lab2_add.c SortedList.h SortedList.c lab2_list.c lab2_add.csv lab2_list.csv lab2_add-1.png lab2_add-2.png lab2_add-2.png lab2_add-3.png lab2_add-4.png lab2_add-5.png lab2_list-1.png lab2_list-2.png lab2_list-3.png lab2_list-4.png Makefile README lab2_add.gp lab2_list.gp

tests: default
	
	#add
	#without yield no sync
	./lab2_add --threads=2 --iterations=100 >> lab2_add.csv
	./lab2_add --threads=2 --iterations=1000 >> lab2_add.csv
	./lab2_add --threads=2 --iterations=10000 >> lab2_add.csv
	./lab2_add --threads=2 --iterations=100000 >> lab2_add.csv
	./lab2_add --threads=4 --iterations=100 >> lab2_add.csv
	./lab2_add --threads=4 --iterations=1000 >> lab2_add.csv
	./lab2_add --threads=4 --iterations=10000 >> lab2_add.csv
	./lab2_add --threads=4 --iterations=100000 >> lab2_add.csv
	./lab2_add --threads=8 --iterations=100 >> lab2_add.csv
	./lab2_add --threads=8 --iterations=1000 >> lab2_add.csv
	./lab2_add --threads=8 --iterations=10000 >> lab2_add.csv
	./lab2_add --threads=8 --iterations=100000 >> lab2_add.csv
	./lab2_add --threads=12 --iterations=100 >> lab2_add.csv
	./lab2_add --threads=12 --iterations=1000 >> lab2_add.csv
	./lab2_add --threads=12 --iterations=10000 >> lab2_add.csv
	./lab2_add --threads=12 --iterations=100000 >> lab2_add.csv

	#with yield no sync
	./lab2_add --threads=2 --iterations=10 --yield >> lab2_add.csv
	./lab2_add --threads=2 --iterations=20 --yield >> lab2_add.csv
	./lab2_add --threads=2 --iterations=40 --yield >> lab2_add.csv
	./lab2_add --threads=2 --iterations=80 --yield >> lab2_add.csv
	./lab2_add --threads=2 --iterations=100 --yield >> lab2_add.csv
	./lab2_add --threads=2 --iterations=1000 --yield >> lab2_add.csv
	./lab2_add --threads=2 --iterations=10000 --yield >> lab2_add.csv
	./lab2_add --threads=2 --iterations=100000 --yield >> lab2_add.csv
	./lab2_add --threads=4 --iterations=10 --yield >> lab2_add.csv
	./lab2_add --threads=4 --iterations=20 --yield >> lab2_add.csv
	./lab2_add --threads=4 --iterations=40 --yield >> lab2_add.csv
	./lab2_add --threads=4 --iterations=80 --yield >> lab2_add.csv
	./lab2_add --threads=4 --iterations=100 --yield >> lab2_add.csv
	./lab2_add --threads=4 --iterations=1000 --yield >> lab2_add.csv
	./lab2_add --threads=4 --iterations=10000 --yield >> lab2_add.csv
	./lab2_add --threads=4 --iterations=100000 --yield >> lab2_add.csv
	./lab2_add --threads=8 --iterations=10 --yield >> lab2_add.csv
	./lab2_add --threads=8 --iterations=20 --yield >> lab2_add.csv
	./lab2_add --threads=8 --iterations=40 --yield >> lab2_add.csv
	./lab2_add --threads=8 --iterations=80 --yield >> lab2_add.csv
	./lab2_add --threads=8 --iterations=100 --yield >> lab2_add.csv
	./lab2_add --threads=8 --iterations=1000 --yield >> lab2_add.csv
	./lab2_add --threads=8 --iterations=10000 --yield >> lab2_add.csv
	./lab2_add --threads=8 --iterations=100000 --yield >> lab2_add.csv
	./lab2_add --threads=12 --iterations=10 --yield >> lab2_add.csv
	./lab2_add --threads=12 --iterations=20 --yield >> lab2_add.csv
	./lab2_add --threads=12 --iterations=40 --yield >> lab2_add.csv
	./lab2_add --threads=12 --iterations=80 --yield >> lab2_add.csv
	./lab2_add --threads=12 --iterations=100 --yield >> lab2_add.csv
	./lab2_add --threads=12 --iterations=1000 --yield >> lab2_add.csv
	./lab2_add --threads=12 --iterations=10000 --yield >> lab2_add.csv
	./lab2_add --threads=12 --iterations=100000 --yield >> lab2_add.csv

	#single thread without yield
	./lab2_add --threads=1 --iterations=1 >> lab2_add.csv
	./lab2_add --threads=1 --iterations=10 >> lab2_add.csv
	./lab2_add --threads=1 --iterations=100 >> lab2_add.csv
	./lab2_add --threads=1 --iterations=1000 >> lab2_add.csv
	./lab2_add --threads=1 --iterations=10000 >> lab2_add.csv
	./lab2_add --threads=1 --iterations=100000 >> lab2_add.csv
	./lab2_add --threads=1 --iterations=1000000 >> lab2_add.csv
	./lab2_add --threads=2 --iterations=1 >> lab2_add.csv
	./lab2_add --threads=2 --iterations=10 >> lab2_add.csv
	./lab2_add --threads=2 --iterations=100 >> lab2_add.csv
	./lab2_add --threads=2 --iterations=1000 >> lab2_add.csv
	./lab2_add --threads=2 --iterations=10000 >> lab2_add.csv
	./lab2_add --threads=2 --iterations=100000 >> lab2_add.csv
	./lab2_add --threads=2 --iterations=1000000 >> lab2_add.csv
	./lab2_add --threads=4 --iterations=1 >> lab2_add.csv
	./lab2_add --threads=4 --iterations=10 >> lab2_add.csv
	./lab2_add --threads=4 --iterations=100 >> lab2_add.csv
	./lab2_add --threads=4 --iterations=1000 >> lab2_add.csv
	./lab2_add --threads=4 --iterations=10000 >> lab2_add.csv
	./lab2_add --threads=4 --iterations=100000 >> lab2_add.csv
	./lab2_add --threads=4 --iterations=1000000 >> lab2_add.csv

	#mutex no yield
	./lab2_add --threads=1 --iterations=100 --sync=m >> lab2_add.csv
	./lab2_add --threads=1 --iterations=1000 --sync=m >> lab2_add.csv
	./lab2_add --threads=1 --iterations=10000 --sync=m >> lab2_add.csv
	./lab2_add --threads=1 --iterations=100000 --sync=m >> lab2_add.csv
	./lab2_add --threads=2 --iterations=100 --sync=m >> lab2_add.csv
	./lab2_add --threads=2 --iterations=1000 --sync=m >> lab2_add.csv
	./lab2_add --threads=2 --iterations=10000 --sync=m >> lab2_add.csv
	./lab2_add --threads=2 --iterations=100000 --sync=m >> lab2_add.csv
	./lab2_add --threads=4 --iterations=100 --sync=m >> lab2_add.csv
	./lab2_add --threads=4 --iterations=1000 --sync=m >> lab2_add.csv
	./lab2_add --threads=4 --iterations=10000 --sync=m >> lab2_add.csv
	./lab2_add --threads=4 --iterations=100000 --sync=m >> lab2_add.csv
	./lab2_add --threads=8 --iterations=100 --sync=m >> lab2_add.csv
	./lab2_add --threads=8 --iterations=1000 --sync=m >> lab2_add.csv
	./lab2_add --threads=8 --iterations=10000 --sync=m >> lab2_add.csv
	./lab2_add --threads=8 --iterations=100000 --sync=m >> lab2_add.csv
	./lab2_add --threads=12 --iterations=100 --sync=m >> lab2_add.csv
	./lab2_add --threads=12 --iterations=1000 --sync=m >> lab2_add.csv
	./lab2_add --threads=12 --iterations=10000 --sync=m >> lab2_add.csv
	./lab2_add --threads=12 --iterations=100000 --sync=m >> lab2_add.csv

	#spin lock no yield
	./lab2_add --threads=1 --iterations=100 --sync=s >> lab2_add.csv
	./lab2_add --threads=1 --iterations=1000 --sync=s >> lab2_add.csv
	./lab2_add --threads=1 --iterations=10000 --sync=s >> lab2_add.csv
	./lab2_add --threads=1 --iterations=100000 --sync=s >> lab2_add.csv
	./lab2_add --threads=2 --iterations=100 --sync=s >> lab2_add.csv
	./lab2_add --threads=2 --iterations=1000 --sync=s >> lab2_add.csv
	./lab2_add --threads=2 --iterations=10000 --sync=s >> lab2_add.csv
	./lab2_add --threads=2 --iterations=100000 --sync=s >> lab2_add.csv
	./lab2_add --threads=4 --iterations=100 --sync=s >> lab2_add.csv
	./lab2_add --threads=4 --iterations=1000 --sync=s >> lab2_add.csv
	./lab2_add --threads=4 --iterations=10000 --sync=s >> lab2_add.csv
	./lab2_add --threads=4 --iterations=100000 --sync=s >> lab2_add.csv
	./lab2_add --threads=8 --iterations=100 --sync=s >> lab2_add.csv
	./lab2_add --threads=8 --iterations=1000 --sync=s >> lab2_add.csv
	./lab2_add --threads=8 --iterations=10000 --sync=s >> lab2_add.csv
	./lab2_add --threads=8 --iterations=100000 --sync=s >> lab2_add.csv
	./lab2_add --threads=12 --iterations=100 --sync=s >> lab2_add.csv
	./lab2_add --threads=12 --iterations=1000 --sync=s >> lab2_add.csv
	./lab2_add --threads=12 --iterations=10000 --sync=s >> lab2_add.csv
	./lab2_add --threads=12 --iterations=100000 --sync=s >> lab2_add.csv

	#compare and swap no yield
	./lab2_add --threads=1 --iterations=100 --sync=c >> lab2_add.csv
	./lab2_add --threads=1 --iterations=1000 --sync=c >> lab2_add.csv
	./lab2_add --threads=1 --iterations=10000 --sync=c >> lab2_add.csv
	./lab2_add --threads=1 --iterations=100000 --sync=c >> lab2_add.csv
	./lab2_add --threads=2 --iterations=100 --sync=c >> lab2_add.csv
	./lab2_add --threads=2 --iterations=1000 --sync=c >> lab2_add.csv
	./lab2_add --threads=2 --iterations=10000 --sync=c >> lab2_add.csv
	./lab2_add --threads=2 --iterations=100000 --sync=c >> lab2_add.csv
	./lab2_add --threads=4 --iterations=100 --sync=c >> lab2_add.csv
	./lab2_add --threads=4 --iterations=1000 --sync=c >> lab2_add.csv
	./lab2_add --threads=4 --iterations=10000 --sync=c >> lab2_add.csv
	./lab2_add --threads=4 --iterations=100000 --sync=c >> lab2_add.csv
	./lab2_add --threads=8 --iterations=100 --sync=c >> lab2_add.csv
	./lab2_add --threads=8 --iterations=1000 --sync=c >> lab2_add.csv
	./lab2_add --threads=8 --iterations=10000 --sync=c >> lab2_add.csv
	./lab2_add --threads=8 --iterations=100000 --sync=c >> lab2_add.csv
	./lab2_add --threads=12 --iterations=100 --sync=c >> lab2_add.csv
	./lab2_add --threads=12 --iterations=1000 --sync=c >> lab2_add.csv
	./lab2_add --threads=12 --iterations=10000 --sync=c >> lab2_add.csv
	./lab2_add --threads=12 --iterations=100000 --sync=c >> lab2_add.csv

	#mutex with yield
	./lab2_add --threads=1 --iterations=100 --sync=m --yield >> lab2_add.csv
	./lab2_add --threads=1 --iterations=1000 --sync=m --yield >> lab2_add.csv
	./lab2_add --threads=1 --iterations=10000 --sync=m --yield >> lab2_add.csv
	./lab2_add --threads=2 --iterations=100 --sync=m --yield >> lab2_add.csv
	./lab2_add --threads=2 --iterations=1000 --sync=m --yield >> lab2_add.csv
	./lab2_add --threads=2 --iterations=10000 --sync=m --yield >> lab2_add.csv
	./lab2_add --threads=4 --iterations=100 --sync=m --yield >> lab2_add.csv
	./lab2_add --threads=4 --iterations=1000 --sync=m --yield >> lab2_add.csv
	./lab2_add --threads=4 --iterations=10000 --sync=m --yield >> lab2_add.csv
	./lab2_add --threads=8 --iterations=100 --sync=m --yield >> lab2_add.csv
	./lab2_add --threads=8 --iterations=1000 --sync=m --yield >> lab2_add.csv
	./lab2_add --threads=8 --iterations=10000 --sync=m --yield >> lab2_add.csv
	./lab2_add --threads=12 --iterations=100 --sync=m --yield >> lab2_add.csv
	./lab2_add --threads=12 --iterations=1000 --sync=m --yield >> lab2_add.csv
	./lab2_add --threads=12 --iterations=10000 --sync=m --yield >> lab2_add.csv

	#spin lock with yield
	./lab2_add --threads=1 --iterations=100 --sync=s --yield >> lab2_add.csv
	./lab2_add --threads=1 --iterations=1000 --sync=s --yield >> lab2_add.csv
	./lab2_add --threads=2 --iterations=100 --sync=s --yield >> lab2_add.csv
	./lab2_add --threads=2 --iterations=1000 --sync=s --yield >> lab2_add.csv
	./lab2_add --threads=4 --iterations=100 --sync=s --yield >> lab2_add.csv
	./lab2_add --threads=4 --iterations=1000 --sync=s --yield >> lab2_add.csv
	./lab2_add --threads=8 --iterations=100 --sync=s --yield >> lab2_add.csv
	./lab2_add --threads=8 --iterations=1000 --sync=s --yield >> lab2_add.csv
	./lab2_add --threads=12 --iterations=100 --sync=s --yield >> lab2_add.csv
	./lab2_add --threads=12 --iterations=1000 --sync=s --yield >> lab2_add.csv

	#compare and swap with yield
	./lab2_add --threads=1 --iterations=100 --sync=c --yield >> lab2_add.csv
	./lab2_add --threads=1 --iterations=1000 --sync=c --yield >> lab2_add.csv
	./lab2_add --threads=1 --iterations=10000 --sync=c --yield >> lab2_add.csv
	./lab2_add --threads=2 --iterations=100 --sync=c --yield >> lab2_add.csv
	./lab2_add --threads=2 --iterations=1000 --sync=c --yield >> lab2_add.csv
	./lab2_add --threads=2 --iterations=10000 --sync=c --yield >> lab2_add.csv
	./lab2_add --threads=4 --iterations=100 --sync=c --yield >> lab2_add.csv
	./lab2_add --threads=4 --iterations=1000 --sync=c --yield >> lab2_add.csv
	./lab2_add --threads=4 --iterations=10000 --sync=c --yield >> lab2_add.csv
	./lab2_add --threads=8 --iterations=100 --sync=c --yield >> lab2_add.csv
	./lab2_add --threads=8 --iterations=1000 --sync=c --yield >> lab2_add.csv
	./lab2_add --threads=8 --iterations=10000 --sync=c --yield >> lab2_add.csv
	./lab2_add --threads=12 --iterations=100 --sync=c --yield >> lab2_add.csv
	./lab2_add --threads=12 --iterations=1000 --sync=c --yield >> lab2_add.csv
	./lab2_add --threads=12 --iterations=10000 --sync=c --yield >> lab2_add.csv
	
	#list
	#single thread no yield or sync
	./lab2_list --threads=1 --iterations=10 >> lab2_list.csv
	./lab2_list --threads=1 --iterations=100 >> lab2_list.csv
	./lab2_list --threads=1 --iterations=1000 >> lab2_list.csv
	./lab2_list --threads=1 --iterations=10000 >> lab2_list.csv
	./lab2_list --threads=1 --iterations=20000 >> lab2_list.csv
	
	
	#multi thread no yield
	- ./lab2_list --threads=2 --iterations=1 >> lab2_list.csv
	- ./lab2_list --threads=2 --iterations=10 >> lab2_list.csv
	- ./lab2_list --threads=2 --iterations=100 >> lab2_list.csv
	- ./lab2_list --threads=2 --iterations=1000 >> lab2_list.csv
	- ./lab2_list --threads=4 --iterations=1 >> lab2_list.csv
	- ./lab2_list --threads=4 --iterations=10 >> lab2_list.csv
	- ./lab2_list --threads=4 --iterations=100 >> lab2_list.csv
	- ./lab2_list --threads=4 --iterations=1000 >> lab2_list.csv
	- ./lab2_list --threads=8 --iterations=1 >> lab2_list.csv
	- ./lab2_list --threads=8 --iterations=10 >> lab2_list.csv
	- ./lab2_list --threads=8 --iterations=100 >> lab2_list.csv
	- ./lab2_list --threads=8 --iterations=1000 >> lab2_list.csv
	- ./lab2_list --threads=12 --iterations=1 >> lab2_list.csv
	- ./lab2_list --threads=12 --iterations=10 >> lab2_list.csv
	- ./lab2_list --threads=12 --iterations=100 >> lab2_list.csv
	- ./lab2_list --threads=12 --iterations=1000 >> lab2_list.csv
	
	
	#yield i
	- ./lab2_list --threads=2 --iterations=1 --yield=i >> lab2_list.csv
	- ./lab2_list --threads=2 --iterations=2 --yield=i >> lab2_list.csv
	- ./lab2_list --threads=2 --iterations=4 --yield=i >> lab2_list.csv
	- ./lab2_list --threads=2 --iterations=8 --yield=i >> lab2_list.csv
	- ./lab2_list --threads=2 --iterations=16 --yield=i >> lab2_list.csv
	- ./lab2_list --threads=2 --iterations=32 --yield=i >> lab2_list.csv
	- ./lab2_list --threads=4 --iterations=1 --yield=i >> lab2_list.csv
	- ./lab2_list --threads=4 --iterations=2 --yield=i >> lab2_list.csv
	- ./lab2_list --threads=4 --iterations=4 --yield=i >> lab2_list.csv
	- ./lab2_list --threads=4 --iterations=8 --yield=i >> lab2_list.csv
	- ./lab2_list --threads=4 --iterations=16 --yield=i >> lab2_list.csv
	- ./lab2_list --threads=4 --iterations=32 --yield=i >> lab2_list.csv
	- ./lab2_list --threads=8 --iterations=1 --yield=i >> lab2_list.csv
	- ./lab2_list --threads=8 --iterations=2 --yield=i >> lab2_list.csv
	- ./lab2_list --threads=8 --iterations=4 --yield=i >> lab2_list.csv
	- ./lab2_list --threads=8 --iterations=8 --yield=i >> lab2_list.csv
	- ./lab2_list --threads=8 --iterations=16 --yield=i >> lab2_list.csv
	- ./lab2_list --threads=8 --iterations=32 --yield=i >> lab2_list.csv
	- ./lab2_list --threads=12 --iterations=1 --yield=i >> lab2_list.csv
	- ./lab2_list --threads=12 --iterations=2 --yield=i >> lab2_list.csv
	- ./lab2_list --threads=12 --iterations=4 --yield=i >> lab2_list.csv
	- ./lab2_list --threads=12 --iterations=8 --yield=i >> lab2_list.csv
	- ./lab2_list --threads=12 --iterations=16 --yield=i >> lab2_list.csv
	- ./lab2_list --threads=12 --iterations=32 --yield=i >> lab2_list.csv
	
	
	
	#yield d
	- ./lab2_list --threads=2 --iterations=1 --yield=d >> lab2_list.csv
	- ./lab2_list --threads=2 --iterations=2 --yield=d >> lab2_list.csv
	- ./lab2_list --threads=2 --iterations=4 --yield=d >> lab2_list.csv
	- ./lab2_list --threads=2 --iterations=8 --yield=d >> lab2_list.csv
	- ./lab2_list --threads=2 --iterations=16 --yield=d >> lab2_list.csv
	- ./lab2_list --threads=2 --iterations=32 --yield=d >> lab2_list.csv
	- ./lab2_list --threads=4 --iterations=1 --yield=d >> lab2_list.csv
	- ./lab2_list --threads=4 --iterations=2 --yield=d >> lab2_list.csv
	- ./lab2_list --threads=4 --iterations=4 --yield=d >> lab2_list.csv
	- ./lab2_list --threads=4 --iterations=8 --yield=d >> lab2_list.csv
	- ./lab2_list --threads=4 --iterations=16 --yield=d >> lab2_list.csv
	- ./lab2_list --threads=4 --iterations=32 --yield=d >> lab2_list.csv
	- ./lab2_list --threads=8 --iterations=1 --yield=d >> lab2_list.csv
	- ./lab2_list --threads=8 --iterations=2 --yield=d >> lab2_list.csv
	- ./lab2_list --threads=8 --iterations=4 --yield=d >> lab2_list.csv
	- ./lab2_list --threads=8 --iterations=8 --yield=d >> lab2_list.csv
	- ./lab2_list --threads=8 --iterations=16 --yield=d >> lab2_list.csv
	- ./lab2_list --threads=8 --iterations=32 --yield=d >> lab2_list.csv
	- ./lab2_list --threads=12 --iterations=1 --yield=d >> lab2_list.csv
	- ./lab2_list --threads=12 --iterations=2 --yield=d >> lab2_list.csv
	- ./lab2_list --threads=12 --iterations=4 --yield=d >> lab2_list.csv
	- ./lab2_list --threads=12 --iterations=8 --yield=d >> lab2_list.csv
	- ./lab2_list --threads=12 --iterations=16 --yield=d >> lab2_list.csv
	- ./lab2_list --threads=12 --iterations=32 --yield=d >> lab2_list.csv
	
	
	
	#yield il
	- ./lab2_list --threads=2 --iterations=1 --yield=il >> lab2_list.csv
	- ./lab2_list --threads=2 --iterations=2 --yield=il >> lab2_list.csv
	- ./lab2_list --threads=2 --iterations=4 --yield=il >> lab2_list.csv
	- ./lab2_list --threads=2 --iterations=8 --yield=il >> lab2_list.csv
	- ./lab2_list --threads=2 --iterations=16 --yield=il >> lab2_list.csv
	- ./lab2_list --threads=2 --iterations=32 --yield=il >> lab2_list.csv
	- ./lab2_list --threads=4 --iterations=1 --yield=il >> lab2_list.csv
	- ./lab2_list --threads=4 --iterations=2 --yield=il >> lab2_list.csv
	- ./lab2_list --threads=4 --iterations=4 --yield=il >> lab2_list.csv
	- ./lab2_list --threads=4 --iterations=8 --yield=il >> lab2_list.csv
	- ./lab2_list --threads=4 --iterations=16 --yield=il >> lab2_list.csv
	- ./lab2_list --threads=4 --iterations=32 --yield=il >> lab2_list.csv
	- ./lab2_list --threads=8 --iterations=1 --yield=il >> lab2_list.csv
	- ./lab2_list --threads=8 --iterations=2 --yield=il >> lab2_list.csv
	- ./lab2_list --threads=8 --iterations=4 --yield=il >> lab2_list.csv
	- ./lab2_list --threads=8 --iterations=8 --yield=il >> lab2_list.csv
	- ./lab2_list --threads=8 --iterations=16 --yield=il >> lab2_list.csv
	- ./lab2_list --threads=8 --iterations=32 --yield=il >> lab2_list.csv
	- ./lab2_list --threads=12 --iterations=1 --yield=il >> lab2_list.csv
	- ./lab2_list --threads=12 --iterations=2 --yield=il >> lab2_list.csv
	- ./lab2_list --threads=12 --iterations=4 --yield=il >> lab2_list.csv
	- ./lab2_list --threads=12 --iterations=8 --yield=il >> lab2_list.csv
	- ./lab2_list --threads=12 --iterations=16 --yield=il >> lab2_list.csv
	- ./lab2_list --threads=12 --iterations=32 --yield=il >> lab2_list.csv
	
	
	#yield dl
	- ./lab2_list --threads=2 --iterations=1 --yield=dl >> lab2_list.csv
	- ./lab2_list --threads=2 --iterations=2 --yield=dl >> lab2_list.csv
	- ./lab2_list --threads=2 --iterations=4 --yield=dl >> lab2_list.csv
	- ./lab2_list --threads=2 --iterations=8 --yield=dl >> lab2_list.csv
	- ./lab2_list --threads=2 --iterations=16 --yield=dl >> lab2_list.csv
	- ./lab2_list --threads=2 --iterations=32 --yield=dl >> lab2_list.csv
	- ./lab2_list --threads=4 --iterations=1 --yield=dl >> lab2_list.csv
	- ./lab2_list --threads=4 --iterations=2 --yield=dl >> lab2_list.csv
	- ./lab2_list --threads=4 --iterations=4 --yield=dl >> lab2_list.csv
	- ./lab2_list --threads=4 --iterations=8 --yield=dl >> lab2_list.csv
	- ./lab2_list --threads=4 --iterations=16 --yield=dl >> lab2_list.csv
	- ./lab2_list --threads=4 --iterations=32 --yield=dl >> lab2_list.csv
	- ./lab2_list --threads=8 --iterations=1 --yield=dl >> lab2_list.csv
	- ./lab2_list --threads=8 --iterations=2 --yield=dl >> lab2_list.csv
	- ./lab2_list --threads=8 --iterations=4 --yield=dl >> lab2_list.csv
	- ./lab2_list --threads=8 --iterations=8 --yield=dl >> lab2_list.csv
	- ./lab2_list --threads=8 --iterations=16 --yield=dl >> lab2_list.csv
	- ./lab2_list --threads=8 --iterations=32 --yield=dl >> lab2_list.csv
	- ./lab2_list --threads=12 --iterations=1 --yield=dl >> lab2_list.csv
	- ./lab2_list --threads=12 --iterations=2 --yield=dl >> lab2_list.csv
	- ./lab2_list --threads=12 --iterations=4 --yield=dl >> lab2_list.csv
	- ./lab2_list --threads=12 --iterations=8 --yield=dl >> lab2_list.csv
	- ./lab2_list --threads=12 --iterations=16 --yield=dl >> lab2_list.csv
	- ./lab2_list --threads=12 --iterations=32 --yield=dl >> lab2_list.csv
	
	#yield i with mutex
	./lab2_list --threads=2 --iterations=1 --yield=i --sync=m >> lab2_list.csv
	./lab2_list --threads=2 --iterations=2 --yield=i --sync=m >> lab2_list.csv
	./lab2_list --threads=2 --iterations=4 --yield=i --sync=m >> lab2_list.csv
	./lab2_list --threads=2 --iterations=8 --yield=i --sync=m >> lab2_list.csv
	./lab2_list --threads=2 --iterations=16 --yield=i --sync=m >> lab2_list.csv
	./lab2_list --threads=2 --iterations=32 --yield=i --sync=m >> lab2_list.csv
	./lab2_list --threads=4 --iterations=1 --yield=i --sync=m >> lab2_list.csv
	./lab2_list --threads=4 --iterations=2 --yield=i --sync=m >> lab2_list.csv
	./lab2_list --threads=4 --iterations=4 --yield=i --sync=m >> lab2_list.csv
	./lab2_list --threads=4 --iterations=8 --yield=i --sync=m >> lab2_list.csv
	./lab2_list --threads=4 --iterations=16 --yield=i --sync=m >> lab2_list.csv
	./lab2_list --threads=4 --iterations=32 --yield=i --sync=m >> lab2_list.csv
	./lab2_list --threads=8 --iterations=1 --yield=i --sync=m >> lab2_list.csv
	./lab2_list --threads=8 --iterations=2 --yield=i --sync=m >> lab2_list.csv
	./lab2_list --threads=8 --iterations=4 --yield=i --sync=m >> lab2_list.csv
	./lab2_list --threads=8 --iterations=8 --yield=i --sync=m >> lab2_list.csv
	./lab2_list --threads=8 --iterations=16 --yield=i --sync=m >> lab2_list.csv
	./lab2_list --threads=8 --iterations=32 --yield=i --sync=m >> lab2_list.csv
	./lab2_list --threads=12 --iterations=1 --yield=i --sync=m >> lab2_list.csv
	./lab2_list --threads=12 --iterations=2 --yield=i --sync=m >> lab2_list.csv
	./lab2_list --threads=12 --iterations=4 --yield=i --sync=m >> lab2_list.csv
	./lab2_list --threads=12 --iterations=8 --yield=i --sync=m >> lab2_list.csv
	./lab2_list --threads=12 --iterations=16 --yield=i --sync=m >> lab2_list.csv
	./lab2_list --threads=12 --iterations=32 --yield=i --sync=m >> lab2_list.csv
	
	
	
	#yield d with mutex
	./lab2_list --threads=2 --iterations=1 --yield=d --sync=m >> lab2_list.csv
	./lab2_list --threads=2 --iterations=2 --yield=d --sync=m >> lab2_list.csv
	./lab2_list --threads=2 --iterations=4 --yield=d --sync=m >> lab2_list.csv
	./lab2_list --threads=2 --iterations=8 --yield=d --sync=m >> lab2_list.csv
	./lab2_list --threads=2 --iterations=16 --yield=d --sync=m >> lab2_list.csv
	./lab2_list --threads=2 --iterations=32 --yield=d --sync=m >> lab2_list.csv
	./lab2_list --threads=4 --iterations=1 --yield=d --sync=m >> lab2_list.csv
	./lab2_list --threads=4 --iterations=2 --yield=d --sync=m >> lab2_list.csv
	./lab2_list --threads=4 --iterations=4 --yield=d --sync=m >> lab2_list.csv
	./lab2_list --threads=4 --iterations=8 --yield=d --sync=m >> lab2_list.csv
	./lab2_list --threads=4 --iterations=16 --yield=d --sync=m >> lab2_list.csv
	./lab2_list --threads=4 --iterations=32 --yield=d --sync=m >> lab2_list.csv
	./lab2_list --threads=8 --iterations=1 --yield=d --sync=m >> lab2_list.csv
	./lab2_list --threads=8 --iterations=2 --yield=d --sync=m >> lab2_list.csv
	./lab2_list --threads=8 --iterations=4 --yield=d --sync=m >> lab2_list.csv
	./lab2_list --threads=8 --iterations=8 --yield=d --sync=m >> lab2_list.csv
	./lab2_list --threads=8 --iterations=16 --yield=d --sync=m >> lab2_list.csv
	./lab2_list --threads=8 --iterations=32 --yield=d --sync=m >> lab2_list.csv
	./lab2_list --threads=12 --iterations=1 --yield=d --sync=m >> lab2_list.csv
	./lab2_list --threads=12 --iterations=2 --yield=d --sync=m >> lab2_list.csv
	./lab2_list --threads=12 --iterations=4 --yield=d --sync=m >> lab2_list.csv
	./lab2_list --threads=12 --iterations=8 --yield=d --sync=m >> lab2_list.csv
	./lab2_list --threads=12 --iterations=16 --yield=d --sync=m >> lab2_list.csv
	./lab2_list --threads=12 --iterations=32 --yield=d --sync=m >> lab2_list.csv
	
	
	
	#yield il with mutex
	./lab2_list --threads=2 --iterations=1 --yield=il --sync=m >> lab2_list.csv
	./lab2_list --threads=2 --iterations=2 --yield=il --sync=m >> lab2_list.csv
	./lab2_list --threads=2 --iterations=4 --yield=il --sync=m >> lab2_list.csv
	./lab2_list --threads=2 --iterations=8 --yield=il --sync=m >> lab2_list.csv
	./lab2_list --threads=2 --iterations=16 --yield=il --sync=m >> lab2_list.csv
	./lab2_list --threads=2 --iterations=32 --yield=il --sync=m >> lab2_list.csv
	./lab2_list --threads=4 --iterations=1 --yield=il --sync=m >> lab2_list.csv
	./lab2_list --threads=4 --iterations=2 --yield=il --sync=m >> lab2_list.csv
	./lab2_list --threads=4 --iterations=4 --yield=il --sync=m >> lab2_list.csv
	./lab2_list --threads=4 --iterations=8 --yield=il --sync=m >> lab2_list.csv
	./lab2_list --threads=4 --iterations=16 --yield=il --sync=m >> lab2_list.csv
	./lab2_list --threads=4 --iterations=32 --yield=il --sync=m >> lab2_list.csv
	./lab2_list --threads=8 --iterations=1 --yield=il --sync=m >> lab2_list.csv
	./lab2_list --threads=8 --iterations=2 --yield=il --sync=m >> lab2_list.csv
	./lab2_list --threads=8 --iterations=4 --yield=il --sync=m >> lab2_list.csv
	./lab2_list --threads=8 --iterations=8 --yield=il --sync=m >> lab2_list.csv
	./lab2_list --threads=8 --iterations=16 --yield=il --sync=m >> lab2_list.csv
	./lab2_list --threads=8 --iterations=32 --yield=il --sync=m >> lab2_list.csv
	./lab2_list --threads=12 --iterations=1 --yield=il --sync=m >> lab2_list.csv
	./lab2_list --threads=12 --iterations=2 --yield=il --sync=m >> lab2_list.csv
	./lab2_list --threads=12 --iterations=4 --yield=il --sync=m >> lab2_list.csv
	./lab2_list --threads=12 --iterations=8 --yield=il --sync=m >> lab2_list.csv
	./lab2_list --threads=12 --iterations=16 --yield=il --sync=m >> lab2_list.csv
	./lab2_list --threads=12 --iterations=32 --yield=il --sync=m >> lab2_list.csv
	
	
	#yield dl with mutex
	./lab2_list --threads=2 --iterations=1 --yield=dl --sync=m >> lab2_list.csv
	./lab2_list --threads=2 --iterations=2 --yield=dl --sync=m >> lab2_list.csv
	./lab2_list --threads=2 --iterations=4 --yield=dl --sync=m >> lab2_list.csv
	./lab2_list --threads=2 --iterations=8 --yield=dl --sync=m >> lab2_list.csv
	./lab2_list --threads=2 --iterations=16 --yield=dl --sync=m >> lab2_list.csv
	./lab2_list --threads=2 --iterations=32 --yield=dl --sync=m >> lab2_list.csv
	./lab2_list --threads=4 --iterations=1 --yield=dl --sync=m >> lab2_list.csv
	./lab2_list --threads=4 --iterations=2 --yield=dl --sync=m >> lab2_list.csv
	./lab2_list --threads=4 --iterations=4 --yield=dl --sync=m >> lab2_list.csv
	./lab2_list --threads=4 --iterations=8 --yield=dl --sync=m >> lab2_list.csv
	./lab2_list --threads=4 --iterations=16 --yield=dl --sync=m >> lab2_list.csv
	./lab2_list --threads=4 --iterations=32 --yield=dl --sync=m >> lab2_list.csv
	./lab2_list --threads=8 --iterations=1 --yield=dl --sync=m >> lab2_list.csv
	./lab2_list --threads=8 --iterations=2 --yield=dl --sync=m >> lab2_list.csv
	./lab2_list --threads=8 --iterations=4 --yield=dl --sync=m >> lab2_list.csv
	./lab2_list --threads=8 --iterations=8 --yield=dl --sync=m >> lab2_list.csv
	./lab2_list --threads=8 --iterations=16 --yield=dl --sync=m >> lab2_list.csv
	./lab2_list --threads=8 --iterations=32 --yield=dl --sync=m >> lab2_list.csv
	./lab2_list --threads=12 --iterations=1 --yield=dl --sync=m >> lab2_list.csv
	./lab2_list --threads=12 --iterations=2 --yield=dl --sync=m >> lab2_list.csv
	./lab2_list --threads=12 --iterations=4 --yield=dl --sync=m >> lab2_list.csv
	./lab2_list --threads=12 --iterations=8 --yield=dl --sync=m >> lab2_list.csv
	./lab2_list --threads=12 --iterations=16 --yield=dl --sync=m >> lab2_list.csv
	./lab2_list --threads=12 --iterations=32 --yield=dl --sync=m >> lab2_list.csv
	
	#yield i with spin
	./lab2_list --threads=2 --iterations=1 --yield=i --sync=s >> lab2_list.csv
	./lab2_list --threads=2 --iterations=2 --yield=i --sync=s >> lab2_list.csv
	./lab2_list --threads=2 --iterations=4 --yield=i --sync=s >> lab2_list.csv
	./lab2_list --threads=2 --iterations=8 --yield=i --sync=s >> lab2_list.csv
	./lab2_list --threads=2 --iterations=16 --yield=i --sync=s >> lab2_list.csv
	./lab2_list --threads=2 --iterations=32 --yield=i --sync=s >> lab2_list.csv
	./lab2_list --threads=4 --iterations=1 --yield=i --sync=s >> lab2_list.csv
	./lab2_list --threads=4 --iterations=2 --yield=i --sync=s >> lab2_list.csv
	./lab2_list --threads=4 --iterations=4 --yield=i --sync=s >> lab2_list.csv
	./lab2_list --threads=4 --iterations=8 --yield=i --sync=s >> lab2_list.csv
	./lab2_list --threads=4 --iterations=16 --yield=i --sync=s >> lab2_list.csv
	./lab2_list --threads=4 --iterations=32 --yield=i --sync=s >> lab2_list.csv
	./lab2_list --threads=8 --iterations=1 --yield=i --sync=s >> lab2_list.csv
	./lab2_list --threads=8 --iterations=2 --yield=i --sync=s >> lab2_list.csv
	./lab2_list --threads=8 --iterations=4 --yield=i --sync=s >> lab2_list.csv
	./lab2_list --threads=8 --iterations=8 --yield=i --sync=s >> lab2_list.csv
	./lab2_list --threads=8 --iterations=16 --yield=i --sync=s >> lab2_list.csv
	./lab2_list --threads=8 --iterations=32 --yield=i --sync=s >> lab2_list.csv
	./lab2_list --threads=12 --iterations=1 --yield=i --sync=s >> lab2_list.csv
	./lab2_list --threads=12 --iterations=2 --yield=i --sync=s >> lab2_list.csv
	./lab2_list --threads=12 --iterations=4 --yield=i --sync=s >> lab2_list.csv
	./lab2_list --threads=12 --iterations=8 --yield=i --sync=s >> lab2_list.csv
	./lab2_list --threads=12 --iterations=16 --yield=i --sync=s >> lab2_list.csv
	./lab2_list --threads=12 --iterations=32 --yield=i --sync=s >> lab2_list.csv
	
	
	#yield d with spin
	./lab2_list --threads=2 --iterations=1 --yield=d --sync=s >> lab2_list.csv
	./lab2_list --threads=2 --iterations=2 --yield=d --sync=s >> lab2_list.csv
	./lab2_list --threads=2 --iterations=4 --yield=d --sync=s >> lab2_list.csv
	./lab2_list --threads=2 --iterations=8 --yield=d --sync=s >> lab2_list.csv
	./lab2_list --threads=2 --iterations=16 --yield=d --sync=s >> lab2_list.csv
	./lab2_list --threads=2 --iterations=32 --yield=d --sync=s >> lab2_list.csv
	./lab2_list --threads=4 --iterations=1 --yield=d --sync=s >> lab2_list.csv
	./lab2_list --threads=4 --iterations=2 --yield=d --sync=s >> lab2_list.csv
	./lab2_list --threads=4 --iterations=4 --yield=d --sync=s >> lab2_list.csv
	./lab2_list --threads=4 --iterations=8 --yield=d --sync=s >> lab2_list.csv
	./lab2_list --threads=4 --iterations=16 --yield=d --sync=s >> lab2_list.csv
	./lab2_list --threads=4 --iterations=32 --yield=d --sync=s >> lab2_list.csv
	./lab2_list --threads=8 --iterations=1 --yield=d --sync=s >> lab2_list.csv
	./lab2_list --threads=8 --iterations=2 --yield=d --sync=s >> lab2_list.csv
	./lab2_list --threads=8 --iterations=4 --yield=d --sync=s >> lab2_list.csv
	./lab2_list --threads=8 --iterations=8 --yield=d --sync=s >> lab2_list.csv
	./lab2_list --threads=8 --iterations=16 --yield=d --sync=s >> lab2_list.csv
	./lab2_list --threads=8 --iterations=32 --yield=d --sync=s >> lab2_list.csv
	./lab2_list --threads=12 --iterations=1 --yield=d --sync=s >> lab2_list.csv
	./lab2_list --threads=12 --iterations=2 --yield=d --sync=s >> lab2_list.csv
	./lab2_list --threads=12 --iterations=4 --yield=d --sync=s >> lab2_list.csv
	./lab2_list --threads=12 --iterations=8 --yield=d --sync=s >> lab2_list.csv
	./lab2_list --threads=12 --iterations=16 --yield=d --sync=s >> lab2_list.csv
	./lab2_list --threads=12 --iterations=32 --yield=d --sync=s >> lab2_list.csv
	
	
	
	#yield il with spin
	./lab2_list --threads=2 --iterations=1 --yield=il --sync=s >> lab2_list.csv
	./lab2_list --threads=2 --iterations=2 --yield=il --sync=s >> lab2_list.csv
	./lab2_list --threads=2 --iterations=4 --yield=il --sync=s >> lab2_list.csv
	./lab2_list --threads=2 --iterations=8 --yield=il --sync=s >> lab2_list.csv
	./lab2_list --threads=2 --iterations=16 --yield=il --sync=s >> lab2_list.csv
	./lab2_list --threads=2 --iterations=32 --yield=il --sync=s >> lab2_list.csv
	./lab2_list --threads=4 --iterations=1 --yield=il --sync=s >> lab2_list.csv
	./lab2_list --threads=4 --iterations=2 --yield=il --sync=s >> lab2_list.csv
	./lab2_list --threads=4 --iterations=4 --yield=il --sync=s >> lab2_list.csv
	./lab2_list --threads=4 --iterations=8 --yield=il --sync=s >> lab2_list.csv
	./lab2_list --threads=4 --iterations=16 --yield=il --sync=s >> lab2_list.csv
	./lab2_list --threads=4 --iterations=32 --yield=il --sync=s >> lab2_list.csv
	./lab2_list --threads=8 --iterations=1 --yield=il --sync=s >> lab2_list.csv
	./lab2_list --threads=8 --iterations=2 --yield=il --sync=s >> lab2_list.csv
	./lab2_list --threads=8 --iterations=4 --yield=il --sync=s >> lab2_list.csv
	./lab2_list --threads=8 --iterations=8 --yield=il --sync=s >> lab2_list.csv
	./lab2_list --threads=8 --iterations=16 --yield=il --sync=s >> lab2_list.csv
	./lab2_list --threads=8 --iterations=32 --yield=il --sync=s >> lab2_list.csv
	./lab2_list --threads=12 --iterations=1 --yield=il --sync=s >> lab2_list.csv
	./lab2_list --threads=12 --iterations=2 --yield=il --sync=s >> lab2_list.csv
	./lab2_list --threads=12 --iterations=4 --yield=il --sync=s >> lab2_list.csv
	./lab2_list --threads=12 --iterations=8 --yield=il --sync=s >> lab2_list.csv
	./lab2_list --threads=12 --iterations=16 --yield=il --sync=s >> lab2_list.csv
	./lab2_list --threads=12 --iterations=32 --yield=il --sync=s >> lab2_list.csv
	
	
	#yield dl with spin
	./lab2_list --threads=2 --iterations=1 --yield=dl --sync=s >> lab2_list.csv
	./lab2_list --threads=2 --iterations=2 --yield=dl --sync=s >> lab2_list.csv
	./lab2_list --threads=2 --iterations=4 --yield=dl --sync=s >> lab2_list.csv
	./lab2_list --threads=2 --iterations=8 --yield=dl --sync=s >> lab2_list.csv
	./lab2_list --threads=2 --iterations=16 --yield=dl --sync=s >> lab2_list.csv
	./lab2_list --threads=2 --iterations=32 --yield=dl --sync=s >> lab2_list.csv
	./lab2_list --threads=4 --iterations=1 --yield=dl --sync=s >> lab2_list.csv
	./lab2_list --threads=4 --iterations=2 --yield=dl --sync=s >> lab2_list.csv
	./lab2_list --threads=4 --iterations=4 --yield=dl --sync=s >> lab2_list.csv
	./lab2_list --threads=4 --iterations=8 --yield=dl --sync=s >> lab2_list.csv
	./lab2_list --threads=4 --iterations=16 --yield=dl --sync=s >> lab2_list.csv
	./lab2_list --threads=4 --iterations=32 --yield=dl --sync=s >> lab2_list.csv
	./lab2_list --threads=8 --iterations=1 --yield=dl --sync=s >> lab2_list.csv
	./lab2_list --threads=8 --iterations=2 --yield=dl --sync=s >> lab2_list.csv
	./lab2_list --threads=8 --iterations=4 --yield=dl --sync=s >> lab2_list.csv
	./lab2_list --threads=8 --iterations=8 --yield=dl --sync=s >> lab2_list.csv
	./lab2_list --threads=8 --iterations=16 --yield=dl --sync=s >> lab2_list.csv
	./lab2_list --threads=8 --iterations=32 --yield=dl --sync=s >> lab2_list.csv
	./lab2_list --threads=12 --iterations=1 --yield=dl --sync=s >> lab2_list.csv
	./lab2_list --threads=12 --iterations=2 --yield=dl --sync=s >> lab2_list.csv
	./lab2_list --threads=12 --iterations=4 --yield=dl --sync=s >> lab2_list.csv
	./lab2_list --threads=12 --iterations=8 --yield=dl --sync=s >> lab2_list.csv
	./lab2_list --threads=12 --iterations=16 --yield=dl --sync=s >> lab2_list.csv
	./lab2_list --threads=12 --iterations=32 --yield=dl --sync=s >> lab2_list.csv
	
	
	#no yield mutexes
	./lab2_list --threads=1 --iterations=1000 --sync=m >> lab2_list.csv
	./lab2_list --threads=2 --iterations=1000 --sync=m >> lab2_list.csv
	./lab2_list --threads=4 --iterations=1000 --sync=m >> lab2_list.csv
	./lab2_list --threads=8 --iterations=1000 --sync=m >> lab2_list.csv
	./lab2_list --threads=12 --iterations=1000 --sync=m >> lab2_list.csv
	./lab2_list --threads=16 --iterations=1000 --sync=m >> lab2_list.csv
	./lab2_list --threads=24 --iterations=1000 --sync=m >> lab2_list.csv

	#no yield spin
	./lab2_list --threads=1 --iterations=1000 --sync=s >> lab2_list.csv
	./lab2_list --threads=2 --iterations=1000 --sync=s >> lab2_list.csv
	./lab2_list --threads=4 --iterations=1000 --sync=s >> lab2_list.csv
	./lab2_list --threads=8 --iterations=1000 --sync=s >> lab2_list.csv
	./lab2_list --threads=12 --iterations=1000 --sync=s >> lab2_list.csv
	./lab2_list --threads=16 --iterations=1000 --sync=s >> lab2_list.csv
	./lab2_list --threads=24 --iterations=1000 --sync=s >> lab2_list.csv
