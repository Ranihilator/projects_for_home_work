#pragma once

#include <iostream>
#include <sstream>
#include <list>
#include <vector>
#include <deque>
#include <tuple>

namespace PRINT
{

using std::cout;
using std::endl;
using std::enable_if_t;
using std::is_arithmetic;
using std::is_same;
using std::stringstream;
using std::string;
using std::vector;
using std::list;


///-------------------------value---------------------------------------------------///
template <class T>
enable_if_t<is_arithmetic<T>::value,void> print_ip (T &&arg)
{
    uint8_t size = sizeof(T);
    uint8_t *data = (uint8_t*)&arg;

    stringstream str;

    for (auto i = size-1; i >= 0; --i)
    {
		if (str.tellp() != 0)
			str << ".";

        str << static_cast<int64_t>(data[i]);
    }

    cout << str.str() << endl;
}

///-------------------------string---------------------------------------------------///
template <class T>
enable_if_t<is_same<T, string>::value,void> print_ip (T &&arg)
{
    cout << arg << endl;
}


///-------------------------container---------------------------------------------------///
template <class T>       struct is_stl_container:std::false_type{};
template <class... Args> struct is_stl_container<std::vector            <Args...>>:std::true_type{};
template <class... Args> struct is_stl_container<std::list              <Args...>>:std::true_type{};

template <class T>
enable_if_t<is_stl_container<T>::value,void> print_ip (T &&arg)
{
    stringstream str;

    for (const auto &i : arg)
    {
        if (str.tellp() != 0)
			str << "..";

        str << static_cast<int64_t>(i);
    }
    cout << str.str() << endl;
}



///-------------------------tuple---------------------------------------------------///
template<typename Test, template<typename...> class Ref>
struct is_specialization : std::false_type {};

template<template<typename...> class Ref, typename... Args>
struct is_specialization<Ref<Args...>, Ref>: std::true_type {};

template <class T>
enable_if_t<is_specialization<T, std::tuple>::value,void> print_ip (T &&arg)
{
    std::cout << "tuple" << std::endl;
}

}
