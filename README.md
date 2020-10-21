# Operating-Systems
Projects aligning with principles about Operating Systems such as processes, multithreading, scheduling, file systems, and IOT.

lab1a - C program. Study of processes and I/O. Create a bash shell program by splitting a process. Implement piping and inter-process communication with pipe() and poll(). Full duplex terminal I/O and polled I/O that passes input and output between the two processes.

lab1b - C program. Continuation of the splitting process program from lab1a. Creates two processes, a client process and a server process. Connects the two processes using sockets to send and receive data. The server process connects to the client using the socket and then forks to create a separate bash shell and pipes I/O between the terminal and shell. The server processes receives input from the client and then pass it to the shell to execute. Then, the shell sends it back to the terminal which will further send to through the socket and back to the client. This lab also implemented a compression option to compress data that goes in the socket.

lab2a - C program. Multithreading and synchronization project. Testing addition/subtraction from a counter and modifying linked lists. Study of how increasing threads and number of operations influences the runtime of the program and the accuracy of the result in regards to race conditions. Also learning how mutexes and spin locks perform in runtime and accuracy.

lab2b - C program. Continuation of the study of multithreading and synchronization from lab2a. Multithreads linked list operations with different synchronization options. Further study into how mutexes and spin locks work and how they differ in performance at high iterations and threads. Test average wait time for a thread for both mutexes and spin locks.

lab3a - C++ program. File system project. Program takes in an EXT2 file system image and parses and summarizes it. Implements functions to retreive data about superblock, groups, blocks, and inodes in an EXT2 file system image. Outputs a summary of the image.

lab3b - Python program. Continuation of file system project from lab3a. Takes in a csv file that summarizes an EXT2 file system image (like the one generated from the lab3a project) and checks for errors or inconsistencies in the inode, block, and directory entries. Tests whether the inputted file system summary is valid and follows EXT2 rules.

lab4a - C program. Internet of Things project using a Beaglebone. Simple project setting up the Beaglebone and installing its necessary software. Tests it using a simple Hello World C program.

lab4b - C program. Continuation of IOT project. Utilizes a temperature sensor and button sensor hooked up to the Beaglebon board. Program takes in data from the temperature sensor and outputs to the terminal periodically. Takes in arguments to change the period, swap the temperature units, or log the data. Program can also take input from the keyboard to change this information.

lab4c - C program. Continuation of IOT project. Adds networking capabilites to the previous lab4b program. Beaglebone is now able to communicate with a TCP logging server to receive data from the temperature sensor. The other C program can communicate with a secure TLS server through SSL.

All projects have their own corresponding Makefiles to build the programs and README files summarizing the files in each project folder.
