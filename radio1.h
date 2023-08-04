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
    explicit Radio1(Backend<BackendT, R2ConnectionParamsT>* backend, QObject *parent = nullptr) : QObject(parent)
    {
        m_backend = backend;
    };

    const int MAX_NEIGHBOURS = 10;

    // если функция будет вызвана при активном подключении - перейти в состояние ошибки
    void connect();
    void disconnect();
    std::list<R2ConnectionParamsT> exchange(GEOT geo);


signals:







private:
    BackendT backendConnectionParam = BackendT();
    // возможно переделать на стейт машину
    bool m_isConnected = false;
    Backend<BackendT, R2ConnectionParamsT>* m_backend = nullptr;
};



//template <typename BackendT, typename R2ConnectionParamsT,
//          typename TokenT, typename GEOT>
//Radio1::Radio1(Backend<BackendT, R2ConnectionParamsT>* backend, QObject *parent) : QObject(parent)
//{

//}





#endif // RADIO1_H
