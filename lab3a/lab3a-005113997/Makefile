# Jake Herron
# 005113997
# jakeh524@gmail.com

default: lab3a.cpp ext2_fs.h
	g++ -Wall -Wextra -g lab3a.cpp -o lab3a
	
clean: default
	rm lab3a
	rm lab3a-005113997.tar.gz
	
dist:
	tar -cvzf lab3a-005113997.tar.gz lab3a.cpp ext2_fs.h Makefile README
