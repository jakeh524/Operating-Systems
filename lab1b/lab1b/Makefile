# Jake Herron
# 005113997
# jakeh524@gmail.com

default: lab1b-client.c lab1b-server.c
	gcc -Wall -Wextra -g lab1b-client.c -lz -o lab1b-client
	gcc -Wall -Wextra -g lab1b-server.c -lz -o lab1b-server
	
client: lab1b-client.c
	gcc -Wall -Wextra -g lab1b-client.c -lz -o lab1b-client
	
server: lab1b-server.c
	gcc -Wall -Wextra -g lab1b-server.c -lz -o lab1b-server
	
clean:
	rm lab1b-server
	rm lab1b-client
	rm lab1b-005113997.tar.gz
	
dist:
	tar -cvzf lab1b-005113997.tar.gz lab1b-client.c lab1b-server.c Makefile README
