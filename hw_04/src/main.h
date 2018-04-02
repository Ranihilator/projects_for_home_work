#pragma once

#include <iostream>
#include <sstream>
#include <list>
#include <vector>
#include <deque>
#include <tuple>

namespace PRINT
{

using namespace std;


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
namespace CONTAINER
{
template <class T>       struct is_stl_container:false_type {};
template <class... Args> struct is_stl_container<vector            <Args...>>:true_type {};
template <class... Args> struct is_stl_container<list              <Args...>>:true_type {};
}


template <class T>
enable_if_t<CONTAINER::is_stl_container<T>::value,void> print_ip (T &&arg)
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
namespace TUPLE
{
template<typename Test, template<typename...> class Ref>
struct is_specialization : false_type {};

template<template<typename...> class Ref, typename... Args>
struct is_specialization<Ref<Args...>, Ref>: true_type {};
}


template<int index, class... T>
struct print_tuple
{
    void operator() (tuple<T...>& t)
    {
        cout << get<index>(t) << "..";
        print_tuple<index - 1, T...> {}(t);
    }
};

template<class... T>
struct print_tuple<0, T...>
{
    void operator() (tuple<T...>& t)
    {
        cout << get<0>(t) << "";
    }
};

template<class... T>
void print(tuple<T...>& t)
{
    const auto size = tuple_size<tuple<T...>>::value;
    print_tuple<size - 1, T...> {}(t);
}

template <class T>
enable_if_t<TUPLE::is_specialization<T, tuple>::value,void> print_ip (T &&arg)
{
    print(arg);
}

}
