#include "library.h"

/*!
\file main.cpp
\brief Точка входа

Функция main
*/


int main()
{
    IP_Address_Sort<std::deque> data;
    IP_Address_Sort<std::deque> data_filter_task1(1);
    IP_Address_Sort<std::deque> data_filter_task2(46,70);
    IP_Address_Sort_Any<std::deque> data_filter_task3(46);

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
            ip_address value = std::make_tuple(std::stoi(pieces[1]),std::stoi(pieces[2]),std::stoi(pieces[3]),std::stoi(pieces[4]));
            data(value);
            data_filter_task1(value);data_filter_task2(value);data_filter_task3(value);
        }
    }

    std::sort(data.rbegin(),data.rend());
    std::sort(data_filter_task1.rbegin(),data_filter_task1.rend());
    std::sort(data_filter_task2.rbegin(),data_filter_task2.rend());
    std::sort(data_filter_task3.rbegin(),data_filter_task3.rend());

    std::cout << data.str().str();
    std::cout << data_filter_task1.str().str();
    std::cout << data_filter_task2.str().str();
    std::cout << data_filter_task3.str().str();

    return 0;


}
