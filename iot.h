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

class IOT : public QObject
{
    Q_OBJECT

public:

    explicit IOT(QObject *parent = nullptr): QObject(parent)
    {

    };

};



template <typename BackendT, typename R2ConnectionParamsT,
          typename GEOT, typename TokenT>
class IOTF : public IOT
{

public:
    explicit IOTF(Radio2ChannelF<R2ConnectionParamsT, TokenT>* channel,
                 R2ConnectionParamsT myR2Info, BackendT backendConnectionParams,
                 BackendF<BackendT, R2ConnectionParamsT, GEOT>* backend):
                 m_radio1(backend, backendConnectionParams),
                 m_radio2(channel, myR2Info), m_sensor(), m_actuator()
    {

    };

    void sync();


    //? выглядит как не очень эффективно и корректно
    void propagate();
    void process();


    Radio1F<BackendT, R2ConnectionParamsT, GEOT> m_radio1;
    Radio2F<TokenT, R2ConnectionParamsT> m_radio2;

//signals:






private:
    GEOT m_geo = GEOT();

    QStateMachine m_stateMachine;

    QState startingInitialization;
    QState awaitingButton;
    QState talkingToBackend;
    QState WorkingWithSensor;
    QFinalState errorState;
    SensorF<TokenT> m_sensor;
    ActuatorF<TokenT> m_actuator;


};





#endif // IOT_H
