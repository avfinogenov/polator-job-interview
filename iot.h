#ifndef IOT_H
#define IOT_H

#include <QObject>
#include <QStateMachine>
#include <QFinalState>
#include <QDebug>
#include "structs.h"
#include "radio1.h"
#include "radio2.h"
#include "sensor.h"
#include "actuator.h"
#include "button.h"

class IOT : public QObject
{
    Q_OBJECT

public:

    explicit IOT(QObject *parent = nullptr): QObject(parent)
    {

    };
    void stateEntered()
    {
        qInfo() << sender() << "Entered";

    }

    void stateExited()
    {
        qInfo() << sender() << "Exited";

    }

    void stateFinished()
    {
        qInfo() << sender() << "Finished";

    }


signals:
    void initComplete();
    void waitForButton();
    void workWithSensor();
    void buttonSendInstantiate();


public slots:
    void gotButtonSignal()
    {
        emit buttonSendInstantiate();
    }
    void justAPlug(){};




private:



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


        m_startingInitialization.addTransition(this, SIGNAL(initComplete()), &m_afterInit);
        m_afterInit.addTransition(this, SIGNAL(waitForButton()), &m_awaitingButton);
        m_afterInit.addTransition(this, SIGNAL(workWithSensor()), &m_workingWithSensor);
        m_awaitingButton.addTransition(this, SIGNAL(buttonSendInstantiate()), &m_talkingToBackend);
        m_talkingToBackend.addTransition(&m_radio1, SIGNAL(backendRoutineFinished()), &m_workingWithSensor);
        m_workingWithSensor.addTransition(&m_radio2, SIGNAL(sendError()), &m_errorState);
        //todo

        m_stateMachine.addState(&m_startingInitialization);
        m_stateMachine.addState(&m_afterInit);
        m_stateMachine.addState(&m_awaitingButton);
        m_stateMachine.addState(&m_talkingToBackend);
        m_stateMachine.addState(&m_workingWithSensor);
        m_stateMachine.addState(&m_errorState);
        m_stateMachine.setInitialState(&m_startingInitialization);

        connect(&m_stateMachine, &QStateMachine::finished, this, &IOTF::lastAction);

        connect(this, SIGNAL(initComplete()), this, SLOT(justAPlug()));
        connect(this, SIGNAL(waitForButton()), this, SLOT(justAPlug()));
        connect(this, SIGNAL(workWithSensor()), this, SLOT(justAPlug()));
        connect(&m_radio1, SIGNAL(backendRoutineFinished()), this, SLOT(justAPlug()));
        connect(&m_radio2, SIGNAL(sendError()), this, SLOT(justAPlug()));




         m_stateMachine.start();
         emit initComplete();
         afterInit();

    };
    ~IOTF(){};
    void lastAction()
    {
        this->~IOTF();
    }
    void sync()
    {

        while(!m_radio1.connect())
        {
           continue;
        }
        if (m_radio1.getConnectionStatus())
        {
            m_radio2.updateNeighbours(m_radio1.exchange(m_geo));
            m_radio1.disconnect();
        }

    }
    void debugInfo()
    {
        connect(m_startingInitialization, &QState::entered, this, &IOTF::stateEntered);
        connect(m_startingInitialization, &QState::exited, this, &IOTF::stateExited);
        connect(m_startingInitialization, &QState::finished, this, &IOTF::stateFinished);
        connect(m_afterInit, &QState::entered, this, &IOTF::stateEntered);
        connect(m_afterInit, &QState::exited, this, &IOTF::stateExited);
        connect(m_afterInit, &QState::finished, this, &IOTF::stateFinished);
        connect(m_awaitingButton, &QState::entered, this, &IOTF::stateEntered);
        connect(m_awaitingButton, &QState::exited, this, &IOTF::stateExited);
        connect(m_awaitingButton, &QState::finished, this, &IOTF::stateFinished);
        connect(m_talkingToBackend, &QState::entered, this, &IOTF::stateEntered);
        connect(m_talkingToBackend, &QState::exited, this, &IOTF::stateExited);
        connect(m_talkingToBackend, &QState::finished, this, &IOTF::stateFinished);
        connect(m_workingWithSensor, &QState::entered, this, &IOTF::stateEntered);
        connect(m_workingWithSensor, &QState::exited, this, &IOTF::stateExited);
        connect(m_workingWithSensor, &QState::finished, this, &IOTF::stateFinished);
        connect(m_errorState, &QState::entered, this, &IOTF::stateEntered);
        connect(m_errorState, &QState::exited, this, &IOTF::stateExited);
        connect(m_errorState, &QState::finished, this, &IOTF::stateFinished);
    }






    //? выглядит как не очень эффективно и корректно
    void propagate()
    {
        m_radio2.propagate(m_sensor.read());

    }
    void process()
    {
        TokenT token;
        m_radio2.process(&token);
        m_actuator.write(token);
    }

    //очень странно что по схеме они паблик, но да ладно
    Radio1F<BackendT, R2ConnectionParamsT, GEOT> m_radio1;
    Radio2F<TokenT, R2ConnectionParamsT> m_radio2;

//signals:






private:
    GEOT m_geo = GEOT();

    QStateMachine m_stateMachine;

    QState m_startingInitialization;
    QState m_afterInit;
    QState m_awaitingButton;
    QState m_talkingToBackend;
    QState m_workingWithSensor;
    QFinalState m_errorState;
    SensorF<TokenT> m_sensor;
    ActuatorF<TokenT> m_actuator;
    void afterInit()
    {
        if (m_radio2.isHaveNeighbours())
        {
            emit workWithSensor();
        }
        else
        {
            emit waitForButton();
        }
    }

};





#endif // IOT_H
