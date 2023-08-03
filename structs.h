#ifndef STRUCTS_H
#define STRUCTS_H
#include <list>

template <typename T>
struct GEO
{
    T data;

};



template <typename ConnectionParamsT, typename Token>
struct ConnectionParams
{
    ConnectionParamsT data = ConnectionParamsT();
    std::list<Token> tokens;
};



#endif // STRUCTS_H
