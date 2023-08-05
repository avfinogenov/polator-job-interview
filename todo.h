#ifndef TODO_H
#define TODO_H

/* пояснения
 * реализацию шаблонов пишу внутрь класса, потому что снаружи среда почему то не позволяет
 */



/* todo
//
// first look at
// class iot +
// struct geo +
// struct connectionParam +


// simple qsm example


// на qobject формально
// r1
// r2
// sensor
// actuator
// iot


//r1
// поверхностно объект бекенда

// логику подключения
// логику обмена
// логику отключения



//r2
// класс радиоканала



// генерация токенов в сенсоре

// хранение токенов в актуаторе



// дип дайв ин иот

// state machine stuff
*/
//-----------------------------------------------------------------------------

// r2 signal to iot
// sensor signal to iot



// тестирование






/* мысли и идеи



// сенсор должен иметь возможность получать токены на вход или генерировать их случайно по вызову функции рид
// иот должен обновлять гео
// для упращения коннект и дисконет в р1 будут менять только qsm сами функции имитировать связь не будут
// функцию эксчендж заменю на бекенд сенд и бекенд ресив
// сенд будет выплевывать гео
// ресив будет забирать набор сведений о соседях
// актуатор будет хранить токены
// р2 будет иметь функцию ввода вывода сообщений (симуляция радиоканала)
// радио пакет будет иметь 2 поля - коннекшн парамс и токен (по коннекшн парамсу будет определятся, брать ли пакет)

// состояния иот сделал в виде картинки
// скорее всего картинку надо будет уточнить
// почитав про qsm по подробнее решил, что
// будут следующие состояния
// startingInitialization
// awaitingButton
// talkingToBackend
// WorkingWithSensor - mainWorkingState
// errorState - он же будет finishState


// иот реализую ввиде класса под условное железо с виртуальными функциями, которые потом перегружу дочерним классом под тестирование(testIOT)
// в частности р1 и р2. перегружатся будут только функции сети и условного железа

// несмотря на то, что задачу можно решить и через многопоточность ( в частности симуляцию сети),
// обойдусь синхронным поведением, потому что уже придумал, да и нет задачи сделать асинхронно, да и дольше это

//testIOT
// будет хранить в себе указатель на объект симуляции бекенда
// так же указатель на объект, симулирующий сеть р2
// батон будет нажиматься вручную в тестировании, условно это объект, который хранит указатель на свой iot, и при "нажатии" дергает sync iot
// если нормально пойдет, попробую сделать через сигналы

// возможно есть вариант сделать в р1 и р2 и других по qsm, которые будут отправлять сигналы, о том, что отработали

// поскольку стейты и стейт машина работают на сигналах, есть смысл все объекты, которые учавствуют в взаимодействии



// можно сделать сенсор закрытым, и он асинхронно будет генерить токены время от времени
// upd он должен быть закрытым(по заданию)
*/




#endif // TODO_H
