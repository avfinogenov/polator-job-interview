#ifndef STRUCTS_H
#define STRUCTS_H
#include <vector>



// данная структура являет собой по сути очередь на обработку
// для актуатора. эта структура будет пополнятся автономно от сенсора на отправку
// и от р2 для актуатора
// возможно имя не лучшее подобрано
template <typename ConnectionParamsT, typename TokenT>
struct ConnectionParams
{
    ConnectionParamsT connectionData = ConnectionParamsT();
    TokenT token;
};



#endif // STRUCTS_H
