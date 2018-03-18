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

static Elf64_Dyn* findDynByTag(Elf64_Sxword tag)
{
    Elf64_Dyn* dyn = _DYNAMIC;
    while (dyn->d_tag != DT_NULL)
    {
        if (dyn->d_tag == tag)
        {
            return dyn;
        }
        dyn++;
    }
    return NULL;
}


static int replaceDoNothing()
{
    Elf64_Dyn* strtab = findDynByTag(DT_STRTAB);
    if (strtab != NULL)
    {
        printf("String table address: %p\n", (void*)(strtab->d_un.d_ptr));
    }

    Elf64_Dyn* symtab = findDynByTag(DT_SYMTAB);
    if (symtab != NULL)
    {
        printf("Symbols table address: %p\n", (void*)symtab->d_un.d_ptr);
    }

    Elf64_Dyn* pltgot = findDynByTag(DT_PLTGOT);
    if (pltgot != NULL)
    {
        printf("PLT/GOT: %p\n", (void*)pltgot->d_un.d_ptr);
    }

    Elf64_Dyn* jmprel = findDynByTag(DT_JMPREL);
    if (jmprel != NULL)
    {
        printf("JMP relocations: %p\n", (void*)jmprel->d_un.d_ptr);
    }

    Elf64_Dyn* jmprelsz = findDynByTag(DT_PLTRELSZ);
    if (jmprelsz != NULL)
    {
        printf("Number of relocations: %lu\n", jmprelsz->d_un.d_val / sizeof(Elf64_Rela));
    }

    unsigned long numberOfRelocations = jmprelsz->d_un.d_val / sizeof(Elf64_Rela);
    Elf64_Rela* relBase = (Elf64_Rela*)jmprel->d_un.d_ptr;

    for (int i = 0; i < numberOfRelocations; ++i)
    {
        Elf64_Rela rel = relBase[i];
        printf("%lx -> %lu\n", rel.r_offset, ELF64_R_SYM(rel.r_info));
    }

    /* unsigned long idx = ELF64_R_SYM(rel->r_info); */
    /* printf("%lu\n", idx); */

    /* Elf64_Sym* sym = (Elf64_Sym*) symtab->d_un.d_ptr; */
    /* puts((const char*)strtab + sym[idx].st_name); */


    /* while (rel - relBase < relsize->d_un.d_ptr) */
    /* { */
    /*     printf("%p\n", (void*) rel->r_offset); */
    /*     rel++; */
    /* } */


    /* void* handle = NULL; */
    /* void (*function)(void); */
    /* struct link_map* lmap = NULL; */
    /* if ((handle = dlopen("libnothing.so", RTLD_LAZY)) == NULL) */
    /* { */
    /*     puts("ERROR"); */
    /*     return 1; */
    /* } */
    /* if ((function = (void (*)(void)) dlsym(handle, "doNothing")) == NULL) */
    /* { */
    /*     puts("ERROR"); */
    /*     return 1; */
    /* } */
    /* printf("Address of doNothing: %p\n", (void*) function); */
    /* if (dlinfo(handle, RTLD_DI_LINKMAP, &lmap) != 0) */
    /* { */
    /*     puts("ERROR"); */
    /*     return 1; */
    /* } */
    /* Elf64_Addr addr = lmap->l_addr; */
    /* printf("Address: %p\n", (void*)addr); */

    /* Elf64_Dyn* dyn = lmap->l_ld; */
    /* printf("Dynamic section: %p\n", (void*)dyn); */
    /* printf("Shared lib path: %s\n", lmap->l_name); */
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
