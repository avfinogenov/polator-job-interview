#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <list>
// нужна функция генерации коннекшн парамсов
// нужна функция получения коннекшн парамсов
// возможно QObject тут не нужен
// хотя можно кидать сигнал, и ловить его стейт машиной


template <typename BackendT, typename R2ConnectionParamsT>
class Backend : public QObject
{
    Q_OBJECT
public:
    explicit Backend(QObject *parent = nullptr);
    void generateParamsToSend();
    std::list<R2ConnectionParamsT> getParamsToSend();
    bool connect(BackendT backendConnectionParams);
    bool disconnect();



signals:



private:
    BackendT m_backendConnectionParam = BackendT();
    std::list<R2ConnectionParamsT> m_paramsToSend;
    bool m_isConnected = false;



};

#endif // BACKEND_H
