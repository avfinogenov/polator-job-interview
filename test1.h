#ifndef TEST1_H
#define TEST1_H

#include <QObject>
#include <qstatemachine.h>
#include <QFinalState>
#include <iostream>
#include <QDebug>
#include <QString>
//#include <QApplication>
#include "myqsm.h"
#include "mystate.h"
#include "test2.h"

class test1 : public QObject
{
    Q_OBJECT

public:
    test1();
    ~test1();
    QStateMachine* m1;
    test2 t;
    void update();
    QString test;



public slots:
     void onSMTH();


};

#endif // TEST1_H
