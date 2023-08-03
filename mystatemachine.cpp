#include "mystatemachine.h"

void MyStateMachine::on_actionPerformed()
{
    qInfo() << "t";

}



void MyStateMachine::addState(QState *state)
{


    int i = m_states.length();
    if (i > 0)
    {
        QState* p = (QState*)m_states.at(i-1);
        p->addTransition(this, &MyStateMachine::actionPerformed, state);

    }

    connect(state, &QState::entered, this, &MyStateMachine::stateEntered);
    connect(state, &QState::exited, this, &MyStateMachine::stateExited);
    connect(state, &QState::finished, this, &MyStateMachine::stateFinished);

    m_states.append(state);
    m_statemachine.addState(state);

}



void MyStateMachine::stateEntered()
{
    qInfo() << sender() << "Entered";

}

void MyStateMachine::stateExited()
{
    qInfo() << sender() << "Exited";

}

void MyStateMachine::stateFinished()
{
    qInfo() << sender() << "Finished";

}
