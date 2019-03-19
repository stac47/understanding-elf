#include <stdio.h>

#include "context.h"
#include "printer.h"

void sayHello(PrinterContext* context, const char* name)
{
    context->name = name;
    printf("Hello, %s!\n", context->name);
    context->count++;
}
