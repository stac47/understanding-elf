#include <stdlib.h>

#include "context.h"
#include "printer.h"


PrinterContext* initContext()
{
    PrinterContext* context = malloc(sizeof(PrinterContext));
    context->count = 0;
    return context;
}

void closeContext(PrinterContext* context)
{
    if (context == NULL) return;
    free(context);
}
