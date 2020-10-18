#!/usr/bin/env python3

"""
Jake Herron
005113997
jakeh524@gmail.com
"""

import sys, csv

csv_file = ""

def main(argv):
    input_csv_path = argv
    global input_csv
    try:
        input_csv = open(input_csv_path, 'r', newline='')
    except:
        print("File does not exist.", file=sys.stderr)
        exit(1)
    global csv_file
    csv_file = csv.reader(input_csv, delimiter=',', quotechar='"')

    inode_inconsistency_check()

    block_inconsistency_check()

    directory_inconsistency_check()



def inode_inconsistency_check():
    inode_count = 0
    global inode_free_list
    inode_free_list = []
    global inode_allocated_list
    inode_allocated_list = []
    for row in csv_file:
        if(row[0] == 'SUPERBLOCK'):
            inode_count = int(row[2])
        if(row[0] == 'IFREE'):
            inode_free_list += [int(row[1])]
        if(row[0] == 'INODE'):
            inode_allocated_list += [int(row[1])]

    for x in inode_free_list: #ALLOCATED ; if free and also in use
        if(x in inode_allocated_list):
            print("ALLOCATED INODE", x, "ON FREELIST")
    for x in range(1, inode_count+1): #UNALLOCATED; if not in either list but should be in one
        if(x == 1 or x in range(3, 11)): #reserved so don't check these
            continue
        elif(x not in inode_allocated_list and x not in inode_free_list):
            print("UNALLOCATED INODE", x, "NOT ON FREELIST")

def block_inconsistency_check():
    input_csv.seek(0)
    block_count = 0
    global inode_count
    inode_count = 0
    block_size = 0
    inode_size = 0
    inode_table_loc = 0
    first_block = 0
    free_block_list = []
    used_block_list = []
    dup_block_list = []
    for row in csv_file:
        if(row[0] == "SUPERBLOCK"):
            block_count = int(row[1])
            inode_count = int(row[2])
            block_size = int(row[3])
            inode_size = int(row[4])
        if(row[0] == "GROUP"):
            inode_table_loc = int(row[8])
            first_block = int(inode_table_loc + (inode_count * inode_size) / block_size)
        if(row[0] == "BFREE"):
            free_block_list += [int(row[1])]

    input_csv.seek(0)

    #INVALID, RESERVED, ALLOCATED
    for row in csv_file:
        if(row[0] == "INODE"):
            if(row[2] != 'f' and row[2] != 'd'):
                continue
            for i in range(12, 24):
                if(int(row[i]) < 0 or int(row[i]) > block_count): #invalid
                    print("INVALID BLOCK", int(row[i]), "IN INODE", int(row[1]), "AT OFFSET 0")
                if(int(row[i]) < first_block and int(row[i]) > 0): #reserved
                    print("RESERVED BLOCK", int(row[i]), "IN INODE", int(row[1]), "AT OFFSET 0")
                if(int(row[i]) in free_block_list): #allocated
                    print("ALLOCATED BLOCK", int(row[i]), "ON FREELIST")
                if(int(row[i]) != 0):
                    if(int(row[i]) in used_block_list):
                        dup_block_list += [int(row[i])]
                    else:
                        used_block_list += [int(row[i])]


            if(int(row[24]) != 0):
                if(int(row[24]) in used_block_list):
                    dup_block_list += [int(row[24])]
                else:
                    used_block_list += [int(row[24])]
            if(int(row[25]) != 0):
                if(int(row[25]) in used_block_list):
                    dup_block_list += [int(row[25])]
                else:
                    used_block_list += [int(row[25])]
            if(int(row[26]) != 0):
                if(int(row[26]) in used_block_list):
                    dup_block_list += [int(row[26])]
                else:
                    used_block_list += [int(row[26])]

            if(int(row[24]) < 0 or int(row[24]) > block_count): #indirect invalid
                print("INVALID INDIRECT BLOCK", int(row[24]), "IN INODE", int(row[1]), "AT OFFSET 12")
            if(int(row[25]) < 0 or int(row[25]) > block_count):  # double indirect invalid
                print("INVALID DOUBLE INDIRECT BLOCK", int(row[25]), "IN INODE", int(row[1]), "AT OFFSET 268")
            if(int(row[26]) < 0 or int(row[26]) > block_count):  # triple indirect invalid
                print("INVALID TRIPLE INDIRECT BLOCK", int(row[26]), "IN INODE", int(row[1]), "AT OFFSET 65804")

            if(int(row[24]) < first_block and int(row[24]) > 0): #indirect reserved
                print("RESERVED INDIRECT BLOCK", int(row[24]), "IN INODE", int(row[1]), "AT OFFSET 12")
            if(int(row[25]) < first_block and int(row[25]) > 0): #double indirect reserved
                print("RESERVED DOUBLE INDIRECT BLOCK", int(row[25]), "IN INODE", int(row[1]), "AT OFFSET 268")
            if(int(row[26]) < first_block and int(row[26]) > 0): #triple indirect reserved
                print("RESERVED TRIPLE INDIRECT BLOCK", int(row[26]), "IN INODE", int(row[1]), "AT OFFSET 65804")

            if(int(row[24]) in free_block_list): #allocated indirect
                print("ALLOCATED BLOCK", int(row[24]), "ON FREELIST")
            if(int(row[25]) in free_block_list): #allocated double indirect
                print("ALLOCATED BLOCK", int(row[25]), "ON FREELIST")
            if(int(row[26]) in free_block_list): # allocated triple indirect
                print("ALLOCATED BLOCK", int(row[26]), "ON FREELIST")

        if(row[0] == "INDIRECT"):
            if(int(row[5]) < 0 or int(row[5]) > block_count):
                if(int(row[2]) == 1):
                    print("INVALID INDIRECT BLOCK", int(row[5]), "IN INODE", int(row[1]), "AT OFFSET 12")
                if (int(row[2]) == 2):
                    print("INVALID DOUBLE INDIRECT BLOCK", int(row[5]), "IN INODE", int(row[1]), "AT OFFSET 268")
                if (int(row[2]) == 3):
                    print("INVALID TRIPLE INDIRECT BLOCK", int(row[5]), "IN INODE", int(row[1]), "AT OFFSET 65804")
            if(int(row[5]) < first_block and int(row[5]) > 0):
                if(int(row[2]) == 1):
                    print("RESERVED INDIRECT BLOCK", int(row[5]), "IN INODE", int(row[1]), "AT OFFSET 12")
                if(int(row[2]) == 2):
                    print("RESERVED DOUBLE INDIRECT BLOCK", int(row[5]), "IN INODE", int(row[1]), "AT OFFSET 268")
                if (int(row[2]) == 3):
                    print("RESERVED TRIPLE INDIRECT BLOCK", int(row[5]), "IN INODE", int(row[1]), "AT OFFSET 65804")
            if(int(row[5]) in free_block_list):
                print("ALLOCATED BLOCK", int(row[5]), "ON FREELIST")
            if (int(row[5]) != 0):
                if(int(row[5]) in used_block_list):
                    dup_block_list += [int(row[5])]
                else:
                    used_block_list += [int(row[5])]

    input_csv.seek(0)

    #DUPLICATE
    for row in csv_file:
        if (row[0] == "INODE"):
            if (row[2] != 'f' and row[2] != 'd'):
                continue
            for i in range(12, 24):
                if(int(row[i]) in dup_block_list):
                    print("DUPLICATE BLOCK", int(row[i]), "IN INODE", int(row[1]), "AT OFFSET 0")
            if(int(row[24]) in dup_block_list): #indirect dupes
                print("DUPLICATE INDIRECT BLOCK", int(row[24]), "IN INODE", int(row[1]), "AT OFFSET 12")
            if(int(row[25]) in dup_block_list): #double indirect dupes
                print("DUPLICATE DOUBLE INDIRECT BLOCK", int(row[25]), "IN INODE", int(row[1]), "AT OFFSET 268")
            if(int(row[26]) in dup_block_list): #triple indirect dupes
                print("DUPLICATE TRIPLE INDIRECT BLOCK", int(row[26]), "IN INODE", int(row[1]), "AT OFFSET 65804")

        if(row[0] == "INDIRECT"):
            if(int(row[5]) in dup_block_list):
                if(int(row[2]) == 1):
                    print("DUPLICATE INDIRECT BLOCK", int(row[5]), "IN INODE", int(row[1]), "AT OFFSET 12")
                if(int(row[2]) == 2):
                    print("DUPLICATE DOUBLE INDIRECT BLOCK", int(row[5]), "IN INODE", int(row[1]), "AT OFFSET 268")
                if(int(row[2]) == 3):
                    print("DUPLICATE TRIPLE INDIRECT BLOCK", int(row[5]), "IN INODE", int(row[1]), "AT OFFSET 65804")

    #UNREFERENCED
    for x in range(first_block, block_count):
        if(x not in free_block_list and x not in used_block_list):
            print("UNREFERENCED BLOCK", x)

def directory_inconsistency_check():
    input_csv.seek(0)
    inode_links_dict = {}
    inode_children_dict = {}
    for x in range(1, inode_count+1):
        inode_links_dict[x] = 0
        inode_children_dict[x] = []
    for row in csv_file:
        if(row[0] == "DIRENT"):
            corresponding_inode = int(row[3])
            if(corresponding_inode > 1 and corresponding_inode < inode_count):
                inode_links_dict[corresponding_inode] += 1
            if(int(row[3]) not in inode_allocated_list and int(row[3]) in inode_free_list):
                print("DIRECTORY INODE", int(row[1]), "NAME", row[6], "UNALLOCATED INODE", int(row[3]))
            if(int(row[3]) < 1 or int(row[3]) > inode_count):
                print("DIRECTORY INODE", int(row[1]), "NAME", row[6], "INVALID INODE", int(row[3]))
            if(row[6] == "'.'"):
                if(int(row[1]) != int(row[3])): # for . directory
                    print("DIRECTORY INODE", int(row[1]), "NAME", row[6], "LINK TO INODE", int(row[3]), "SHOULD BE", int(row[1]))
            if(row[6] != "'.'" and row[6] != "'..'"):
                inode_children_dict[int(row[1])] += [int(row[3])]

    input_csv.seek(0)
    for row in csv_file:
        if(row[0] == "INODE"):
            if(int(row[6]) != inode_links_dict[int(row[1])]): #if link count doesn't equal dict link count
                print("INODE", row[1], "HAS", inode_links_dict[int(row[1])], "LINKS BUT LINKCOUNT IS", int(row[6]))
        if(row[0] == "DIRENT"):
            if(row[6] == "'..'"):
                if(int(row[1]) == int(row[3])):
                    continue
                corresponding_inode = int(row[3])
                if(int(row[1]) not in inode_children_dict[corresponding_inode]):
                    print("DIRECTORY INODE", int(row[1]), "NAME", row[6], "LINK TO INODE", int(row[3]), "SHOULD BE", int(row[1]))




if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Program takes in only one argument.", file=sys.stderr)
        exit(1)
    main(sys.argv[1])
