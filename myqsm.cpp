#include "myqsm.h"

myqsm::myqsm(QObject* parent): QStateMachine(parent)
{

}
bool myqsm::event(QEvent* e)
{

    e->accept();
    std::cout << "got event\n";
    return true;

}



myqsm::~myqsm()
{

}
