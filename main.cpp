#include <QCoreApplication>
#include <QStateMachine>
#include <QState>
#include <QFinalState>
#include <QDebug>
#include <iostream>
#include <future>

#include "mystatemachine.h"
#include "iot.h"

/* пояснения
 * пока иот не войдет в режим "ожидания ввода", токены сенсора будут игнорироватся
 * если данных о соседях нет, будет ждать кнопки на синхронизацию
 * после успешной синхронизации может быть в одном из трех состояний - ожидание ввода, обработка данных сенсора, обработка информации р2
 * в текущей реализации, если сигнал придет не на режиме ожидание ввода, ввод проигнорируется и данные потеряются,
 * режим не переключится (механики очереди тут нет)
 * далее сенсор на своем потоке раз в 10 секунд генерит токен и пытается инициировать пропагейт
 * при поступлении данных в канал, канал симулирует работу сети, и в режиме очереди оттуда все по очереди свой пакет забирают
 * (тоже по сигналу от канала)
 * баттн получился настолько простой, что я даже не знаю как его прокомментировать
 *
 * mystatemachine - пример, на котором тестилась qstatemachine. решил не удалять, пусть будет.
 * backend - заглушка, подыгрывающая бекенд (для тестирования функционала)
 * radio2channel - заглушка, симулирующая сеть ( для тестирования)
 * todo - текстовый файл, помогающий в работе, кода там нет
 * structs - остался от решения без шаблонов, поскольку в шаблон можно и структуру и объект положить,
 * осталась только одна структура, в которой 2 поля нужны в логике работы
 * все остальные файлы описывают сущности с названиями, совпадающими с заданием
 *
 */


// знаю, что так делать не хорошо, но так сильно проще тестить
// функция потока, которая будет работать на момент main return
void threadv(Button* b)
{
    char tmp;

    bool isStarted = false;
    while (true)
    {
        std::cin >> tmp;

        if (!isStarted)
        {
            b->doYourThing();
            isStarted = true;
        }



    }

}



int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    Radio2ChannelF<int, int> r2channel;
    int x = 1;
    std::vector<Button*> buttons;
    Button b;
    std::vector<IOTF<int, int, int, int>*> iots;
    BackendF<int, int, int> backend(x);
    for (int i = 0; i < 10; ++i)
    {

        IOTF<int, int, int, int>* iot = new IOTF<int, int, int, int>(&r2channel, i + 1,  1, &backend, "iot " + QString(i));
        backend.addParamsToSend(i + 1);
        iots.push_back(iot);
    }

    for (int i = 0; i < 10; ++i)
    {
        QObject::connect(&b, SIGNAL(instantiate()), iots[i], SLOT(gotButtonSignal()));
    }


    std::future<void> thread1 = std::async(std::launch::async, &threadv, &b);

    return app.exec();
}



