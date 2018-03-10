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
@brief Класс реализации заголовка ип адресса
@detailed Формирует ип адресс на основе веденного текста или чисел, позволяет выводить ип адресс в формате строки, класс может выполнять лексикографическое сравнение
*/
class IP_Header
{

public:

    /*!
    @brief Конструктор заголовка ип адресса,
    @detailed конструктор позволяет создать ип адресс на основее чисел или текста
    */
    IP_Header(){}
    IP_Header(uint8_t a,uint8_t b,uint8_t c,uint8_t d) {header=std::make_tuple(a,b,c,d);}
    IP_Header(const std::string a, const std::string b, const std::string c, const std::string d){header=std::make_tuple(std::stoi(a),std::stoi(b),std::stoi(c),std::stoi(d));}

    /*!
    @brief Метод выводящий ип адресс в виде строки,
    @detailed Метод выводит ип адресс вида "A.B.C.D"
    @return строка, тип определяет компилятор
    */
    auto str() const
    {
        std::stringstream ss;

        ss << static_cast<int>(std::get<0>(header)) << ".";
        ss << static_cast<int>(std::get<1>(header)) << ".";
        ss << static_cast<int>(std::get<2>(header)) << ".";
        ss << static_cast<int>(std::get<3>(header));

        return ss.str();
    }


    /*!
    @brief Метод возвращает указатель на контейнер содержащий внутреннии данные класса,
    @return указатель на контейнер данных
    */
    auto data() const {return &header;}


    /*!
    @brief перегрузка оператора сравнения,
    @detailed Необходимо для лексикографического сравнения
    @return результат сравнения
    */
    bool operator<  (const IP_Header &val) const {return (header< val.header)?true:false;}
    bool operator<= (const IP_Header &val) const {return (header<=val.header)?true:false;}
    bool operator== (const IP_Header &val) const {return (header==val.header)?true:false;}
    bool operator!= (const IP_Header &val) const {return (header!=val.header)?true:false;}
    bool operator>= (const IP_Header &val) const {return (header>=val.header)?true:false;}
    bool operator>  (const IP_Header &val) const {return (header> val.header)?true:false;}

private:
    ip_address header;  ///Контейнер содержащий данные класса (ИП адресс)
};



/*!
@brief Структура фильтра по умолчанию
@detailed Структура всегда работает по умолчанию в классе IP_List, смысл ее всегда записывать в список ип адресса без фильтрации
Структура является Интерфейсом фильтров
*/
struct IIP_Filter
{
    /*!
    @brief Метод сравнения
    @detailed Метод на основе которого класс IP_List по умолчанию всегда принимает любой ип адресс в свой список
    метод является виртуальным, и позволяет переопределить его в других структурах для разработки собственного фильтра
    @return результат всегда true
    */
    virtual bool operator==(const IP_Header &val) {return true;}
};

/*!
@brief Шаблонная структура фильтра по одному из четырех байтов
@detailed Структура позволяет фильтровать ип адресса по одному из четырех байтов
static_assert проверит что variadic шаблон получит не более четырех аргументов
*/
template <uint8_t A, uint8_t... F>
struct IP_Filter:public IIP_Filter
{
    static_assert(sizeof...(F)<=3,"invalid IP_Filter mask");

    /*!
    @brief Метод сравнения
    @detailed Метод на основе которого класс IP_List сможет отфильтровать ип адресс по одному из четырех байтов,
    фильтрование возможно как 1 байта так и нескольких до четырех.
    @return результат в зависимости от совпадения
    */
    bool operator==(const IP_Header &val)
    {
        auto value = val.data();
        uint8_t arg[sizeof...(F)+1]={F...};

        switch (sizeof...(F))
        {
            case 0://filter for first byte
            {
                if (std::get<0>(*value)==A)
                {
                    return true;
                }
                break;
            }
            case 1://filter for first,second byte
            {
                if (std::get<0>(*value)==A && std::get<1>(*value)==arg[0])
                {
                    return true;
                }
                break;
            }
            case 2://filter for first,second,third byte
            {
                if (std::get<0>(*value)==A && std::get<1>(*value)==arg[0] && std::get<2>(*value)==arg[1])
                {
                    return true;
                }
                break;
            }
            case 3://filter for first,second,third,four byte (just find ip address)
            {
                if (std::get<0>(*value)==A && std::get<1>(*value)==arg[0] && std::get<2>(*value)==arg[1] && std::get<3>(*value)==arg[2])
                {
                    return true;
                }
                break;
            }
            default:
            {
            }
        }
        return false;
    }
};


/*!
@brief Шаблонная структура фильтра по любому байту
@detailed Структура позволяет фильтровать ип адресса по любому байту ип адресса
*/
template <uint8_t N>
struct IP_Filter_Any:public IIP_Filter
{
    /*!
    @brief Метод сравнения
    @detailed Метод на основе которого класс IP_List сможет отфильтровать ип адресс по любому байту,
    @return результат в зависимости от совпадения
    */
    bool operator==(const IP_Header &val)
    {
        auto value = val.data();

        if (std::get<0>(*value)==N || std::get<1>(*value)==N || std::get<2>(*value)==N || std::get<3>(*value)==N)
        {
            return true;
        }
        return false;
    }
};


/*!
@brief Класс интерфейса списка ип адрессов
@detailed Интерфейс используется для взаимосвязи разных классов списка ип адрессов
*/
class IIP_List
{
public:

    /*!
    @brief Метод добавления элемента
    @detailed Метод виртуальный, необходима реализации при наследовании
    @return нет результата
    */
    virtual void push_back(const IP_Header &val)=0;

    /*!
    @brief Метод сортировки элементов
    @detailed Метод виртуальный, необходима реализации при наследовании
    @return нет результата
    */
    virtual void sort()=0;
};


/*!
@brief Класс список ип адрессов
@detailed Основной класс контейнер который содержит ИП адресса и также использует сортировки их
В качестве шаблонов класс принимает 1 аргументом контейнер в котором будет хранит ип адресса (им может быть vector или deque)
Вторых аргументом шаблона является метод фильтра принимаемым в контейнере
*/
template<template <class Q, class Allocator=std::allocator<Q>> class T=std::deque, class F=IIP_Filter>
class IP_List:private T<IP_Header>, public IIP_List
{
public:

    /*!
    @brief Конструктор указателей взаимосвязанных списков
    @detailed В конструктор помещаются указатели на другие списки в которые текущий класс будет также добавлять данные паралельно
    static_assert проверить корректность контейнера
    */
    IP_List(std::initializer_list<IIP_List*> aList=std::initializer_list<IIP_List*>()):List(aList)
    {
        static_assert
                    (
                        std::is_same<T<IP_Header>,std::deque<IP_Header>>::value ||
                        std::is_same<T<IP_Header>,std::vector<IP_Header>>::value
                        ,"IP_List accept container vector or deque"
                    );
    }

    /*!
    @brief Метод добавление элемента
    @detailed Метод добавить элемент ИП адресс в внутренний контейнер
    Если присутствует связь с другими списками, контейнер вызовет добавления и в них тоже
    @return нет результата
    */
    void push_back(const IP_Header &val)
    {
        if (Filter==val)
        {
            T<IP_Header>::push_back(val);
        }
        for (auto i=List.begin();i!=List.end();++i)
        {
            (*i)->push_back(val);
        }
    }
    void push_back(const uint8_t a,const uint8_t b,const uint8_t c,const uint8_t d)
    {
        IP_Header val(a,b,c,d);
        push_back(val);
    }
    void push_back(const std::string a, const std::string b, const std::string c, const std::string d)
    {
        IP_Header val(a,b,c,d);
        push_back(val);
    }

    /*!
    @brief Метод сортировки
    @detailed Будет вызвана лексикографическая сортировка элементов ИП адресса
    Если присутствует связь с другими списками, контейнер вызовет сортировки и в них тоже
    @return нет результата
    */
    void sort()
    {
        std::sort(this->begin(),this->end());

        for (auto i=List.begin();i!=List.end();++i)
        {
            (*i)->sort();
        }
        /*std::sort(data.begin(),data.end(),[](const ip_address &lhs, const ip_address &rhs)
        {
            //return true if lhs < rhs

            auto _l_ip = static_cast<uint32_t>(0), _r_ip = static_cast<uint32_t>(0);

            _l_ip = (std::get<0>(lhs))<<24;
            _l_ip|= (std::get<1>(lhs))<<16;
            _l_ip|= (std::get<2>(lhs))<<8;
            _l_ip|= (std::get<3>(lhs));


            _r_ip = (std::get<0>(rhs))<<24;
            _r_ip|= (std::get<1>(rhs))<<16;
            _r_ip|= (std::get<2>(rhs))<<8;
            _r_ip|= (std::get<3>(rhs));

            return (_l_ip<_r_ip)?true:false;
            //return lhs<rhs;
        });*/
    }

    /*!
    @brief Метод вывода полного списка
    @detailed Метод прочитает весь список с внутреннего контейнера и выведет результат в строку
    @param reverse флаг вывода (направления чтения)
    @return строка, компилятор определяет тип автоматически
    */
    auto str(bool reverse=false) const
    {
        std::stringstream ss;

        if (reverse)
        {
            for (auto i=this->rbegin(); i!=this->rend(); ++i)
            {
                ss << i->str() << std::endl;
            }
        }
        else
        {
            for (auto i=this->begin(); i!=this->end(); ++i)
            {
                ss << i->str() << std::endl;
            }
        }

        return ss.str();
    }

private:
    F Filter;                       /// Применяем тип фильтра
    T<IIP_List*> List;              /// указатели на другие списки, взаимосвязь
};

/*!
@brief вызов версии ПО
*/
int version();
