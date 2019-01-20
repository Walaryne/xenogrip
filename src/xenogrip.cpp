#include <stdio.h>
#include <sys/mman.h>
#include <string.h>
#include <errno.h>
#include <error.h>
#include <stdlib.h>

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
        //unsigned char instr[] = "\x48\xb8\x10\x21\xff\xf7\xff\x7f\x00\x00\xff\xe0";
        unsigned char instr[] = "\x48\xb8\xff\xff\xff\xff\xff\xff\x00\x00\xff\xe0";
        //instr[7]

        memmove((void *) 0x00402a00, instr, 12);
        pinfo((char *) "SUCCESSFULLY WROTE NEW INSTRUCTIONS TO 0x00402a00");
        printf("[xeno]ERRORNO: %d\n", errno);
        printf("[xeno]TESTFUNC: %p\n", test);
    } else {
        pinfo((char *) "ERROR UNLOCKING MEMORY");
        printf("[xeno]ERRORNO: %d\n", errno);
    }
    return 0;
}
