#ifndef RADIO1_H
#define RADIO1_H

#include <QObject>
#include "structs.h"

template <typename BackendT, typename TokenT, typename GEOT>
class Radio1 : public QObject
{
    Q_OBJECT
public:
    explicit Radio1(QObject *parent = nullptr);

    const int MAX_NEIGHBOURS = 10;

    void connect();
    void disconnect();
    TokenT* exchange(GEOT geo);


signals:







private:
    BackendT backendConnectionParam = BackendT();

};

#endif // RADIO1_H
