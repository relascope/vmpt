#include "testrunner.h"
int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    return RUN_ALL_TESTS(argc, argv);
}
