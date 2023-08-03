#include <QCoreApplication>
#include <QStateMachine>
#include <QState>
#include <QFinalState>
#include <QDebug>
#include <iostream>
#include <future>

#include "mystatemachine.h"


//class MyStateMachine : public QObject {
//    Q_OBJECT
//public:

//    QStateMachine m_statemachine;
//    QList<QAbstractState*> m_states;
//    void addState(QState *state);



//    void stateEntered();


//    void stateExited();

//    void stateFinished();




//    explicit MyStateMachine(QObject *parent = nullptr) : QObject(parent) {
//        // Создаем конечный автомат
//        for (int i = 0; i < 10; ++i)
//        {
//            QState* state = new QState();
//            state->setObjectName("State " + QString::number(i));
//            addState(state);
//        }

//        QFinalState* final = new QFinalState();
//        QState* p = (QState*)m_states.last();
//        p->addTransition(this, &MyStateMachine::nextStateSignal, final);

//        connect(&m_statemachine, &QStateMachine::finished, this, &MyStateMachine::stateFinished);

//        m_statemachine.addState(final);

//        m_statemachine.setInitialState(m_states.at(0));

//        m_statemachine.start();
//    }

//signals:
//    void nextStateSignal();
//    void finalStateSignal();

//public slots:
//    void smth(){};
//};


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

    QObject::connect(&stateMachine, &MyStateMachine::actionPerformed, &s2, &MyStateMachine::on_actionPerformed);

    std::future<void> thread1 = std::async(std::launch::async, &threadv, &stateMachine);

    return app.exec();
}



