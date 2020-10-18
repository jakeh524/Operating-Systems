// Jake Herron
// UID: 005113997
// jakeh524@gmail.com

#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netdb.h>
#include <strings.h>
#include <poll.h>
#include <signal.h>
#include <errno.h>
#include <sys/wait.h>
#include <zlib.h>
#include <string.h>


int main(int argc, char * argv[]) {
    
    //ARGUMENT PARSING
    
    extern char *optarg;
    
    int port_number = -1;
    int compress_flag = 0;
    
    static struct option long_options[] = {
        {"port", required_argument, 0, 'p'},
        {"compress", no_argument, 0, 'c'},
        {0, 0, 0, 0}
    };
    
    char c;
    
    while((c=getopt_long(argc,argv,"s",long_options,NULL)) != -1) {
        switch(c){
            case 'p': // shell
                port_number = atoi(optarg); //convert port number (which is a string) to an int
                break;
            case 'c':
                compress_flag = 1;
                break;
            case '?': //unknown arg
                fprintf(stderr, "Unrecognized argument present.\n");
                exit(1);
                break;
        }
    }
    
    if(port_number == -1) // check to make sure --port is used
    {
        fprintf(stderr, "--port= option is not present.\n");
        exit(1);
    }
    
    // SOCKET SETUP
    
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(socket_fd == -1)
    {
        fprintf(stderr, "Error on socket system call.\n");
        exit(1);
    }
    
    struct hostent *host = gethostbyname("localhost");
    if(host == NULL)
    {
        fprintf(stderr, "Error on gethostbyname system call.\n");
        exit(1);
    }
    
    struct sockaddr_in address_struct;
    bzero(&address_struct, sizeof(struct sockaddr_in));
    //bzero(&address_struct.sin_addr, sizeof(address_struct.sin_addr));
    address_struct.sin_family = AF_INET;
    address_struct.sin_port = htons(port_number);
    memcpy(&address_struct.sin_addr, host->h_addr_list[0], host->h_length);
    
    int bind_error_check = bind(socket_fd, (struct sockaddr *)&address_struct, sizeof(struct sockaddr));
    if(bind_error_check == -1)
    {
        fprintf(stderr, "Error on bind system call.\n");
        exit(1);
    }
    
    int listen_error_check = listen(socket_fd, 5);
    if(listen_error_check == -1)
    {
        fprintf(stderr, "Error on listen system call.\n");
        exit(1);
    }
    

    //TODO:ACCEPT MAY NEED TO BE INSIDE THE LOOP IDK
    socklen_t size = sizeof(address_struct);
    int accept_fd = accept(socket_fd, (struct sockaddr *)&address_struct, &size);
    if(accept_fd == -1)
    {
        fprintf(stderr, "Error on accept system call.\n");
        exit(1);
    }

    
    
    
    // PROCESS INPUT FROM SOCKET AND SHELL
    
    
    
    
    // MAKE THE TWO SETS OF PIPES
            
    int pipefd_terminal[2]; // read is [0] ; write is [1]
    int error_check = pipe(pipefd_terminal);
    if(error_check == -1)
    {
        fprintf(stderr, "Error on pipe system call.\n");
        exit(1);
    }
    int pipefd_shell[2]; // read is [0] ; write is [1]
    error_check = pipe(pipefd_shell);
    if(error_check == -1)
    {
        fprintf(stderr, "Error on pipe system call.\n");
        exit(1);
    }
    
    // FORK AND EXEC A SHELL
    
    pid_t pid = fork();
    if(pid == -1) // ERROR CHECK
    {
        fprintf(stderr, "Error on fork system call.\n");
        exit(1);
    }
    
    else if(pid == 0) // CHILD (the shell)
    {
        close(pipefd_terminal[0]);
        close(pipefd_shell[1]);
        // KEEP terminal[1] write (we write to the terminal) and shell[0] read (we read from the terminal)
        
        close(0);
        dup(pipefd_shell[0]);
        
        close(1);
        dup(pipefd_terminal[1]);
        close(2);
        dup(pipefd_terminal[1]);
        close(pipefd_terminal[1]);
        
        // TURN INTO BASH SHELL
        
        error_check = execl("/bin/bash", "bash", (char*) NULL);
        if(error_check == -1)
        {
            fprintf(stderr, "Error on exec system call.\n");
            exit(1);
        }
    }
    
    else // PARENT (the terminal)
    {
        close(pipefd_terminal[1]);
        close(pipefd_shell[0]);
        // KEEP terminal[0] read (we read from the shell) and shell[1] write (we write to the shell)
        
        // POLL
        
        struct pollfd poll_list[2]; // [0] will be socket/accept_fd ; [1] will be pipefd_terminal[0]/shell input
        
        poll_list[0].fd = accept_fd;
        poll_list[0].events = POLLIN;
        poll_list[0].revents = 0;
        
        poll_list[1].fd = pipefd_terminal[0];
        poll_list[1].events = POLLIN|POLLERR|POLLHUP;
        poll_list[1].revents = 0;
        
        struct z_stream_s decompress_from_socket;
        decompress_from_socket.zalloc = Z_NULL;
        decompress_from_socket.zfree = Z_NULL;
        decompress_from_socket.opaque = Z_NULL;
        
        struct z_stream_s compress_to_socket;
        compress_to_socket.zalloc = Z_NULL;
        compress_to_socket.zfree = Z_NULL;
        compress_to_socket.opaque = Z_NULL;
        
        while(1)
        {
            int poll_return = poll(poll_list, 2, 0);
            if(poll_return == -1)
            {
                fprintf(stderr, "Error on poll system call.\n");
                exit(1);
            }
            
            if(poll_list[0].revents & POLLIN) // input from socket
            {
                // READ FROM SOCKET
                
                char buffer_stdin[512];
                size_t read_size_stdin = read(accept_fd, &buffer_stdin, 16);
                if((int)read_size_stdin == -1)
                {
                    fprintf(stderr, "Error on read system call.\n");
                    exit(1);
                }
                
                if(compress_flag == 0)
                {
                    size_t i;
                    for(i = 0; i < read_size_stdin; i++)
                    {
                        if((int)buffer_stdin[i] == '\r' || (int)buffer_stdin[i] == '\n') //check carriage return and newline
                        {
                            size_t error_check = write(pipefd_shell[1], "\n", 1); // write to shell
                            if((int)error_check == -1)
                            {
                                fprintf(stderr, "Error on write system call.\n");
                                exit(1);
                            }
                        }
                        else if(buffer_stdin[i] == 0x03) // ^C
                        {
                            int err = kill(pid, SIGINT);
                            if(err == -1)
                            {
                                fprintf(stderr, "Error on kill system call.\n");
                                exit(1);
                            }
    //                        size_t error_check = write(accept_fd, "^C", 2);
    //                        if((int)error_check == -1)
    //                        {
    //                            fprintf(stderr, "Error on write system call.\n");
    //                            exit(1);
    //                        }
                        }
                        else if(buffer_stdin[i] == 0x04) // ^D
                        {
                            close(pipefd_shell[1]);
    //                        size_t error_check = write(accept_fd, "^D", 2);
    //                        if((int)error_check == -1)
    //                        {
    //                            fprintf(stderr, "Error on write system call.\n");
    //                            exit(1);
    //                        }
                            break;
                        }
                        else if(buffer_stdin[i] == EOF)
                        {
                            break;
                        }
                        else
                        {
                            size_t error_check = write(pipefd_shell[1], &buffer_stdin[i], 1); // write to shell
                            if((int)error_check == -1)
                            {
                                fprintf(stderr, "Error on write system call.\n");
                                exit(1);
                            }
                        }
                    }
                }
                else // DECOMPRESS FROM SOCKET
                {
                    char compression_buffer[512];
                    int compression_buffer_size = 512;
                    //memcpy(compression_buffer, buffer_stdin, read_size_stdin);
                    
                    
                    decompress_from_socket.next_in = (Bytef *)buffer_stdin;
                    decompress_from_socket.avail_in = (uInt)read_size_stdin;
                    decompress_from_socket.next_out = (Bytef *)compression_buffer;
                    decompress_from_socket.avail_out = (uInt)compression_buffer_size;
                    
                    int z_error = inflateInit(&decompress_from_socket);
                    if(z_error != Z_OK)
                    {
                        fprintf(stderr, "Error on inflateInit call.\n");
                        exit(1);
                    }
                    
                    while(1)
                    {
                        int z_error = inflate(&decompress_from_socket, Z_SYNC_FLUSH);
                        if(z_error != Z_OK)
                        {
                            fprintf(stderr, "Error on inflate call.\n");
                            exit(1);
                        }
                        if(decompress_from_socket.avail_in <= 0)
                        {
                            break;
                        }
                    }
                    
                    int actual_compression_size = compression_buffer_size - decompress_from_socket.avail_out;
                    
                    int i;
                    for(i = 0; i < actual_compression_size; i++)
                    {
                        if((int)compression_buffer[i] == '\r' || (int)compression_buffer[i] == '\n') //check carriage return and newline
                        {
                            size_t error_check = write(pipefd_shell[1], "\n", 1); // write to shell
                            if((int)error_check == -1)
                            {
                                fprintf(stderr, "Error on write system call.\n");
                                exit(1);
                            }
                        }
                        else if(compression_buffer[i] == 0x03) // ^C
                        {
                            int err = kill(pid, SIGINT);
                            if(err == -1)
                            {
                                fprintf(stderr, "Error on kill system call.\n");
                                exit(1);
                            }
    //                        size_t error_check = write(accept_fd, "^C", 2);
    //                        if((int)error_check == -1)
    //                        {
    //                            fprintf(stderr, "Error on write system call.\n");
    //                            exit(1);
    //                        }
                        }
                        else if(compression_buffer[i] == 0x04) // ^D
                        {
                            close(pipefd_shell[1]);
    //                        size_t error_check = write(accept_fd, "^D", 2);
    //                        if((int)error_check == -1)
    //                        {
    //                            fprintf(stderr, "Error on write system call.\n");
    //                            exit(1);
    //                        }
                            break;
                        }
                        else if(compression_buffer[i] == EOF)
                        {
                            break;
                        }
                        else
                        {
                            size_t error_check = write(pipefd_shell[1], &compression_buffer[i], 1); // write to shell
                            if((int)error_check == -1)
                            {
                                fprintf(stderr, "Error on write system call.\n");
                                exit(1);
                            }
                        }
                    }
                    
                }
            }
            if(poll_list[1].revents & POLLIN) // input from shell
            {
                // READ FROM SHELL
                
                char buffer_shell[512];
                size_t read_size_shell = read(pipefd_terminal[0], buffer_shell, 512);
                if((int)read_size_shell == -1)
                {
                    fprintf(stderr, "Error on read system call.\n");
                    exit(1);
                }
                if(compress_flag == 0)
                {
                    size_t i;
                    for(i = 0; i < read_size_shell; i++)
                    {
                        if((int)buffer_shell[i] == '\n') //check newline
                        {
                            size_t error_check = write(accept_fd, "\r\n", 2); // echo to socket
                            if((int)error_check == -1)
                            {
                                fprintf(stderr, "Error on write system call.\n");
                                exit(1);
                            }
                        }
                        else if(buffer_shell[i] == EOF)
                        {
                            break;
                        }
                        else
                        {
                            size_t error_check = write(accept_fd, &buffer_shell[i], 1); // echo to socket
                            if((int)error_check == -1)
                            {
                                fprintf(stderr, "Error on write system call.\n");
                                exit(1);
                            }
                        }
                    }
                }
                else // COMPRESS TO SOCKET
                {
                    size_t i;
                    for(i = 0; i < read_size_shell; i++)
                    {
                        if(buffer_shell[i] == EOF)
                        {
                            break;
                        }
                    }
                    char compression_buffer[512];
                    int compression_buffer_size = 512;
                    //memcpy(compression_buffer, buffer_shell, read_size_shell);
                    
                    compress_to_socket.next_in = (Bytef *)buffer_shell;
                    compress_to_socket.avail_in = (uInt)read_size_shell;
                    compress_to_socket.next_out = (Bytef *)compression_buffer;
                    compress_to_socket.avail_out = (uInt)compression_buffer_size;
                    
                    int z_error = deflateInit(&compress_to_socket, Z_DEFAULT_COMPRESSION);
                    if(z_error != Z_OK)
                    {
                        fprintf(stderr, "Error on deflateInit call.\n");
                        exit(1);
                    }
                    
                    while(1)
                    {
                        int z_error = deflate(&compress_to_socket, Z_SYNC_FLUSH);
                        if(z_error != Z_OK)
                        {
                            fprintf(stderr, "Error on deflate call.\n");
                            exit(1);
                        }
                        if(compress_to_socket.avail_in <= 0)
                        {
                            break;
                        }
                    }
                    
                    int actual_compression_size = compression_buffer_size - compress_to_socket.avail_out;
                    
                    size_t error_check = write(accept_fd, compression_buffer, actual_compression_size); // echo to socket
                    if((int)error_check == -1)
                    {
                        fprintf(stderr, "Error on write system call.\n");
                        exit(1);
                    }
                            
                    
                }

            }
            if(poll_list[1].revents & (POLLHUP + POLLERR))
            {
                break;
            }
        }
        
        // SHUT DOWN
        inflateEnd(&decompress_from_socket);
//        if(z_error != Z_OK)
//        {
//            fprintf(stderr, "Error on inflateEnd call.\n");
//            exit(1);
//        }

        int status;
        waitpid(pid, &status, 0);
        int lower_order = status & 127;
        int higher_order = status & 16256;
        fprintf(stderr, "\r\nSHELL EXIT SIGNAL=%d STATUS=%d\r\n", lower_order, higher_order);
        int error_check_shutdown = shutdown(accept_fd, SHUT_RDWR);
        if(error_check_shutdown == -1)
        {
            fprintf(stderr, "Error on shutdown system call.\n");
            exit(1);
        }
        deflateEnd(&compress_to_socket);
//        if(z_error != Z_OK)
//        {
//            printf("%d", z_error);
//            printf("%s", decompress_from_socket.msg);
//            fprintf(stderr, "Error on deflateEnd call.\n");
//            exit(1);
//        }
        exit(0);
    }
    
    return 0;
}
