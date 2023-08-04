#ifndef ACTUATOR_H
#define ACTUATOR_H

#include <QObject>



template <typename TokenT>
class Actuator : public QObject
{
    Q_OBJECT
public:
    explicit Actuator(QObject *parent = nullptr);

    void write(TokenT token);
signals:



private:
    TokenT output = TokenT();
};

#endif // ACTUATOR_H
