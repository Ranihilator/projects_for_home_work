/*!
\file library.cpp
\brief Реализация библиотеки вывод версии ПО

вызов функции version
*/


#include <iostream>
#include "library.h"
#include "version.h"

/*!
Функция вызова версии ПО
\return {возвращает число формата INT}
*/
int version()
{
    return PROJECT_VERSION_PATCH;
}
