#include <cstdio>
#include <sys/mman.h>
#include <cerrno>
#include <cstdlib>
#include <unistd.h>
#include <dlfcn.h>
#include <link.h>
#include "options.hpp"

void pinfo(char buf[]) {
    printf("[xeno]INFO: %s\n", buf);
}

unsigned long get_base_pointer() {
        auto* lm = (struct link_map *) dlopen(nullptr, RTLD_NOW);
        return (unsigned long)lm -> l_addr;
}

void test() {
    printf("It worked!\n");
    exit(0);
}

int xeno() {
    __asm__(".section .init \n call _Z4xenov \n .section .text\n");
    pinfo((char *) "Xenogrip loaded!");
    long pagesize = sysconf(_SC_PAGESIZE);
    void *aligned_address = (void *)(INITIAL_WRITE_POINTER & ~(pagesize - 1));
    int retval = mprotect(aligned_address, pagesize, PROT_READ | PROT_WRITE | PROT_EXEC);
    if(retval == 0) {
        pinfo((char *) "SUCCESSFULLY UNLOCKED MEMORY");

        *(short *)(INITIAL_WRITE_POINTER + 0x0) = (short) 0xb848;
        *(long int *)(INITIAL_WRITE_POINTER + 0x02) = (long int) &test;
        *(short *)(INITIAL_WRITE_POINTER + 0xa) = (short) 0xe0ff;

        printf("[xeno]INFO: Overwrote instructions at %p\n", (void *) INITIAL_WRITE_POINTER);
        //printf("[xeno]ERRORNO: %d\n", errno);
        //printf("[xeno]TESTFUNC: %p\n", test);
        //printf("[xeno]HEX2INT: %d\n", hex2int((char *)"2d"));
    } else {
        pinfo((char *) "ERROR UNLOCKING MEMORY");
        printf("[xeno]ERRORNO: %d\n", errno);
    }
    mprotect(aligned_address, pagesize, PROT_READ | PROT_EXEC);
    pinfo((char *) "SUCCESSFULLY RELOCKED MEMORY");
    return 0;
}
