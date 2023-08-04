#ifndef IOT_H
#define IOT_H

#include <QObject>
#include <QStateMachine>
#include <QFinalState>
#include "structs.h"
#include "radio1.h"
#include "radio2.h"
#include "sensor.h"
#include "actuator.h"

template <typename BackendT, typename R2ConnectionParamsT,
          typename GEOT, typename TokenT>
class IOT : public QObject
{
    Q_OBJECT
public:
    explicit IOT(R2ConnectionParamsT myR2Info,
                 Backend<BackendT, R2ConnectionParamsT>* backend,
                 QObject *parent = nullptr): QObject(parent), m_radio1(backend),
                 m_radio2(myR2Info), m_sensor(), m_actuator()
    {

    };

    void sync();


    //? выглядит как не очень эффективно и корректно
    void propagate();
    void process();


    Radio1<BackendT, R2ConnectionParamsT, GEOT> m_radio1;
    Radio2<TokenT, R2ConnectionParamsT> m_radio2;

signals:






private:
    GEOT m_geo = GEOT();

    QStateMachine m_stateMachine;

    QState startingInitialization;
    QState awaitingButton;
    QState talkingToBackend;
    QState WorkingWithSensor;
    QFinalState errorState;
    Sensor<TokenT> m_sensor;
    Actuator<TokenT> m_actuator;


};


//IOT::IOT(QObject *parent) : QObject(parent)
//{

//}


#endif // IOT_H
