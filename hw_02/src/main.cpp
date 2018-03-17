#include "library.h"

/*!
\file main.cpp
\brief Точка входа

Функция main
*/


int main()
{
    auto data=IP_Address_Sort<std::deque>();                        ///Контейнер ип адрессов без фильтрацией
    auto data_filter_task1 = IP_Address_Sort<std::deque>(1);        ///Контейнер ип адрессов с фильтрацией по 1 байту (1)
    auto data_filter_task2 = IP_Address_Sort<std::deque>(46,70);    ///Контейнер ип адрессов с фильтрацией по 1,2 байту (46,70)
    auto data_filter_task3 = IP_Address_Sort_Any<std::deque>(46);   ///Контейнер ип адрессов с фильтрацией по любому байту (46)

    for(std::string line; std::getline(std::cin, line);)
    {
        ///Заполнить контейнер
        auto value=ip_address();
        try
        {
            value = split_ip(std::move(line));
            data << value;
        }
        catch (std::invalid_argument &e){}
    }

    std::sort(data.rbegin(),data.rend());   ///Отсортировать контейнер в обратном порядке

    for (auto &i:data)  ///Перебрать результаты не фильтровонного контейнера для копирования значений в другие контейнеры
    {
        data_filter_task1 << i;
        data_filter_task2 << i;
        data_filter_task3 << i;
    }


    for (auto &i:data)
    {
        std::cout << i;
    }
    for (auto &i:data_filter_task1)
    {
        std::cout << i;
    }
    for (auto &i:data_filter_task2)
    {
        std::cout << i;
    }
    for (auto &i:data_filter_task3)
    {
        std::cout << i;
    }

    return 0;


}
