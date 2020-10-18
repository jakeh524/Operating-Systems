// Jake Herron
// UID: 005113997
// jakeh524@gmail.com

#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netdb.h>
#include <strings.h>
#include <termios.h>
#include <poll.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <zlib.h>

void set_input_mode(void);
void reset_input_mode(void); // method to reset back to original terminal mode

struct termios saved_attr; // original terminal mode



int main(int argc, char * argv[]) {
    
    //ARGUMENT PARSING
    
    extern char *optarg;
    
    int port_number = -1;
    int log_flag = 0;
    char *log_file;
    int log_fd = 1; // placeholder to avoid unit warning
    int compress_flag = 0;
    
    static struct option long_options[] = {
        {"port", required_argument, 0, 'p'},
        {"log", required_argument, 0, 'l'},
        {"compress", no_argument, 0, 'c'},
        {0, 0, 0, 0}
    };
    
    char c;
    
    while((c=getopt_long(argc,argv,"p:l:c",long_options,NULL)) != -1) {
        switch(c){
            case 'p': // port
                port_number = atoi(optarg); //convert port number (which is a string) to an int
                break;
            case 'l':
                log_flag = 1;
                log_file = optarg;
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
    if(log_flag == 1)
    {
        log_fd = open(log_file, O_CREAT | O_RDWR, 0666);
        if(log_fd == -1)
        {
            fprintf(stderr, "Error on open system call.\n");
            exit(1);
        }
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
    bzero(&address_struct,sizeof(struct sockaddr_in));
    address_struct.sin_family = AF_INET;
    address_struct.sin_port = htons(port_number);
    memcpy(&address_struct.sin_addr, host->h_addr_list[0], host->h_length);
    
    int connection_error_check = connect(socket_fd, (struct sockaddr *)&address_struct, sizeof(struct sockaddr));
    if(connection_error_check == -1)
    {
        fprintf(stderr, "Error on connect system call.\n");
        exit(1);
    }
    
    
    // TERMIOS SETUP
    
    set_input_mode();
    
    // POLL
    
    struct pollfd poll_list[2]; // [0] will be STDIN/keyboard ; [1] will be socket_fd/socket input
    
    poll_list[0].fd = STDIN_FILENO;
    poll_list[0].events = POLLIN;
    poll_list[0].revents = 0;
    
    poll_list[1].fd = socket_fd;
    poll_list[1].events = POLLIN|POLLERR|POLLHUP;
    poll_list[1].revents = 0;
    
    struct z_stream_s compress_to_socket;
    compress_to_socket.zalloc = Z_NULL;
    compress_to_socket.zfree = Z_NULL;
    compress_to_socket.opaque = Z_NULL;
    
    struct z_stream_s decompress_from_socket;
    decompress_from_socket.zalloc = Z_NULL;
    decompress_from_socket.zfree = Z_NULL;
    decompress_from_socket.opaque = Z_NULL;
    
    while(1)
    {
        int poll_return = poll(poll_list, 2, 0);
        if(poll_return == -1)
        {
            fprintf(stderr, "Error on poll system call.\n");
            exit(1);
        }
        
        
        if(poll_list[0].revents & POLLIN) // input from STDIN
        {
            // READ FROM KEYBOARD
            
            char buffer_stdin[512];
            size_t read_size_stdin = read(0, &buffer_stdin, 16);
            if((int)read_size_stdin == -1)
            {
                fprintf(stderr, "Error on read system call.\n");
                exit(1);
            }

            size_t i;
            for(i = 0; i < read_size_stdin; i++)
            {
                if((int)buffer_stdin[i] == '\r' || (int)buffer_stdin[i] == '\n') //check carriage return and newline
                {
                    size_t error_check = write(1, "\r\n", 2); // echo to screen
                    if((int)error_check == -1)
                    {
                        fprintf(stderr, "Error on write system call.\n");
                        exit(1);
                    }
                }
                else
                {
                    size_t error_check = write(1, &buffer_stdin[i], 1); // echo to screen
                    if((int)error_check == -1)
                    {
                        fprintf(stderr, "Error on write system call.\n");
                        exit(1);
                    }
                }
                if(compress_flag == 0)
                {
                    if(log_flag == 1)
                    {
                        char log_buffer[512];
                        memcpy(log_buffer, buffer_stdin, read_size_stdin);
                        dprintf(log_fd, "SENT %lu bytes: ", read_size_stdin);
                        write(log_fd, log_buffer, read_size_stdin);
                        write(log_fd, "\n", 1);
                    }
                    size_t error_check = write(socket_fd, &buffer_stdin[i], 1); // write to socket
                    if((int)error_check == -1)
                    {
                        fprintf(stderr, "Error on write system call.\n");
                        exit(1);
                    }
                }
                else // COMPRESS TO SOCKET
                {
                    char compression_buffer[512];
                    int compression_buffer_size = 512;
                    memcpy(compression_buffer, buffer_stdin, read_size_stdin);
                    
                    
                    compress_to_socket.next_in = (Bytef *)buffer_stdin;
                    compress_to_socket.avail_in = (uInt)read_size_stdin;
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
                    
                    if(log_flag == 1)
                    {
                        char log_buffer[512];
                        memcpy(log_buffer, compression_buffer, actual_compression_size);
                        dprintf(log_fd, "SENT %d bytes: ", actual_compression_size);
                        write(log_fd, log_buffer, actual_compression_size);
                        write(log_fd, "\n", 1);
                    }
                    size_t error_check = write(socket_fd, compression_buffer, actual_compression_size); // write to socket
                    if((int)error_check == -1)
                    {
                        fprintf(stderr, "Error on write system call.\n");
                        exit(1);
                    }
                    

                }
            }

        }
        
        if(poll_list[1].revents & POLLIN) // input from socket
        {
            // READ FROM SOCKET
            
            
            char buffer_shell[512];
            size_t read_size_shell = read(socket_fd, buffer_shell, 512);
            if((int)read_size_shell == -1)
            {
                fprintf(stderr, "Error on read system call.\n");
                exit(1);
            }
            
            if(compress_flag == 0)
            {
                if(log_flag == 1)
                {
                    char log_buffer[512];
                    memcpy(log_buffer, buffer_shell, read_size_shell);
                    dprintf(log_fd, "RECEIVED %lu bytes: ", read_size_shell);
                    write(log_fd, &log_buffer, read_size_shell);
                    write(log_fd, "\n", 1);
                }
                
                size_t i;
                for(i = 0; i < read_size_shell; i++)
                {
                    if(buffer_shell[i] == EOF)
                    {
                        break;
                    }
                    else
                    {
                        size_t error_check = write(1, &buffer_shell[i], 1); // echo to screen
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
                if(log_flag == 1)
                {
                    char log_buffer[512];
                    memcpy(log_buffer, buffer_shell, read_size_shell);
                    dprintf(log_fd, "RECEIVED %lu bytes: ", read_size_shell);
                    write(log_fd, &log_buffer, read_size_shell);
                    write(log_fd, "\n", 1);
                }
                
                char compression_buffer[512];
                int compression_buffer_size = 512;
                memcpy(compression_buffer, buffer_shell, read_size_shell);
                
                
                decompress_from_socket.next_in = (Bytef *)buffer_shell;
                decompress_from_socket.avail_in = (uInt)read_size_shell;
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
                    if(decompress_from_socket.avail_in <= 0)
                    {
                        break;
                    }
                    int z_error = inflate(&decompress_from_socket, Z_SYNC_FLUSH);
                    if(z_error != Z_OK)
                    {
                        fprintf(stderr, "Error on inflate call.\n");
                        exit(1);
                    }
                    if(z_error == Z_STREAM_END)
                    {
                        break;
                    }
                }
                
                
                int actual_compression_size = compression_buffer_size - decompress_from_socket.avail_out;
            
                 
                 int i;
                 for(i = 0; i < actual_compression_size; i++)
                 {
                     if((int)compression_buffer[i] == '\n') //check newline
                     {
                         size_t error_check = write(1, "\r\n", 2); // echo to screen
                         if((int)error_check == -1)
                         {
                             fprintf(stderr, "Error on write system call.\n");
                             exit(1);
                         }
                     }
                     else if(compression_buffer[i] == EOF)
                     {
                         break;
                     }
                     else
                     {
                         size_t error_check = write(1, &compression_buffer[i], 1); // echo to screen
                         if((int)error_check == -1)
                         {
                             fprintf(stderr, "Error on write system call.\n");
                             exit(1);
                         }
                     }
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
//    if(z_error != Z_OK)
//    {
//        fprintf(stderr, "Error on inflateEnd call.\n");
//        exit(1);
//    }
    deflateEnd(&compress_to_socket);
//    if(z_error != Z_OK)
//    {
////        printf("%d", z_error);
////        printf("%s", decompress_from_socket.msg);
//        fprintf(stderr, "Error on deflateEnd call.\n");
//        exit(1);
//    }
    reset_input_mode();
    exit(0);
    
    
    return 0;
}

//TERMIOS FUNCTIONS

void set_input_mode(void)
{
    int error_check;
    struct termios tattr;
    error_check = tcgetattr(STDIN_FILENO, &saved_attr);
    if(error_check == -1)
    {
        fprintf(stderr, "Error on termios tcgetattr.\n");
        exit(1);
    }
    error_check = tcgetattr(STDIN_FILENO, &tattr);
    if(error_check == -1)
    {
        fprintf(stderr, "Error on termios tcgetattr.\n");
        exit(1);
    }
    tattr.c_iflag = ISTRIP;
    tattr.c_oflag = 0;
    tattr.c_lflag = 0; // idk which one to do
    error_check = tcsetattr(STDIN_FILENO, TCSANOW, &tattr);
    if(error_check == -1)
    {
        fprintf(stderr, "Error on termios tcsetattr.\n");
        exit(1);
    }
}

void reset_input_mode(void)
{
    int error_check;
    error_check = tcsetattr(STDIN_FILENO, TCSANOW, &saved_attr);
    if(error_check == -1)
    {
        fprintf(stderr, "Error on termios tcsetattr.\n");
        exit(1);
    }
}
