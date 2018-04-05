/*!
\file
\brief 

шаблоны print_ip
*/
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
enable_if_t
<
    is_arithmetic<T>::value,
    void
> print_ip (T &&arg)
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
enable_if_t
<
    is_same<T, string>::value,
    void
> print_ip (T &&arg)
{
    cout << arg << endl;
}


///-------------------------container---------------------------------------------------///
template <class T>
enable_if_t
<
    is_same<T, vector<typename T::value_type>>::value ||
    is_same<T, list<typename T::value_type>>::value,
    void
> print_ip (T &&arg)
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

    template
    <
        class Test,
        template <class...> class Ref
    >
    struct is_specialization : false_type {};

    template
    <
        template<class...> class Ref,
        class... Args
    >
    struct is_specialization<Ref<Args...>, Ref>: true_type {};

}

template<size_t index, class T>
struct print_tuple
{
    void operator()(T &arg)
    {
        std::cout << std::get<index-1>(arg);
        if ((index-1) != 0)
            std::cout << "..";
        print_tuple<index-1, T>()(arg);
    }
};

template<class T>
struct print_tuple<0, T>
{
    void operator()(T &arg)
    {
        std::cout << std::endl;
    }
};

template <class T>
enable_if_t
<
    TUPLE::is_specialization<T, tuple>::value,
    void
> print_ip (T &&arg)
{
    print_tuple<std::tuple_size<T>::value, T>()(arg);
}

}
