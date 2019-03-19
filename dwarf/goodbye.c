#include <stdio.h>

#include "context.h"
#include "printer.h"

void sayGoodbye(PrinterContext* context)
{
    if (context == NULL)
    {
        printf("No context available");
    }
    else
    {
        if (context->name != NULL)
        {
            printf("Goodbye %s. You told me Hello %d times.\n", context->name,
                                                                context->count);
        }
        else
        {
            puts("I do not know you");
        }
    }
}
