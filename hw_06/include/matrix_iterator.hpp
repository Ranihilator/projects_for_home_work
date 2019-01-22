/*!
\file
\brief matrix iterator header
*/

#pragma once

namespace HW_06
{

/*!
\brief Matrix iterator helper
\tparam I - Matrix data buffer iterator
\tparam T - Type of data in matrix
*/
template <class I, class T>
class Matrix_Iterator
{
public:
	Matrix_Iterator(I _data_begin, I _data_end);

	auto* operator->();
	auto& operator*();
	auto& operator++();
	auto& operator=(const T& _data);
	bool operator!=(const Matrix_Iterator& other);
	bool operator==(const Matrix_Iterator& other);

private:
	T value;
	I iterator;
	I iterator_end;
};

template <class I, class T>
Matrix_Iterator<I, T>::Matrix_Iterator(I _data_begin, I _data_end):
iterator(_data_begin), iterator_end(_data_end)
{}

template <class I, class T>
auto* Matrix_Iterator<I, T>::operator->()
{
	auto map_value = this->iterator.operator*();
	value = std::tuple_cat(map_value.first, std::make_tuple(map_value.second));

	return &value;
}

template <class I, class T>
auto& Matrix_Iterator<I, T>::operator*()
{
	auto map_value = this->iterator.operator*();
	value = std::tuple_cat(map_value.first, std::make_tuple(map_value.second));

	return value;
}

template <class I, class T>
auto& Matrix_Iterator<I, T>::operator++()
{
	this->iterator = std::next(iterator);

	if (this->iterator == this->iterator_end)
		return value;

	auto map_value = iterator.operator*();
	value = std::tuple_cat(map_value.first, std::make_tuple(map_value.second));

	return value;
}

template <class I, class T>
auto& Matrix_Iterator<I, T>::operator=(const T& _data)
{
	this->iterator.second = _data;

	auto map_value = iterator.operator*();
	value = std::tuple_cat(map_value.first, std::make_tuple(map_value.second));

	return value;
}

template <class I, class T>
bool Matrix_Iterator<I, T>::operator!=(const Matrix_Iterator& other)
{
	return !(*this == other);
}

template <class I, class T>
bool Matrix_Iterator<I, T>::operator==(const Matrix_Iterator& other)
{
	return (this->iterator == other.iterator);
}

}
