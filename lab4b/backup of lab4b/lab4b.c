// Jake Herron
// UID: 005113997
// jakeh524@gmail.com

#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <time.h>
#include <strings.h>
#include <fcntl.h>
#include <math.h>
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
    //int temperature_sensor = 1;
    
    mraa_gpio_context button;
    button = mraa_gpio_init(60);
    //int button = 60;
    mraa_gpio_dir(button, MRAA_GPIO_IN);
    mraa_gpio_isr(button, MRAA_GPIO_EDGE_RISING, &button_pressed, NULL);
    
    
    
    while(run_flag == 1)
    {
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

        sleep(period);
    }
    


    // DEVICE CLOSE
    mraa_aio_close(temperature_sensor);
    mraa_gpio_close(button);
    return(0);
}
