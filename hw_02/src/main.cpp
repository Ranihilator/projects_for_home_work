#include "library.h"

/*!
\file main.cpp
\brief Точка входа

Функция main
*/
int main()
{
    IP_List<std::deque,IP_Filter<1>> data_filter_task1;         ///Список ИП адрессов в отсортированном виде по первому байту
    IP_List<std::deque,IP_Filter<46,70>> data_filter_task2;     ///Список ИП адрессов в отсортированном виде по первому и второму байту
    IP_List<std::deque,IP_Filter_Any<46>> data_filter_task3;    ///Список ИП адрессов в отсортированном виде по любому байту

    IP_List<std::deque> data({&data_filter_task1,&data_filter_task2,&data_filter_task3});   ///Общий Список ИП адрессов со связанными списками

    ///Регулярное выражение для поиска ип адресса в веденной строке
    std::regex ip_filter ("(\\d+)\\.(\\d+)\\.(\\d+)\\.(\\d+)");
    std::smatch pieces;

    ///Чтение данных
    for(std::string line; std::getline(std::cin, line);)
    {
        std::regex_search(line,pieces,ip_filter);
        if (pieces.size()>=5)
        {
            ///Добавление строки в общий список
            data.push_back(IP_Header(pieces[1],pieces[2],pieces[3],pieces[4]));
        }
    }

    data.sort();                                ///Сортировка списка включая связанные списки
    std::cout << data.str(true);                ///Вывод общего списка
    std::cout << data_filter_task1.str(true);   ///Вывод списка по первому байту
    std::cout << data_filter_task2.str(true);   ///Вывод списка по первому и второму байту
    std::cout << data_filter_task3.str(true);   ///Вывод списка по любому байту
    return 0;
}
