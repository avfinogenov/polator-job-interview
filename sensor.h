#ifndef SENSOR_H
#define SENSOR_H

#include <QObject>

class Sensor : public QObject
{
    Q_OBJECT
public:

    explicit Sensor(QObject *parent = nullptr) : QObject(parent)
    {

    }

};

template <typename TokenT>
class SensorF : public Sensor
{

public:
    explicit SensorF()
    {

    }


    TokenT read();

//signals:




private:
    TokenT token = TokenT();
};

#endif // SENSOR_H
