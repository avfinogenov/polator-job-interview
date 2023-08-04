#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <list>
// нужна функция генерации коннекшн парамсов
// нужна функция получения коннекшн парамсов
// возможно QObject тут не нужен
// хотя можно кидать сигнал, и ловить его стейт машиной

class Backend : public QObject
{
Q_OBJECT

public:

    explicit Backend(QObject *parent = nullptr) : QObject(parent)
    {

    }


};




template <typename BackendT, typename R2ConnectionParamsT,
          typename GEOT>
class BackendF : public Backend
{

public:
    explicit BackendF() : Backend(nullptr)
    {

    }
    void generateParamsToSend();
    std::list<R2ConnectionParamsT> getParamsToSend(GEOT geo)
    {
        // geo сейчас не используется, но может быть на основании
        // него симуляция будет выбирать что посылать
        m_geo = geo;
        return m_paramsToSend;
    }
    // коннект и дисконнект возвращают статус соединения
    bool connect(BackendT backendConnectionParams)
    {
        // вообще обычно такое принято писать понятнее, но так как внутри класса решил написать покороче
        return (m_isConnected = !m_isConnected && backendConnectionParams == m_backendConnectionParam);
    }
    bool disconnect()
    {
        return (m_isConnected = !m_isConnected);
    }



//signals:



private:
    BackendT m_backendConnectionParam = BackendT();
    std::list<R2ConnectionParamsT> m_paramsToSend;
    bool m_isConnected = false;
    GEOT m_geo;



};

#endif // BACKEND_H
