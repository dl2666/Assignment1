//
//  processor.c
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
    FILE* file_ptr;
    
    fd=shm_open(SHARED_NAME,O_CREAT|O_RDWR,0660);
    if(fd==-1)
        perror("shm_open error");
    
    shm_addr = mmap(NULL, SIZE, PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    if(shm_addr==MAP_FAILED)
        perror("mmap error");
    //create file for writing
    file_ptr = fopen("secrets.out","w");
    
    //infinite loop
    while(1){
      
     //new input found in shared memory if pointer doesn't point to a newline character
        if(*shm_addr!='\n'){
            //set count to 0 within loop, so initializes every time there's new input
            int count = 0;
            for(char* i=shm_addr;*i!='\n';i++){
                if(*i=='0'||*i=='1'||*i=='2'||*i=='3'||*i=='4'||*i=='5'||*i=='6'||*i=='7'||*i=='8'||*i=='9')
                    count++;
            }
            fprintf(file_ptr, shm_addr,":",count);
            fclose(file_ptr);
        }
        //notify receiver that its done writing string
        *shm_addr='\n';
            
    }
    
    return 0;
}
