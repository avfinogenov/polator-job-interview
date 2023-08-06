#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <vector>
#include <QDebug>
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
    explicit BackendF(BackendT backendConnectionParam) : Backend(nullptr)
    {
        m_backendConnectionParam = backendConnectionParam;
    }
    void addParamsToSend(R2ConnectionParamsT param)
    {
        m_paramsToSend.push_back(param);
    }
    std::vector<R2ConnectionParamsT> getParamsToSend(GEOT geo)
    {
        // geo сейчас не используется, но может быть на основании
        // него симуляция будет выбирать что посылать
        m_geo = geo;
        return m_paramsToSend;
    }
    // коннект и дисконнект возвращают статус соединения
    bool connect(BackendT backendConnectionParams)
    {
//        qInfo() << m_isConnected;
//        qInfo() << backendConnectionParams;
//        qInfo() << m_backendConnectionParam;

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
    std::vector<R2ConnectionParamsT> m_paramsToSend;
    bool m_isConnected = false;
    GEOT m_geo;



};

#endif // BACKEND_H
