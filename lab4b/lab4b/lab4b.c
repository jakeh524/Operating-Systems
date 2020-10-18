// Jake Herron
// UID: 005113997
// jakeh524@gmail.com

#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <strings.h>
#include <fcntl.h>
#include <math.h>
#include <poll.h>
#include <unistd.h>
#include <fcntl.h>
#include <mraa.h>

const int B = 4275;               // B value of the thermistor
const int R0 = 100000;            // R0 = 100k

int period = 1;
char scale = 'F';
int log_flag = 0;
char *log_file;
FILE *log_fp;
int run_flag = 1;
time_t basic_time;
struct tm *local_time;

void button_pressed() // shutdown
{
    run_flag = 0;
    time(&basic_time);
    local_time = localtime(&basic_time);
    fprintf(stdout, "%02d:%02d:%02d SHUTDOWN\n", local_time->tm_hour, local_time->tm_min, local_time->tm_sec);
    if(log_flag == 1)
    {
        fprintf(log_fp, "%02d:%02d:%02d SHUTDOWN\n", local_time->tm_hour, local_time->tm_min, local_time->tm_sec);
    }
    exit(0);
}

int main(int argc, char * argv[]) {
    
    //ARGUMENT PARSING

    extern char *optarg;

    static struct option long_options[] = {
    {"period", required_argument, 0, 'p'},
    {"scale", required_argument, 0, 's'},
    {"log", required_argument, 0, 'l'},
    {0, 0, 0, 0}
    };

    signed char c;

    while((c=getopt_long(argc,argv,"p:s:l:",long_options,NULL)) != -1) {
    switch(c){
        case 'p': // period
            period = atoi(optarg);
            break;
        case 's': // scale
            if(*optarg == 'C') // Celsius
            {
                scale = *optarg;
                break;
            }
            else if(*optarg == 'F') // Fareneheit
            {
                scale = *optarg;
                break;
            }
            else // invald arg
            {
                fprintf(stderr, "Invalid scale argument.\n");
                exit(1);
                break;
            }
        case 'l': // log
            log_flag = 1;
            log_file = optarg;
            break;
        case '?': //unknown arg
            fprintf(stderr, "Unrecognized argument present.\n");
            exit(1);
            break;
        }
    }
    if(log_flag == 1)
    {
        log_fp = fopen(log_file, "a+");
        if(log_fp == NULL)
        {
            fprintf(stderr, "Error on fopen system call.\n");
            exit(1);
        }
    }
    
    // DEVICE INITIALIZATION
    
    mraa_aio_context temperature_sensor;
    temperature_sensor = mraa_aio_init(1);
    if(temperature_sensor == NULL)
    {
        fprintf(stderr, "Error on temperature initializer call.\n");
        exit(1);
    }
    
    mraa_gpio_context button;
    button = mraa_gpio_init(60);
    if(button == NULL)
    {
        fprintf(stderr, "Error on button initializer call.\n");
        exit(1);
    }
    mraa_gpio_dir(button, MRAA_GPIO_IN);
    mraa_gpio_isr(button, MRAA_GPIO_EDGE_RISING, &button_pressed, NULL);
    
    // FILE DESCRIPTOR INITIALIZATION
    fcntl(0, F_SETFL, O_NONBLOCK);

    int temp_flag = 1;
    
    while(run_flag == 1)
    {
        if(temp_flag == 1)
        {
            // TEMPERATURE PROCESSING
            
            int a = mraa_aio_read(temperature_sensor);
            if(a == -1)
            {
                fprintf(stderr, "Error on mraa_aio_read call.\n");
                exit(1);
            }
            float R = 1023.0/a-1.0;
            R = R0*R;
            float temperature_celsius = 1.0/(log(R/R0)/B+1/298.15)-273.15;
            float temperature_farenheit = temperature_celsius * (9/5) + 32;
            time(&basic_time);
            local_time = localtime(&basic_time);
            
            if(scale == 'F')
            {
                fprintf(stdout, "%02d:%02d:%02d %.1f\n", local_time->tm_hour, local_time->tm_min, local_time->tm_sec, temperature_farenheit);
                if(log_flag == 1)
                {
                    fprintf(log_fp, "%02d:%02d:%02d %.1f\n", local_time->tm_hour, local_time->tm_min, local_time->tm_sec, temperature_farenheit);
                }
            }
            else if(scale == 'C')
            {
                fprintf(stdout, "%02d:%02d:%02d %.1f\n", local_time->tm_hour, local_time->tm_min, local_time->tm_sec, temperature_celsius);
                if(log_flag == 1)
                {
                    fprintf(log_fp, "%02d:%02d:%02d %.1f\n", local_time->tm_hour, local_time->tm_min, local_time->tm_sec, temperature_celsius);
                }
            }
        }
        
        // STDIN COMMAND PROCESSING
        
        char buffer_stdin[512];
        size_t read_size_stdin = read(0, &buffer_stdin, 512);
        if((int)read_size_stdin < 0)
        {
            // do nothing until you read
        }
        else
        {
            char command_buffer[512] = {};
            size_t i;
            int command_iter;
            for(i = 0, command_iter = 0; i < read_size_stdin; i++)
            {
                if(buffer_stdin[i] == '\n')
                {
                    if(strcmp(command_buffer, "SCALE=F") == 0) // SCALE to Farenheit
                    {
                        scale = 'F';
                        if(log_flag == 1)
                        {
                            fprintf(log_fp, "SCALE=F\n");
                        }
                    }
                    else if(strcmp(command_buffer, "SCALE=C") == 0) // SCALE to Celsius
                    {
                        scale = 'C';
                        if(log_flag == 1)
                        {
                            fprintf(log_fp, "SCALE=C\n");
                        }
                    }
                    else if(strcmp(command_buffer, "START") == 0) // START command
                    {
                        temp_flag = 1;
                        if(log_flag == 1)
                        {
                            fprintf(log_fp, "START\n");
                        }
                    }
                    else if(strcmp(command_buffer, "STOP") == 0) // STOP command
                    {
                        temp_flag = 0;
                        if(log_flag == 1)
                        {
                            fprintf(log_fp, "STOP\n");
                        }
                    }
                    else if(strcmp(command_buffer, "OFF") == 0) // OFF command
                    {
                        if(log_flag == 1)
                        {
                            fprintf(log_fp, "OFF\n");
                        }
                        button_pressed();
                    }
                    else if(strstr(command_buffer, "PERIOD=") != NULL) // PERIOD command
                    {
                        int invalid_flag = 0;
                        int i;
                        int temp_period = 0;
                        int digits = 1;
                        for (i = 7; command_buffer[i] != '\n'; i++)
                        {
                            if(command_buffer[i] >= '0' && command_buffer[i] < '9') // if this char is a digit
                            {
                                int num = command_buffer[i] - '0';
                                temp_period = temp_period * digits;
                                digits = digits * 10;
                                temp_period += num;
                            }
                            else if(command_buffer[i] == 0) // look out for the null character
                            {
                                break;
                            }
                            else // check if there is not a digit after =
                            {
                                invalid_flag = 1;
                                break;
                            }
                        }
                        if(invalid_flag == 0) // if we found a number after the =
                        {
                            period = temp_period;
                            if(log_flag == 1)
                            {
                                fprintf(log_fp, "%s\n", command_buffer);
                            }
                        }
                        else if(invalid_flag == 1) // if it was not a number after the =
                        {
                            if(log_flag == 1)
                            {
                                fprintf(log_fp, "%s\n", command_buffer);
                            }
                        }
                    }
                    else // invalid command, log it
                    {
                        if(log_flag == 1)
                        {
                            fprintf(log_fp, "%s\n", command_buffer);
                        }
                    }
                    memset(command_buffer, 0, sizeof(command_buffer)); // reset command buffer after we process a command
                    command_iter = 0;
                }
                else // not a new line, still processing command
                {
                    command_buffer[command_iter] = buffer_stdin[i];
                    command_iter++;
                }
            }
        }
        sleep(period);
    }
    


    // DEVICE CLOSE
    mraa_aio_close(temperature_sensor);
    mraa_gpio_close(button);
    
    return(0);
}
