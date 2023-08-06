#ifndef MYSTATEMACHINE_H
#define MYSTATEMACHINE_H
// на этом классе разбирал стейт машину, в проекте используется в основном для копирования
#include <QObject>
#include <QDebug>
#include <QCoreApplication>
#include <QStateMachine>
#include <QState>
#include <QFinalState>
#include <QDebug>
#include <iostream>
#include <future>

class MyStateMachine : public QObject
{
    Q_OBJECT
public:
    QStateMachine m_statemachine;
    QList<QAbstractState*> m_states;
    void addState(QState *state);
    void stateEntered();
    void stateExited();
    void stateFinished();
    explicit MyStateMachine(QObject *parent = nullptr) : QObject(parent) {
        // Создаем конечный автомат
        for (int i = 0; i < 10; ++i)
        {
            QState* state = new QState();
            state->setObjectName("State " + QString::number(i));
            addState(state);
        }

        QFinalState* final = new QFinalState();
        QState* p = (QState*)m_states.last();
        p->addTransition(this, &MyStateMachine::actionPerformed, final);

        connect(&m_statemachine, &QStateMachine::finished, this, &MyStateMachine::stateFinished);

        m_statemachine.addState(final);

        m_statemachine.setInitialState(m_states.at(0));

        m_statemachine.start();
    }


signals:
    void actionPerformed();

public slots:
    void on_actionPerformed();
};

#endif // MYSTATEMACHINE_H
