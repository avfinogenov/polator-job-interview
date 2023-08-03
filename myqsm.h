#ifndef MYQSM_H
#define MYQSM_H
#include <QStateMachine>
#include <iostream>
class myqsm : public QStateMachine
{
public:
    myqsm(QObject* parent = nullptr);
    ~myqsm();


    bool event(QEvent* e) override;

};

#endif // MYQSM_H
