#ifndef RADIO2_H
#define RADIO2_H

#include <QObject>


template <typename TokenT, typename ConnectionParamsT>
class Radio2 : public QObject
{
    Q_OBJECT
public:
    explicit Radio2(ConnectionParamsT myR2Info, QObject *parent = nullptr) : QObject(parent)
    {
        m_myR2Info = myR2Info;
    };

    void process(TokenT token);
    void propagate(TokenT token);
    void updateNeighbours(std::list<ConnectionParamsT> neighbours);

signals:


private:

    ConnectionParamsT m_myR2Info = ConnectionParamsT();
    std::list<ConnectionParamsT> m_neighbours;
};

#endif // RADIO2_H
