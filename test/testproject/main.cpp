#include <QtTest/QtTest>

#include <QDebug>

#include "sndfileallinclusive.h"

int main(int argc, char **argv) {

    QCoreApplication a(argc, argv);

    testsndfileread();

    qDebug() << "finished!";
    return a.exec();
}
