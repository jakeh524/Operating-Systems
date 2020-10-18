// Jake Herron
// 005113997
// jakeh524@gmail.com

#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <poll.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>

void set_input_mode(void);
void reset_input_mode(void); // method to reset back to original terminal mode
void exiter(pid_t pid); // used to help shut down the program

struct termios saved_attr; // original terminal mode

int main(int argc, char * argv[]) {
    
    //ARGUMENT PARSING
    
    extern char *optarg;
    
    int shell_flag = 0;
    
    static struct option long_options[] = {
        {"shell", no_argument, 0, 's'},
        {0, 0, 0, 0}
    };
    
    char c;
    
    while((c=getopt_long(argc,argv,"s",long_options,NULL)) != -1) {
        switch(c){
            case 's': // shell
                shell_flag = 1;
                break;
            case '?': //unknown arg
                fprintf(stderr, "Unrecognized argument present. Use either no arguments or '--shell'.\n");
                exit(1);
                break;
        }
    }
    
    // TERMIOS
    
    set_input_mode();
    
    // READ AND WRITE CHAR-AT-A-TIME NO SHELL OPTION
    
    if(shell_flag == 0)
    {
        char buffer[512];
        size_t read_size;
        while((read_size = read(STDIN_FILENO, buffer, 16)) > 0)
        {
            if((int)read_size == -1)
            {
                fprintf(stderr, "Error on read system call.\n");
                exit(1);
            }
            size_t i;
            for(i = 0; i < read_size; i++)
            {
                if(buffer[i] == '\n' || buffer[i] == '\r') //check carriage return and newline
                {
                    size_t error_check = write(STDOUT_FILENO, "\r\n", 2);
                    if((int)error_check == -1)
                    {
                        fprintf(stderr, "Error on write system call.\n");
                        exit(1);
                    }
                }
                else if(buffer[i] == 0x4) //check ^D
                {
                    size_t error_check = write(STDOUT_FILENO, "^D", 2);
                    if((int)error_check == -1)
                    {
                        fprintf(stderr, "Error on write system call.\n");
                        exit(1);
                    }
                    reset_input_mode();
                    exit(0);
                }
                else
                {
                    size_t error_check = write(STDOUT_FILENO, buffer, 1);
                    if((int)error_check == -1)
                    {
                        fprintf(stderr, "Error on write system call.\n");
                        exit(1);
                    }
                }
            }
        }
    }
    // SHELL ARGUMENT
    else
    {
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
            
//            dup2(pipefd_shell[0], 0);
//            close(pipefd_shell[0]);
//
//            dup2(pipefd_terminal[1], 1);
//            dup2(pipefd_terminal[1], 2);
//            close(pipefd_terminal[1]);
            
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
            
            struct pollfd poll_list[2]; // [0] will be STDIN/keyboard ; [1] will be pipefd_terminal[0]/shell input
            
            poll_list[0].fd = STDIN_FILENO;
            poll_list[0].events = POLLIN;
            poll_list[0].revents = 0;
            
            poll_list[1].fd = pipefd_terminal[0];
            poll_list[1].events = POLLIN|POLLERR|POLLHUP;
            poll_list[1].revents = 0;
            
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
                            error_check = write(pipefd_shell[1], "\n", 1); // write to shell
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
                            size_t error_check = write(1, "^C", 2);
                            if((int)error_check == -1)
                            {
                                fprintf(stderr, "Error on write system call.\n");
                                exit(1);
                            }
                        }
                        else if(buffer_stdin[i] == 0x04) // ^D
                        {
                            close(pipefd_shell[1]);
                            size_t error_check = write(1, "^D", 2);
                            if((int)error_check == -1)
                            {
                                fprintf(stderr, "Error on write system call.\n");
                                exit(1);
                            }
                            break;
                        }
                        else
                        {
                            size_t error_check = write(1, &buffer_stdin[i], 1); // echo to screen
                            if((int)error_check == -1)
                            {
                                fprintf(stderr, "Error on write system call.\n");
                                exit(1);
                            }
                            error_check = write(pipefd_shell[1], &buffer_stdin[i], 1); // write to shell
                            if((int)error_check == -1)
                            {
                                fprintf(stderr, "Error on write system call.\n");
                                exit(1);
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
                    size_t i;
                    for(i = 0; i < read_size_shell; i++)
                    {
                        if((int)buffer_shell[i] == '\n') //check newline
                        {
                            size_t error_check = write(1, "\r\n", 2); // echo to screen
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
                            size_t error_check = write(1, &buffer_shell[i], 1); // echo to screen
                            if((int)error_check == -1)
                            {
                                fprintf(stderr, "Error on write system call.\n");
                                exit(1);
                            }
                        }
                    }
                }
                if(poll_list[1].revents & (POLLHUP + POLLERR))
                {
                    break;
                }
            }
            exiter(pid);
        }
    }
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

void exiter(pid_t pid)
{
    int status;
    waitpid(pid, &status, 0);
    int lower_order = status & 127;
    int higher_order = status & 16256;
    fprintf(stderr, "\r\nSHELL EXIT SIGNAL=%d STATUS=%d\r\n", lower_order, higher_order);
    reset_input_mode();
    exit(0);
}
