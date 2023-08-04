#ifndef RADIO2CHANNEL_H
#define RADIO2CHANNEL_H

#include <QObject>
#include "structs.h"
/* for testing
 *
 *
 *
 *
 */

class Radio2Channel : public QObject
{
Q_OBJECT

public:

    explicit Radio2Channel(QObject *parent = nullptr) : QObject(parent)
    {

    }
};



template <typename ConnectionParamsT, typename TokenT>
class Radio2ChannelF : public Radio2Channel
{

public:
    explicit Radio2ChannelF()
    {

    }
    void sendToChannel(ConnectionParams<ConnectionParamsT, TokenT> inputMsg)
    {
        m_msgs.push_back(inputMsg);
    }

    ConnectionParams<ConnectionParamsT, TokenT> readFromChannel()
    {
        return m_msgs.front();
    }
    void confirmReading()
    {
        m_msgs.pop_front();
    }

    //signals:




private:
    std::list<ConnectionParams<ConnectionParamsT, TokenT>> m_msgs;
};

#endif // RADIO2CHANNEL_H