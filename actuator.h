#ifndef ACTUATOR_H
#define ACTUATOR_H

#include <QObject>
#include <iostream>
#include <QDebug>


class Actuator : public QObject
{
    Q_OBJECT

public:
    explicit Actuator(QObject *parent = nullptr) : QObject(parent){}

signals:
    void tokenWritten();

};


template <typename TokenT>
class ActuatorF : public Actuator
{

public:
    explicit ActuatorF(){}
    ~ActuatorF(){};
    void write(TokenT token)
    {
        emit tokenWritten();
        m_output = token;
    }

private:
    TokenT m_output = TokenT();
};

#endif // ACTUATOR_H
