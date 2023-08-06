#ifndef IOT_H
#define IOT_H

#include <QObject>
#include <QStateMachine>
#include <QFinalState>
#include <QDebug>
#include <QString>
#include "structs.h"
#include "radio1.h"
#include "radio2.h"
#include "sensor.h"
#include "actuator.h"
#include "button.h"


class SuperPlug : public QObject
{
    Q_OBJECT

public:

    explicit SuperPlug(QObject *parent = nullptr): QObject(parent)
    {

    };
public slots:
    void justAPlug(QString s)
    {
//        qInfo() << "plug activated\n"    ;
//        qInfo() << s;

    };
};


class IOT : public QObject
{
    Q_OBJECT

public:

    explicit IOT(QString inputName, QObject *parent = nullptr): QObject(parent)
    {
        m_selfName = inputName;
    };

    QString m_selfName;

signals:
    void initComplete(QString s);
    void waitForButton(QString s);
    void workWithSensor(QString s);
    void buttonSendInstantiate(QString s);
    void radio1Error(QString s);

public slots:
    void gotButtonSignal()
    {

        qInfo() << "got button signal\n";
         qInfo() << m_selfName;
        emit buttonSendInstantiate("button send instantiate");
    }


    void on_tokenWritten()
    {
        qDebug() << m_selfName;
        qDebug() << "token written";

    }


private:



};



template <typename BackendT, typename R2ConnectionParamsT,
          typename GEOT, typename TokenT>
class IOTF : public IOT
{

public:
    explicit IOTF(Radio2ChannelF<R2ConnectionParamsT, TokenT>* channel,
                 R2ConnectionParamsT myR2Info, BackendT backendConnectionParams,
                 BackendF<BackendT, R2ConnectionParamsT, GEOT>* backend, QString inputName):
                 IOT(inputName, nullptr), m_radio1(backend, backendConnectionParams),
                 m_superPlug(), m_radio2(channel, myR2Info), m_sensor(), m_actuator()
    {


        m_startingInitialization.addTransition(this, SIGNAL(initComplete(QString)), &m_afterInit);
        m_startingInitialization.setObjectName("m_startingInitialization" );
        m_afterInit.addTransition(this, SIGNAL(waitForButton(QString )), &m_awaitingButton);
        m_afterInit.addTransition(this, SIGNAL(workWithSensor(QString )), &m_workingWithSensor);
        m_awaitingButton.addTransition(this, SIGNAL(buttonSendInstantiate(QString)), &m_talkingToBackend);
        m_talkingToBackend.addTransition(&m_radio1, SIGNAL(backendRoutineFinished(QString)), &m_workingWithSensor);
        m_talkingToBackend.addTransition(this, SIGNAL(radio1Error(QString )), &m_errorState);
        m_workingWithSensor.addTransition(&m_radio2, SIGNAL(sendError(QString)), &m_errorState);
        m_afterInit.setObjectName("m_afterInit" );
        m_awaitingButton.setObjectName("m_awaitingButton" );
        m_talkingToBackend.setObjectName("m_talkingToBackend" );
        m_workingWithSensor.setObjectName("m_workingWithSensor" );

        //todo

        m_stateMachine.addState(&m_startingInitialization);
        m_stateMachine.addState(&m_afterInit);
        m_stateMachine.addState(&m_awaitingButton);
        m_stateMachine.addState(&m_talkingToBackend);
        m_stateMachine.addState(&m_workingWithSensor);
        m_stateMachine.addState(&m_errorState);
        m_stateMachine.setInitialState(&m_startingInitialization);
        connect(&m_stateMachine, &QStateMachine::finished, this, &IOTF::stateFinished);
        debugInfo();
        m_stateMachine.start();

        connect(&m_stateMachine, &QStateMachine::finished, this, &IOTF::lastAction);
        connect(this, &IOT::buttonSendInstantiate, &m_superPlug, &SuperPlug::justAPlug);
        connect(&m_sensor, &Sensor::gotNewToken, this, &IOTF::propagate);
//        connect(&m_sensor, SIGNAL(gotNewToken()), this, SLOT(propagate()));

        connect(this, SIGNAL(initComplete(QString)), &m_superPlug, SLOT(justAPlug(QString)));
        connect(this, SIGNAL(radio1Error(QString)), &m_superPlug, SLOT(justAPlug(QString)));
        connect(this, SIGNAL(waitForButton(QString)), &m_superPlug, SLOT(justAPlug(QString)));
        connect(this, SIGNAL(workWithSensor(QString)), &m_superPlug, SLOT(justAPlug(QString)));
        connect(&m_radio1, SIGNAL(backendRoutineFinished(QString)), &m_superPlug, SLOT(justAPlug(QString)));
        connect(&m_radio2, SIGNAL(sendError(QString)), &m_superPlug, SLOT(justAPlug(QString)));
        connect(&m_radio2, &Radio2::confirmReading, this, &IOTF::process);
//        connect(&m_radio2, SIGNAL(confirmReading()), this, SLOT(process()));

        connect(&m_actuator, SIGNAL(tokenWritten()), this, SLOT(on_tokenWritten()));







    };
    ~IOTF(){};
    void afterInit()
    {

    }

    void stateEntered()
    {
        qInfo() << sender() << "Entered";
        if (sender()->objectName() == "m_startingInitialization")
        {
            emit initComplete(QString("init complete"));
//            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            afterInit();
        }
        if (sender()->objectName() == "m_afterInit")
        {
            if (m_radio2.isHaveNeighbours())
            {
                emit workWithSensor(QString("work with sensor"));
            }
            else
            {
                emit waitForButton(QString("wait for button"));
            }
        }
        if (sender()->objectName() == "m_talkingToBackend")
         {
             sync();
         }


    }

    void stateExited()
    {
//        qInfo() << sender() << "Exited";

    }

    void stateFinished()
    {
//        qInfo() << sender() << "Finished";

    }
    void lastAction()
    {
        this->~IOTF();
    }
    void sync()
    {
        m_radio1.connect();

        int counter = 0;
        while(!m_radio1.getConnectionStatus())
        {
            if (counter > 100)
            {
                qInfo() << "r1 error\n";
                emit radio1Error(QString("radio 1 error\n"));
                return;
            }

            m_radio1.connect();
            counter++;
        }

        if (m_radio1.getConnectionStatus())
        {
            m_radio2.updateNeighbours(m_radio1.exchange(m_geo));
            m_radio1.disconnect();
//            m_radio1.backendRoutineFinished(QString("backend routine finished"));
        }
        else
        {

        }

    }
    void debugInfo()
    {
        connect(&m_startingInitialization, &QState::entered, this, &IOTF::stateEntered);
        connect(&m_startingInitialization, &QState::exited, this, &IOTF::stateExited);
        connect(&m_startingInitialization, &QState::finished, this, &IOTF::stateFinished);
        connect(&m_afterInit, &QState::entered, this, &IOTF::stateEntered);
        connect(&m_afterInit, &QState::exited, this, &IOTF::stateExited);
        connect(&m_afterInit, &QState::finished, this, &IOTF::stateFinished);
        connect(&m_awaitingButton, &QState::entered, this, &IOTF::stateEntered);
        connect(&m_awaitingButton, &QState::exited, this, &IOTF::stateExited);
        connect(&m_awaitingButton, &QState::finished, this, &IOTF::stateFinished);
        connect(&m_talkingToBackend, &QState::entered, this, &IOTF::stateEntered);
        connect(&m_talkingToBackend, &QState::exited, this, &IOTF::stateExited);
        connect(&m_talkingToBackend, &QState::finished, this, &IOTF::stateFinished);
        connect(&m_workingWithSensor, &QState::entered, this, &IOTF::stateEntered);
        connect(&m_workingWithSensor, &QState::exited, this, &IOTF::stateExited);
        connect(&m_workingWithSensor, &QState::finished, this, &IOTF::stateFinished);
//        connect(&m_errorState, &QState::entered, this, &IOTF::stateEntered);
//        connect(&m_errorState, &QState::exited, this, &IOTF::stateExited);
//        connect(&m_errorState, &QState::finished, this, &IOTF::stateFinished);
    }






    //? выглядит как не очень эффективно и корректно
    void propagate()
    {
//        qInfo() << "attempt to read sensor\n";
        m_radio2.propagate(m_sensor.read());

    }
    void process()
    {
//        qInfo() << "process activated";
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

    SuperPlug m_superPlug;




};





#endif // IOT_H
