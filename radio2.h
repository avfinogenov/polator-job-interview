#ifndef RADIO2_H
#define RADIO2_H

#include <QObject>
#include <future>
#include "structs.h"
#include "radio2channel.h"

class Radio2 : public QObject
{
    Q_OBJECT
public:
    explicit Radio2(QObject *parent = nullptr) : QObject(parent){};

signals:
    void sendError(QString s);
    void confirmReading();




};

template <typename TokenT, typename ConnectionParamsT>
class Radio2F : public Radio2
{

public:
    explicit Radio2F(Radio2ChannelF<ConnectionParamsT, TokenT>* channel, ConnectionParamsT myR2Info)
    {

        m_myR2Info = myR2Info;

        m_channel = channel;
         connect(m_channel, &Radio2Channel::gotNewInfo, this, &Radio2F::read);

    };
    ~Radio2F(){};
    void process(TokenT* token)
    {
        ConnectionParams<ConnectionParamsT, TokenT> msgToRead;
        msgToRead = m_channel->readFromChannel();
        if (msgToRead.connectionData == m_myR2Info)
        {
            *token = msgToRead.token;
            m_channel->confirmReading();

        }
    }
    void propagate(TokenT token)
    {
        ConnectionParams<ConnectionParamsT, TokenT> msgToSend;
        msgToSend.token = token;
        for (int i = 0; i < m_neighbours.size(); ++i)
        {

            msgToSend.connectionData = m_neighbours[i];
            m_channel->sendToChannel(msgToSend);
        }


    }
    void updateNeighbours(std::vector<ConnectionParamsT> neighbours)
    {
        m_neighbours = neighbours;
    }
    bool isHaveNeighbours()
    {
        return !m_neighbours.empty();
    }

    void read()
    {

        ConnectionParams<ConnectionParamsT, TokenT> msgToRead;
        msgToRead = m_channel->readFromChannel();

        if (msgToRead.connectionData == m_myR2Info)
        {
            emit confirmReading();

        }


    }

private:

    bool m_isWorking = false;
    ConnectionParamsT m_myR2Info = ConnectionParamsT();
    std::vector<ConnectionParamsT> m_neighbours;
    Radio2ChannelF<ConnectionParamsT, TokenT>* m_channel = nullptr;

};

#endif // RADIO2_H
