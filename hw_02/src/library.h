#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <deque>
#include <regex>
#include <tuple>
#include <algorithm>
#include <initializer_list>

/*!
\file library.h
\brief заголовок библиотеки

вызов функции version, описания классов для работы с ип адрессами
*/

using ip_address = std::tuple<uint8_t,uint8_t,uint8_t,uint8_t>;         ///Контейнер ип адресса

/*!
@brief перегрузка оператора вывода ип адресса
*/
std::ostream& operator<<(std::ostream &out, const ip_address &ip)
{
    out << (int)std::get<0>(ip) << "."
        << (int)std::get<1>(ip) << "."
        << (int)std::get<2>(ip) << "."
        << (int)std::get<3>(ip) << std::endl;
    return out;
}


/*!
@brief Класс отсортированных или неотсортированных ип адрессов
@detailed Класс позволяет добавлять ип адресса по маски или добавлять все адресса если маска не назначена
*/
template<template <class Q, class Allocator=std::allocator<Q>> class T=std::deque>
struct IP_Address_Sort:public T<ip_address>
{
    static_assert
                (
                    std::is_same<T<ip_address>,std::deque<ip_address>>::value ||
                    std::is_same<T<ip_address>,std::vector<ip_address>>::value
                    ,"IP_Address_Sort accept container vector or deque"
                );

    IP_Address_Sort(const int a=-1,const int b=-1, const int c=-1, const int d=-1):A(a),B(b),C(c),D(d){}

    auto operator<<(const ip_address& val)
    {
        bool flag=false;
        if (A<0 && B<0 && C<0 && D<0)
        {
            this->push_back(val);
            flag=true;
        }
        else
        {
            if ( (std::get<0>(val)==A || A<0) && (std::get<1>(val)==B || B<0) && (std::get<2>(val)==C || C<0) && (std::get<3>(val)==D || D<0))
            {
                this->push_back(val);
                flag=true;
            }
        }
        return flag;
    }

    const int A,B,C,D;
};

/*!
@brief Класс отсортированных ип адрессов
@detailed Класс позволяет добавлять ип адресса при совпадение любово заданного байта
*/
template<template <class Q, class Allocator=std::allocator<Q>> class T=std::deque>
struct IP_Address_Sort_Any:public T<ip_address>
{
    static_assert
                (
                    std::is_same<T<ip_address>,std::deque<ip_address>>::value ||
                    std::is_same<T<ip_address>,std::vector<ip_address>>::value
                    ,"IP_Address_Sort_Any accept container vector or deque"
                );

    IP_Address_Sort_Any(const int afilter):filter(afilter){}

    auto operator<<(const ip_address& val)
    {
        if (std::get<0>(val)==filter || std::get<1>(val)==filter || std::get<2>(val)==filter || std::get<3>(val)==filter)
        {
            this->push_back(val);
            return true;
        }
        return false;
    }

    const uint8_t filter;
};


/*!
@brief Получение ип адрессов из строкового ввода
*/
auto split_ip(std::string &&line)
{
    ///Регулярное выражение для поиска ип адресса в веденной строке
    static std::regex ip_filter ("\\b(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\b");
    static std::smatch pieces;

    std::regex_search(line,pieces,ip_filter);
    auto value = ip_address();
    if (pieces.size()>=5)
    {
        value = std::make_tuple(std::stoi(pieces[1]),std::stoi(pieces[2]),std::stoi(pieces[3]),std::stoi(pieces[4]));
    }
    else
    {
        throw std::invalid_argument( "wrong ip format" );
    }

    return std::move(value);
}

/*!
@brief вызов версии ПО
*/
int version();
