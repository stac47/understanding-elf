#define _GNU_SOURCE
#include <dlfcn.h>
#include <link.h>
#include <stdio.h>
#include <stdlib.h>
#include <elf.h>

#include "nothing.h"

// The goal of this program is to replace the definition of the doNothing
// function in the PLT to call a function locally defined

static void doSomething()
{
    puts("I did something");
}

static int replaceDoNothing()
{
    void* handle = NULL;
    void (*function)(void);
    struct link_map* lmap = NULL;
    if ((handle = dlopen("libnothing.so", RTLD_LAZY)) == NULL)
    {
        puts("ERROR");
        return 1;
    }
    if ((function = (void (*)(void)) dlsym(handle, "doNothing")) == NULL)
    {
        puts("ERROR");
        return 1;
    }
    printf("Address of doNothing: %p\n", (void*) function);
    if (dlinfo(handle, RTLD_DI_LINKMAP, &lmap) != 0)
    {
        puts("ERROR");
        return 1;
    }
    Elf64_Addr addr = lmap->l_addr;
    printf("Address: %s\n", addr);
    printf("Shared lib path: %s\n", lmap->l_name);
    //puts(function);
    //free(handle);
    return 0;
}

int main(int argc, const char *argv[])
{
    if (replaceDoNothing() != 0)
    {
        return 1;
    }
    doAlmostNothing();
    return 0;
}
