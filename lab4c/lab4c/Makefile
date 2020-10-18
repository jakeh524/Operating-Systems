# Jake Herron
# 005113997
# jakeh524@gmail.com

default: lab4c_tcp.c lab4c_tls.c
	gcc -Wall -Wextra -g -lmraa -lm lab4c_tcp.c -o lab4c_tcp
	gcc -Wall -Wextra -g -lssl -lcrypto -lmraa -lm lab4c_tls.c -o lab4c_tls
	
clean: default
	rm lab4c_tcp
	rm lab4c_tls
	rm lab4c-005113997.tar.gz
	
dist:
	tar -cvzf lab4c-005113997.tar.gz lab4c_tcp.c lab4c_tls.c Makefile README



