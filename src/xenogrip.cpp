#include <stdio.h>
#include <sys/mman.h>
#include <string.h>
#include <errno.h>
#include <error.h>
#include <stdlib.h>
#include "xenogrip.hpp"

void pinfo(char buf[]) {
    printf("[xeno]INFO: %s\n", buf);
}


int test() {
    printf("kek it worked.\n");
    exit(0);
    return 0;
}

int xeno(void) {
    __asm__(".section .init \n call _Z4xenov \n .section .text\n");
    pinfo((char *) "Xenogrip loaded!");
    int retval = mprotect((void *) 0x00400000, 10816, PROT_WRITE | PROT_EXEC);
    if(retval == 0) {
        pinfo((char *) "SUCCESSFULLY UNLOCKED MEMORY");
        unsigned char tip[] = "\x48\xb8";
        unsigned char mid[6];
        unsigned char tail[] = "\x00\x00\xff\xe0";
        char addrstr[14];
        char hexbuf[2];
        void *initialwp = (void *) 0x00402a00;
        void *writeptr;
        int counter = 5;

        sprintf(addrstr, "%p", test);
        for(int i = 2; i != 14; i += 2) {
            for(int j = 0; j != 2; j++) {
                hexbuf[j] = addrstr[i + j];
                if(j == 1){
                    mid[counter] = hex2int(hexbuf);
                    counter--;
                }
            }
        }

        writeptr = mempcpy(initialwp, tip, 2);
        writeptr = mempcpy(writeptr, mid, 6);
        writeptr = mempcpy(writeptr, tail, 4);
        printf("[xeno]INFO: Overwrote instructions at %p\n", initialwp);
        //printf("[xeno]ERRORNO: %d\n", errno);
        //printf("[xeno]TESTFUNC: %p\n", test);
        //printf("[xeno]HEX2INT: %d\n", hex2int((char *)"2d"));
    } else {
        pinfo((char *) "ERROR UNLOCKING MEMORY");
        printf("[xeno]ERRORNO: %d\n", errno);
    }
    return 0;
}
