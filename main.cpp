#include <QCoreApplication>
#include <QStateMachine>
#include <QState>
#include <QFinalState>
#include <QDebug>
#include <iostream>
#include <future>

#include "mystatemachine.h"
#include "iot.h"



void threadv(MyStateMachine* m)
{
    char tmp;
    while (true)
    {
        std::cin >> tmp;
        emit m->actionPerformed();
    }

}



int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);
    MyStateMachine stateMachine, s2;
    Radio2ChannelF<int, int> r2channel;
    BackendF<int, int, int> backend;
    IOTF<int, int, int, int> iot(&r2channel, 1, 1, &backend);
    QObject::connect(&stateMachine, &MyStateMachine::actionPerformed, &s2, &MyStateMachine::on_actionPerformed);

    std::future<void> thread1 = std::async(std::launch::async, &threadv, &stateMachine);

    return app.exec();
}



