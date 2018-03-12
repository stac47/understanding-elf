#include "nothing.h"

static void doNothingStatic()
{}

void doNothing()
{}

void doAlmostNothing()
{
    doNothingStatic();
    doNothing();
}
