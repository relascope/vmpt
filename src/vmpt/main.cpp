#include <QCoreApplication>

#include <QDebug>

#include <vamphost.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    VampHost *myHost = new VampHost("pyin", "pyin", 1000, 0, 0, false);
    myHost->finish();
    delete myHost;

    return a.exec();
}
