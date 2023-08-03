#include "test1.h"

test1::test1():QObject()
{
    connect(&t, SIGNAL(signalTest()), this, SLOT(onSMTH()));
    m1 = new myqsm();
    MyState* s1 = new MyState("s1");
    MyState* s2 = new MyState("s2");
//    s1->assignProperty(&t, "test", "do something");
    s1->addTransition((QObject*)&t, SIGNAL(signalTest()), s2);
//    s1->addTransition(&t, &test2::signalTest(), s1);
//    s1->addTransition(s1->addTransition(&t, SIGNAL(signalTest()), s2));
//    s1->setProperty("test", "test");
    m1->addState(s1);
    m1->addState(s2);
    m1->setInitialState(s1);
    m1->start();
//    QApplication::processEvents();
    std::cout << (m1->configuration().contains(s1)? "yes": "no");

    std::cout << "machine started\n" << std::endl;

}


//void QStateMachine::event(QEvent *event) override
//{
//    event->accept();
//    qDebug() << "event!" ;
//}
void test1::update()
{
    t.update();
}

void test1::onSMTH()
{
    std::cout << m1->configuration().size();
    _sleep(100);
    std::cout << "got smth\n";
}

test1::~test1()
{

}
