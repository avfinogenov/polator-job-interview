#ifndef SENSOR_H
#define SENSOR_H

#include <QObject>
#include <future>
#include <random>
#include <QDebug>

class Sensor : public QObject
{
    Q_OBJECT
public:

    explicit Sensor(QObject *parent = nullptr) : QObject(parent)
    {

    }


signals:
    void gotNewToken();
};

template <typename TokenT>
class SensorF : public Sensor
{

public:
    explicit SensorF()
    {
        srand(time(NULL));
        m_isWorking = true;
        m_thread = std::async(std::launch::async, &SensorF::threadGenerateRandomToken, this);

    }

    ~SensorF()
    {
        m_isWorking = false;
        m_thread.get();
    }
    TokenT read()
    {


        return m_token;

    }

    //signals:




private:
    TokenT m_token = TokenT();
    std::future<void> m_thread;
    bool m_isWorking = false;
    bool m_isTokenChanged = false;
    void threadGenerateRandomToken()
    {
        while(m_isWorking)
        {
            m_token = TokenT(rand() % 100);

//            qInfo() << "sensor got token\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(10000));
            emit gotNewToken();
        }

    }
};

#endif // SENSOR_H
