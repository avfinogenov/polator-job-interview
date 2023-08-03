#include "mainwindow.h"

#include <QApplication>
#include <QStateMachine>



int main(int argc, char *argv[])
{
    QStateMachine asdf;
    QState s;

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
