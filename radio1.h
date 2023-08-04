#ifndef RADIO1_H
#define RADIO1_H

#include <QObject>
#include "structs.h"
#include "backend.h"


template <typename BackendT, typename R2ConnectionParamsT,
          typename GEOT>
class Radio1 : public QObject
{
    Q_OBJECT
public:
    explicit Radio1(Backend<BackendT, R2ConnectionParamsT, GEOT>* backend, QObject *parent = nullptr) : QObject(parent)
    {
        m_backend = backend;
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

    }


signals:







private:
    BackendT m_backendConnectionParam = BackendT();
    // возможно переделать на стейт машину
    bool m_isConnected = false;
    Backend<BackendT, R2ConnectionParamsT, GEOT>* m_backend = nullptr;
};







#endif // RADIO1_H
