#ifndef RADIO2_H
#define RADIO2_H

#include <QObject>
#include "structs.h"
#include "radio2channel.h"

class Radio2 : public QObject
{
    Q_OBJECT
public:
    explicit Radio2(QObject *parent = nullptr) : QObject(parent)
    {

    };


};


template <typename TokenT, typename ConnectionParamsT>
class Radio2F : public Radio2
{
//    // reimplemented from QObject
//        const QMetaObject *metaObject() const;
//        void *qt_metacast(const char *className);
//        int qt_metacall(QMetaObject::Call call, int id,
//                        void **arguments);

//        // static members
//        static QString tr(const char *sourceText,
//                          const char *comment = 0);
//        static QString trUtf8(const char *sourceText,
//                              const char *comment = 0);
//        static const QMetaObject staticMetaObject;
public:
    explicit Radio2F(Radio2ChannelF<ConnectionParamsT, TokenT>* channel, ConnectionParamsT myR2Info)
    {
        m_myR2Info = myR2Info;
        m_channel = channel;
    };

    void process(ConnectionParams<ConnectionParamsT, TokenT> msg);
    void propagate(ConnectionParams<ConnectionParamsT, TokenT> msg);
    void updateNeighbours(std::list<ConnectionParamsT> neighbours);

//signals:


private:

    ConnectionParamsT m_myR2Info = ConnectionParamsT();
    std::list<ConnectionParamsT> m_neighbours;
    Radio2ChannelF<ConnectionParamsT, TokenT>* m_channel = nullptr;
};

#endif // RADIO2_H
