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

    bool isStarted = false;
    while (true)
    {
        std::cin >> tmp;

        if (!isStarted)
        {
            b->doYourThing();
            isStarted = true;
        }

//        counter++;

    }

}



int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);
//    MyStateMachine stateMachine, s2;
    Radio2ChannelF<int, int> r2channel;
    int x = 1;
    std::vector<Button*> buttons;
    Button b;
    std::vector<IOTF<int, int, int, int>*> iots;
    BackendF<int, int, int> backend(x);
    for (int i = 0; i < 10; ++i)
    {
//        Button* b = new Button();
//        buttons.push_back(b);
        IOTF<int, int, int, int>* iot = new IOTF<int, int, int, int>(&r2channel, i + 1,  1, &backend, "iot " + QString(i));
        backend.addParamsToSend(i + 1);
        iots.push_back(iot);
    }

    for (int i = 0; i < 10; ++i)
    {
        QObject::connect(&b, SIGNAL(instantiate()), iots[i], SLOT(gotButtonSignal()));
    }




//    IOTF<int, int, int, int> iot1(&r2channel, 1, 1, &backend, "iot 1");
//    IOTF<int, int, int, int> iot2(&r2channel, 1, 2, &backend, "iot 2");
//    IOTF<int, int, int, int> iot3(&r2channel, 1, 3, &backend, "iot 3");
//    IOTF<int, int, int, int> iot4(&r2channel, 1, 4, &backend, "iot 4");
//    IOTF<int, int, int, int> iot5(&r2channel, 1, 5, &backend, "iot 5");
//    IOTF<int, int, int, int> iot6(&r2channel, 1, 6, &backend, "iot 6");
//    IOTF<int, int, int, int> iot7(&r2channel, 1, 7, &backend, "iot 7");
//    IOTF<int, int, int, int> iot8(&r2channel, 1, 8, &backend, "iot 8");
//    IOTF<int, int, int, int> iot9(&r2channel, 1, 9, &backend, "iot 9");
//    IOTF<int, int, int, int> iot10(&r2channel, 1, 10, &backend, "iot 10");
//    QObject::connect(&stateMachine, &MyStateMachine::actionPerformed, &s2, &MyStateMachine::on_actionPerformed);

//    QObject::connect(&b, SIGNAL(instantiate()), &iot1, SLOT(gotButtonSignal()));
//    QObject::connect(&b, SIGNAL(instantiate()), &iot2, SLOT(gotButtonSignal()));
//    QObject::connect(&b, SIGNAL(instantiate()), &iot3, SLOT(gotButtonSignal()));
//    QObject::connect(&b, SIGNAL(instantiate()), &iot4, SLOT(gotButtonSignal()));
//    QObject::connect(&b, SIGNAL(instantiate()), &iot5, SLOT(gotButtonSignal()));
//    QObject::connect(&b, SIGNAL(instantiate()), &iot6, SLOT(gotButtonSignal()));
//    QObject::connect(&b, SIGNAL(instantiate()), &iot7, SLOT(gotButtonSignal()));
//    QObject::connect(&b, SIGNAL(instantiate()), &iot8, SLOT(gotButtonSignal()));
//    QObject::connect(&b, SIGNAL(instantiate()), &iot9, SLOT(gotButtonSignal()));
//    QObject::connect(&b, SIGNAL(instantiate()), &iot10, SLOT(gotButtonSignal()));

    std::future<void> thread1 = std::async(std::launch::async, &threadv, &b);

    return app.exec();
}



