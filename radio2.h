#ifndef RADIO2_H
#define RADIO2_H

#include <QObject>


template <typename TokenT>
class Radio2 : public QObject
{
    Q_OBJECT
public:
    explicit Radio2(QObject *parent = nullptr);

    void process(TokenT token);
    void propagate(TokenT token);

signals:

};

#endif // RADIO2_H
