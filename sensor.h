#ifndef SENSOR_H
#define SENSOR_H

#include <QObject>



template <typename TokenT>
class Sensor : public QObject
{
    Q_OBJECT
public:
    explicit Sensor(QObject *parent = nullptr);


    TokenT read();

signals:




private:
    TokenT token = TokenT();
};

#endif // SENSOR_H
