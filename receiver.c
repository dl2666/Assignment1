//
//  main.c
//  SHM
//
//  Created by Diana Levy on 10/18/19.
//  Copyright © 2019 Diana Levy. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <ctype.h>

#define SHARED_NAME "/shm-object-name"
#define SIZE 256

int main(int argc, char **argv) {
    int fd;
    char* shm_addr;
    char* user_input = (malloc((char)sizeof(SIZE)));
    
    
    fd = shm_open(SHARED_NAME,O_CREAT|O_RDWR,0660);
    if(fd==-1)
        perror("shm open error");
    //pointer to shared memory in virtual address space
    shm_addr=mmap(NULL, SIZE,PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (shm_addr==MAP_FAILED)
        perror("mmap error");
    //pointer to check for secret code in alpha-numeric string
    char* test;
    while(1){
        printf("Please enter an alpha-numeric string: ");
        //stores user_input in variable and tests for the code work "C00L"
        fgets(user_input, SIZE, stdin);
        test=strstr(user_input, "C00L");
        //if test returns a ptr, then "C00L" was found and will now be copies into shared memory
        if (test!=NULL)
            strcpy(shm_addr, user_input);
        
        //the newline symbol is used as an indicator that the processor has finished writing code into secret file
        while(*shm_addr!='\n')
            sleep(1);
    }

  
    return 0;
}
