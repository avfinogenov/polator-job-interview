#ifndef ACTUATOR_H
#define ACTUATOR_H

#include <QObject>



class Actuator : public QObject
{
    Q_OBJECT

public:
    explicit Actuator(QObject *parent = nullptr) : QObject(parent)
    {

    }


};


template <typename TokenT>
class ActuatorF : public Actuator
{

public:
    explicit ActuatorF()
    {

    }

    void write(TokenT token);
//signals:



private:
    TokenT output = TokenT();
};

#endif // ACTUATOR_H
