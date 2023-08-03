#include "test2.h"

test2::test2():QObject()
{

}


void test2::update()
{
    emit signalTest();
}

test2::~test2()
{

}
