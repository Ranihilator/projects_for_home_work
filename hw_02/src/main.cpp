/*!
\file
\brief Основной файл main

Приложения filter
На входящий поток ип адрессов выводит их в отсортированном лексиграфическм виде.
- ИП адресс в обратном порядке.
- ИП адресс в обратном порядке, где в 1 байте содержиться 1
- ИП адресс в обратном порядке, где в 1 байте содержиться 46 а во втором байте содержиться 70
- ИП адресс в обратном порядке, где в любом байте содержится 46
*/

#include "filter.h"

using namespace HW_02::FILTER;

/*!
Начала программы
\param[in] argc кол-во аргументов
\param[in] argv массив аргументов
\return Код завершения
*/
int main(int argc, char* argv[])
{
	///Регулярное выражение для поиска ип адресса в веденной строке
	std::regex ip_filter (FILTER_REGEX);

	auto data = IP_Address_Sort();                      ///Контейнер ип адрессов без фильтрацией
	auto data_filter_task1 = IP_Address_Sort(1);        ///Контейнер ип адрессов с фильтрацией по 1 байту (1)
	auto data_filter_task2 = IP_Address_Sort(46, 70);   ///Контейнер ип адрессов с фильтрацией по 1,2 байту (46,70)
	auto data_filter_task3 = IP_Address_Sort_Any(46);   ///Контейнер ип адрессов с фильтрацией по любому байту (46)

	for(std::string line; std::getline(std::cin, line);)
	{
		///Заполнить контейнер
		auto value = ip_address();
		try
		{
			value = split_ip(std::move(line), ip_filter);
			data << value;
		}
		catch (std::invalid_argument &e) {}
	}

	std::sort(data.rbegin(), data.rend());  ///Отсортировать контейнер в обратном порядке

	for (auto &i : data) ///Скопировать результат в другие контейнеры
	{
		/// т.к. основной контейнер отсортирован, то и копируемые результаты будут уже отсортированные в других контейнерах
		data_filter_task1 << i; ///Контейнер получит ип адресс, но сохранит у себя только те, что соответствуют фильтраций по 1 байту
		data_filter_task2 << i; ///Контейнер получит ип адресс, но сохранит у себя только те, что соответствуют фильтраций по 1,2 байту
		data_filter_task3 << i; ///Контейнер получит ип адресс, но сохранит у себя только те, что соответствуют фильтраций по любому байту
	}

	for (auto &i : data)
		std::cout << i;

	for (auto &i : data_filter_task1)
		std::cout << i;

	for (auto &i : data_filter_task2)
		std::cout << i;

	for (auto &i : data_filter_task3)
		std::cout << i;

	return 0;


}
