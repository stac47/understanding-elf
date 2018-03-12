#include <stdio.h>

#include "printer.h"


const char* kExternString = "Extern String";

static const char* kStaticString = "Intern String";

void printExternString()
{
    puts(kExternString);
}

void printStaticString()
{
    puts(kStaticString);
}

void printAllStrings()
{
    printExternString();
    printStaticString();
}
