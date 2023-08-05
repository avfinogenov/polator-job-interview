#include <QCoreApplication>
#include <QStateMachine>
#include <QState>
#include <QFinalState>
#include <QDebug>
#include <iostream>
#include <future>

#include "mystatemachine.h"
#include "iot.h"



void threadv(Button* b)
{
    char tmp;

    while (true)
    {
        std::cin >> tmp;

        b->doYourThing();

    }

}



int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);
//    MyStateMachine stateMachine, s2;
    Radio2ChannelF<int, int> r2channel;
    int x = 1;
    Button b;

    BackendF<int, int, int> backend(x);
    backend.addParamsToSend(x);
    IOTF<int, int, int, int> iot(&r2channel, 0, x, &backend);
//    QObject::connect(&stateMachine, &MyStateMachine::actionPerformed, &s2, &MyStateMachine::on_actionPerformed);

    QObject::connect(&b, SIGNAL(instantiate()), &iot, SLOT(gotButtonSignal()));
    std::future<void> thread1 = std::async(std::launch::async, &threadv, &b);

    return app.exec();
}



