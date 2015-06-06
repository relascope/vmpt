#include "helpers.h"

QTextStream& qStdOut()
{
    static QTextStream ts( stdout );
    return ts;
}

