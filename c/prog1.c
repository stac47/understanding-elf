#include <stdio.h>
#include "printer.h"

static void StaticFunction()
{
    puts("prog1::StaticFunction");
}

extern void ExternFunction()
{
    puts("prog1::ExternFunction");
}

int main(int argc, const char *argv[])
{
    puts("prog1::main");
    StaticFunction();
    ExternFunction();
    puts("Direct call to printer");
    printAllStrings();
    return 0;
}
