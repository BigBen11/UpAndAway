#include "mainwindow.h"

#include <QApplication>

#include "test.h"



//just text for testing git

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Test test;

    QTest::qExec(&test);

    return a.exec();
}

