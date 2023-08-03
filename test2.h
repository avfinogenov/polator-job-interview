#ifndef TEST2_H
#define TEST2_H

#include <QObject>
#include <QString>
#include <iostream>

class test2 : public QObject
{
    Q_OBJECT

public:
    test2();
    ~test2();
    void update();
    QString test;
    void print(){std::cout << "smth";}



signals:
    void signalTest();
};

#endif // TEST2_H
