#include <QtTest/QtTest>

#include "transcribetest.h"

int main()
{
    TranscribeTest tt;
    QTest::qExec(&tt);

    return 0;

}
