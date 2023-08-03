#ifndef MYSTATE_H
#define MYSTATE_H
#include <QState>
#include <QDebug>
class MyState: public QState
{
    Q_OBJECT
private:
    QString _stateName;
public:
    MyState(QString stateName, QState * parent = 0):QState(parent), _stateName(stateName){}
    ~MyState(){}

protected:
   virtual  void onEntry(QEvent * event)
    {
        qDebug() << _stateName << " start.";
    }

   virtual  void onExit(QEvent * event)
    {
        qDebug() << _stateName << " stop.";
    }
signals:
    void finished();
    //void exited();
};
#endif // MYSTATE_H
