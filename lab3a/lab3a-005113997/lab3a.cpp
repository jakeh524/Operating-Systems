// Jake Herron
// 00513397
// jakeh524@gmail.com

#include <unistd.h>
#include <time.h>
#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include "ext2_fs.h"
using namespace std;

#define SUPERBLOCK_OFFSET   1024

char* fs_image_string;
int fs_image_fd;
struct ext2_super_block super_block;
int block_size;
struct ext2_group_desc group_desc;


void superblock_func();
void group_func();
void freeblock_func();
void freeinode_func();
void inode_func();

int main(int argc, char * argv[])
{
    // ARGUMENT PARSING
    
    if(argc != 2)
    {
        fprintf(stderr, "Wrong number of arguments. Should only be name of file system image.\n");
        exit(1);
    }
    fs_image_string = argv[1];
    fs_image_fd = open(fs_image_string, O_RDONLY);
    if(fs_image_fd == -1)
    {
        fprintf(stderr, "Error on open system call.\n");
        exit(1);
    }
    
    //superblock summary
    superblock_func();

    //group summary
    group_func();
    
    //free block entries
    freeblock_func();
    
    //free inode entries
    freeinode_func();
    
    //inode summary, directory entries, and indirect block references
    inode_func();

    return(0);
    
}

void superblock_func()
{
    ssize_t pread_size = pread(fs_image_fd, &super_block, sizeof(struct ext2_super_block), SUPERBLOCK_OFFSET);
    if(pread_size == -1)
    {
        fprintf(stderr, "Error on pread system call in superblock function.\n");
        exit(1);
    }
    block_size = EXT2_MIN_BLOCK_SIZE << super_block.s_log_block_size;
    printf("SUPERBLOCK,%d,%d,%d,%d,%d,%d,%d\n", super_block.s_blocks_count, super_block.s_inodes_count, block_size, super_block.s_inode_size, super_block.s_blocks_per_group, super_block.s_inodes_per_group, super_block.s_first_ino);
}

void group_func()
{
    ssize_t pread_size = pread(fs_image_fd, &group_desc, sizeof(group_desc), SUPERBLOCK_OFFSET + block_size);
    if(pread_size == -1)
    {
        fprintf(stderr, "Error on pread system call in group function.\n");
        exit(1);
    }
    
    printf("GROUP,%d,%d,%d,%d,%d,%d,%d,%d\n", 0, super_block.s_blocks_count, super_block.s_inodes_count, group_desc.bg_free_blocks_count, group_desc.bg_free_inodes_count, group_desc.bg_block_bitmap, group_desc.bg_inode_bitmap, group_desc.bg_inode_table);
}

void freeblock_func()
{
    int block_bitmap_offset = (group_desc.bg_block_bitmap - 1)*block_size + SUPERBLOCK_OFFSET;
    char* block_bitmap = (char*)malloc(block_size);
    pread(fs_image_fd, block_bitmap, block_size, block_bitmap_offset);
    int total_blocks = super_block.s_blocks_count;
    char* block_byte_array = (char*)malloc(total_blocks);
    for(int i = 0, j = 0; i < total_blocks/8; i++)
    {
        unsigned char byte = block_bitmap[i];
        for(int count = 0; count < 8; count++, j++)
        {
            block_byte_array[j] = (byte & 0x01 ? '1' : '0');
            byte = byte >> 1;
        }
    }
    for(int i = 0; i < total_blocks; i++)
    {
        if(block_byte_array[i] == '0')
        {
            printf("BFREE,%d\n", i+1);
        }
    }
    free(block_bitmap);
    free(block_byte_array);
}

void freeinode_func()
{
    int inode_bitmap_offset = (group_desc.bg_inode_bitmap - 1)*block_size + SUPERBLOCK_OFFSET;
    char* inode_bitmap = (char*)malloc(block_size);
    pread(fs_image_fd, inode_bitmap, block_size, inode_bitmap_offset);
    int total_inodes = super_block.s_inodes_count;
    char* inode_byte_array = (char*)malloc(total_inodes);
    for(int i = 0, j = 0; i < total_inodes/8; i++)
    {
        unsigned char byte = inode_bitmap[i];
        for(int count = 0; count < 8; count++, j++)
        {
            inode_byte_array[j] = (byte & 0x01 ? '1' : '0');
            byte = byte >> 1;
        }
    }
    for(int i = 0; i < total_inodes; i++)
    {
        if(inode_byte_array[i] == '0')
        {
            printf("IFREE,%d\n", i+1);
        }
    }
    free(inode_bitmap);
    free(inode_byte_array);
}

void inode_func()
{
    int inode_table_offset = (group_desc.bg_inode_table - 1)*block_size + SUPERBLOCK_OFFSET;
    ext2_inode *inode_table = (ext2_inode*)malloc(sizeof(ext2_inode) * super_block.s_inodes_count);
    pread(fs_image_fd, inode_table, sizeof(ext2_inode) * super_block.s_inodes_count, inode_table_offset);
    int total_inodes = super_block.s_inodes_count;
    for(int i = 0; i < total_inodes; i++)
    {
        ext2_inode current_inode = inode_table[i];
        if(current_inode.i_mode == 0 || current_inode.i_links_count == 0)
        {
            continue;
        }
        
        //inode number
        int inode_number = i+1;
        
        // file type
        char file_type = '?';
        if((current_inode.i_mode & 0xA000) == 0xA000)
        {
            file_type = 's';
        }
        else if((current_inode.i_mode & 0x8000) == 0x8000)
        {
            file_type = 'f';
        }
        else if((current_inode.i_mode & 0x4000) == 0x4000)
        {
            file_type = 'd';
        }
        
        // mode
        __u16 inode_mode = current_inode.i_mode & 0x0FFF;
        
        //owner
        __u16 inode_owner = current_inode.i_uid;
        
        //group
        __u16 inode_group = current_inode.i_gid;
        
        //link count
        __u16 inode_links = current_inode.i_links_count;
        
        //inode change time
        char inode_change_time[20];
        time_t change_time = current_inode.i_ctime;
        tm *inode_time_c = gmtime(&change_time);
        strftime(inode_change_time, sizeof(inode_change_time), "%m/%d/%y %H:%M:%S", inode_time_c);
        
        //modification time
        char inode_mod_time[20];
        time_t mod_time = current_inode.i_mtime;
        tm *inode_time_m = gmtime(&mod_time);
        strftime(inode_mod_time, sizeof(inode_mod_time), "%m/%d/%y %H:%M:%S", inode_time_m);
        
        //last access time
        char inode_access_time[20];
        time_t access_time = current_inode.i_atime;
        tm *inode_time_a = gmtime(&access_time);
        strftime(inode_access_time, sizeof(inode_access_time), "%m/%d/%y %H:%M:%S", inode_time_a);
        
        //file size
        __u32 inode_file_size = current_inode.i_size;
        
        //number of blocks
        __u32 inode_num_blocks = current_inode.i_blocks;
        
        printf("INODE,%d,%c,%o,%d,%d,%d,%s,%s,%s,%d,%d", inode_number, file_type, inode_mode, inode_owner, inode_group, inode_links, inode_change_time, inode_mod_time, inode_access_time, inode_file_size, inode_num_blocks);
        
        //next 15 fields
        if(file_type == 'f' || file_type == 'd') // files or directories
        {
            printf(",");
            int i = 0;
            while(i < EXT2_N_BLOCKS-1)
            {
                printf("%d,", current_inode.i_block[i]);
                i++;
            }
            printf("%d\n", current_inode.i_block[i]);
        }
        else if(file_type == 's') // symbolic links
        {
            if(current_inode.i_fsize < 60)
            {
                printf("\n");
            }
            else
            {
                printf(",");
                int i = 0;
                while(i < EXT2_N_BLOCKS-1)
                {
                    printf("%d,", current_inode.i_block[i]);
                    i++;
                }
                printf("%d\n", current_inode.i_block[i]);
            }
        }
        
        // directory entries
        if(file_type == 'd')
        {
            //iterate through blocks
            for(int j = 0; j < EXT2_NDIR_BLOCKS; j++)
            {
                if(current_inode.i_block[j] == 0)
                {
                    continue;
                }
                //iterate through dir entries
                int offset = 0;
                while(offset < block_size)
                {
                    ext2_dir_entry current_dir;
                    int current_dir_offset = offset + block_size*current_inode.i_block[j];
                    pread(fs_image_fd, &current_dir, sizeof(ext2_dir_entry), current_dir_offset);
                    int logic_byte_offset = offset;
                    offset += current_dir.rec_len;
                    if(current_dir.name_len == 0)
                    {
                        continue;
                    }
                    //process the directory
                    printf("DIRENT,%d,%d,%d,%d,%d,'%s'\n", inode_number, logic_byte_offset, current_dir.inode, current_dir.rec_len, current_dir.name_len, current_dir.name);
                }
            }
        }
        
        //single indirect block references
        if((file_type == 'd' || file_type == 'f') && current_inode.i_block[EXT2_IND_BLOCK] != 0)
        {
            int single_indirect_block = current_inode.i_block[EXT2_IND_BLOCK];
            int *single_indirect_block_array = (int*)malloc(block_size);
            int single_block_indirect_offset = block_size*single_indirect_block;
            pread(fs_image_fd, single_indirect_block_array, block_size, single_block_indirect_offset);
            int size_of_array = block_size/sizeof(__u32);
            for(int j = 0; j < size_of_array; j++)
            {
                int current_block_num = single_indirect_block_array[j];
                if(current_block_num == 0)
                {
                    continue;
                }
                printf("INDIRECT,%d,%d,%d,%d,%d\n", inode_number, 1, (EXT2_IND_BLOCK + j), single_indirect_block, current_block_num);
            }
            free(single_indirect_block_array);
        }
        
        //double indirect block references
        if((file_type == 'd' || file_type == 'f') && current_inode.i_block[EXT2_DIND_BLOCK] != 0)
        {
            int double_indirect_block = current_inode.i_block[EXT2_DIND_BLOCK];
            int *double_indirect_block_array = (int*)malloc(block_size);
            int double_block_indirect_offset = block_size*double_indirect_block;
            pread(fs_image_fd, double_indirect_block_array, block_size, double_block_indirect_offset);
            int size_of_array = block_size/sizeof(__u32);
            for(int k = 0; k < size_of_array; k++)
            {
                int double_current_block_num = double_indirect_block_array[k];
                if(double_current_block_num == 0)
                {
                    continue;
                }
                printf("INDIRECT,%d,%d,%d,%d,%d\n", inode_number, 2, (256 + EXT2_IND_BLOCK + k), double_indirect_block, double_current_block_num);
                
                if((file_type == 'd' || file_type == 'f') && current_inode.i_block[EXT2_IND_BLOCK] != 0)
                {
                    int single_indirect_block = double_current_block_num;
                    int *single_indirect_block_array = (int*)malloc(block_size);
                    int single_block_indirect_offset = block_size*single_indirect_block;
                    pread(fs_image_fd, single_indirect_block_array, block_size, single_block_indirect_offset);
                    int size_of_array = block_size/sizeof(__u32);
                    for(int j = 0; j < size_of_array; j++)
                    {
                        int current_block_num = single_indirect_block_array[j];
                        if(current_block_num == 0)
                        {
                            continue;
                        }
                        printf("INDIRECT,%d,%d,%d,%d,%d\n", inode_number, 1, (256 + EXT2_IND_BLOCK + j), single_indirect_block, current_block_num);
                    }
                    free(single_indirect_block_array);
                }
            }
            free(double_indirect_block_array);
        }
        
        //triple indirect block references
        if((file_type == 'd' || file_type == 'f') && current_inode.i_block[EXT2_TIND_BLOCK] != 0)
        {
            int triple_indirect_block = current_inode.i_block[EXT2_TIND_BLOCK];
            int *triple_indirect_block_array = (int*)malloc(block_size);
            int triple_block_indirect_offset = block_size*triple_indirect_block;
            pread(fs_image_fd, triple_indirect_block_array, block_size, triple_block_indirect_offset);
            int size_of_array = block_size/sizeof(__u32);
            for(int l = 0; l < size_of_array; l++)
            {
                int triple_current_block_num = triple_indirect_block_array[l];
                if(triple_current_block_num == 0)
                {
                    continue;
                }
                printf("INDIRECT,%d,%d,%d,%d,%d\n", inode_number, 3, (65536 + 256 + EXT2_IND_BLOCK + l), triple_indirect_block, triple_current_block_num);
                
                if((file_type == 'd' || file_type == 'f') && current_inode.i_block[EXT2_DIND_BLOCK] != 0)
                {
                    int double_indirect_block = triple_current_block_num;
                    int *double_indirect_block_array = (int*)malloc(block_size);
                    int double_block_indirect_offset = block_size*double_indirect_block;
                    pread(fs_image_fd, double_indirect_block_array, block_size, double_block_indirect_offset);
                    int size_of_array = block_size/sizeof(__u32);
                    for(int k = 0; k < size_of_array; k++)
                    {
                        int double_current_block_num = double_indirect_block_array[k];
                        if(double_current_block_num == 0)
                        {
                            continue;
                        }
                        printf("INDIRECT,%d,%d,%d,%d,%d\n", inode_number, 2, (65536 + 256 + EXT2_IND_BLOCK + k), double_indirect_block, double_current_block_num);
                        
                        if((file_type == 'd' || file_type == 'f') && current_inode.i_block[EXT2_IND_BLOCK] != 0)
                        {
                            int single_indirect_block = double_current_block_num;
                            int *single_indirect_block_array = (int*)malloc(block_size);
                            int single_block_indirect_offset = block_size*single_indirect_block;
                            pread(fs_image_fd, single_indirect_block_array, block_size, single_block_indirect_offset);
                            int size_of_array = block_size/sizeof(__u32);
                            for(int j = 0; j < size_of_array; j++)
                            {
                                int current_block_num = single_indirect_block_array[j];
                                if(current_block_num == 0)
                                {
                                    continue;
                                }
                                printf("INDIRECT,%d,%d,%d,%d,%d\n", inode_number, 1, (65536 + 256 + EXT2_IND_BLOCK + j), single_indirect_block, current_block_num);
                            }
                            free(single_indirect_block_array);
                        }
                    }
                    free(double_indirect_block_array);
                }
            }
            free(triple_indirect_block_array);
        }
    }
    free(inode_table);
}
