#include <QtTest/QtTest>

#include <QDebug>

#include "sndfileallinclusive.h"

int main(int argc, char **argv) {

    QCoreApplication a(argc, argv);

    testsndfileread();
    testsndfileread();
    testgenericsndfileread();
    testgenericsndfileread();

    qDebug() << "finished!";
    return a.exec();
}
