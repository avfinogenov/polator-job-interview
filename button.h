#ifndef BUTTON_H
#define BUTTON_H

#include <QObject>

class Button : public QObject
{
    Q_OBJECT
public:
    explicit Button(QObject *parent = nullptr);


    void doYourThing();
signals:
    void instantiate();

};

#endif // BUTTON_H
