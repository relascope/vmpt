#include <QCoreApplication>

#include <QDebug>

#include <realtimevamphost.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    RealTimeVampHost *myHost = new RealTimeVampHost("pyin", "pyin", 44100, 0, "notes", false);
    myHost->finish();
    delete myHost;

    return a.exec();
}
