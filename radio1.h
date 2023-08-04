#ifndef RADIO1_H
#define RADIO1_H

#include <QObject>
#include "structs.h"
#include "backend.h"

class Radio1 : public QObject
{
    Q_OBJECT
public:

    explicit Radio1(QObject *parent = nullptr) : QObject(parent)
    {

    };

};


template <typename BackendT, typename R2ConnectionParamsT,
          typename GEOT>
class Radio1F : public Radio1
{

public:
    explicit Radio1F(BackendF<BackendT, R2ConnectionParamsT, GEOT>* backend, BackendT backendConnectionParams)
    {
        m_backend = backend;
        m_backendConnectionParam = backendConnectionParams;
    };

    const int MAX_NEIGHBOURS = 10;

    // если функция будет вызвана при активном подключении - перейти в состояние ошибки
    void connect()
    {
        if (!m_isConnected)
        {
             m_isConnected = m_backend->connect(m_backendConnectionParam);
        }
        else
        {
            //todo error
        }
    }
    void disconnect()
    {
        if (m_isConnected)
        {
            m_isConnected = m_backend->disconnect();
        }
        else
        {
            //todo error
        }
    }
    std::list<R2ConnectionParamsT> exchange(GEOT geo)
    {
        if (m_isConnected)
        {
            return m_backend->getParamsToSend(geo);
        }
        else
        {
            //todo error
            return std::list<R2ConnectionParamsT>();
        }
    }


//signals:







private:
    BackendT m_backendConnectionParam = BackendT();
    // возможно переделать на стейт машину
    bool m_isConnected = false;
    BackendF<BackendT, R2ConnectionParamsT, GEOT>* m_backend = nullptr;
};







#endif // RADIO1_H
