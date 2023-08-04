#ifndef STRUCTS_H
#define STRUCTS_H
#include <list>



// данная структура являет собой по сути очередь на обработку
// для актуатора. эта структура будет пополнятся автономно от сенсора на отправку
// и от р2 для актуатора
// возможно имя не лучшее подобрано
template <typename ConnectionParamsT, typename Token>
struct ConnectionParams
{
    ConnectionParamsT data = ConnectionParamsT();
    std::list<Token> tokens;
};



#endif // STRUCTS_H
