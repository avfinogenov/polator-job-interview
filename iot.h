#ifndef IOT_H
#define IOT_H

#include <QObject>
#include <QStateMachine>
#include <QFinalState>
#include "structs.h"

template <typename GEOT>
class IOT : public QObject
{
    Q_OBJECT
public:
    explicit IOT(QObject *parent = nullptr);

    void sync();


    //? выглядит как не очень эффективно и корректно
    void propagate();
    void process();


signals:






private:
    GEOT m_geo = GEOT();

    QStateMachine m_stateMachine;

    QState startingInitialization;
    QState awaitingButton;
    QState talkingToBackend;
    QState WorkingWithSensor;
    QFinalState errorState;


};

#endif // IOT_H
