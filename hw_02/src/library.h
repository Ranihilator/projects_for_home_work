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
@brief Класс отсортированных или неотсортированных ип адрессов
@detailed Класс позволяет добавлять ип адресса по маски или добавлять все адресса если маска не назначена
*/
template<template <class Q, class Allocator=std::allocator<Q>> class T=std::deque>
struct IP_Address_Sort:public T<ip_address>
{
    IP_Address_Sort(const int a=-1,const int b=-1, const int c=-1, const int d=-1):A(a),B(b),C(c),D(d){}

    bool operator()(const ip_address& val)
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

    std::stringstream str()
    {
        std::stringstream ss;
        for (auto &i:(*this))
        {
            ss << static_cast<int>(std::get<0>(i)) << ".";
            ss << static_cast<int>(std::get<1>(i)) << ".";
            ss << static_cast<int>(std::get<2>(i)) << ".";
            ss << static_cast<int>(std::get<3>(i)) << std::endl;
        }
        return std::move(ss);
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
    IP_Address_Sort_Any(const int afilter):filter(afilter){}

    bool operator()(const ip_address& val)
    {
        if (std::get<0>(val)==filter || std::get<1>(val)==filter || std::get<2>(val)==filter || std::get<3>(val)==filter)
        {
            this->push_back(val);
            return true;
        }
        return false;
    }

    std::stringstream str()
    {
        std::stringstream ss;
        for (auto &i:(*this))
        {
            ss << static_cast<int>(std::get<0>(i)) << ".";
            ss << static_cast<int>(std::get<1>(i)) << ".";
            ss << static_cast<int>(std::get<2>(i)) << ".";
            ss << static_cast<int>(std::get<3>(i)) << std::endl;
        }
        return std::move(ss);
    }

    const uint8_t filter;
};

/*!
@brief вызов версии ПО
*/
int version();
