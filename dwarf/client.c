#include <stdio.h>

#include "printer.h"

int main(int argc, const char *argv[])
{
    PrinterContext* context = initContext();
    sayHello(context, "Stac");
    sayHello(context, "Stac");
    sayGoodbye(context);
    closeContext(context);

    return 0;
}
