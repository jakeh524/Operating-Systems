// Jake Herron
// 00513397
// jakeh524@gmail.com

#include <stdio.h>
#include <sys/types.h>
#include <string>
#include <stdint.h>
#include "ext2_fs.h"
using namespace std;

string fs_image;

int main(int argc, char * argv[])
{
    // ARGUMENT PARSING
    
    if(argc != 2)
    {
        fprintf(stderr, "Wrong number of arguments. Should only be name of file system image.\n");
        exit(1);
    }
    fs_image = argv[1];
    
    
    
    return(0);
    
}
