#include "mainwindow.h"

#include <QApplication>


//just text for testing git

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
