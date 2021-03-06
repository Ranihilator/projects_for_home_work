/*!
\file
\brief matrix header

*/
#pragma once

#include <iostream>
#include <sstream>
#include <functional>
#include <tuple>
#include <vector>
#include <initializer_list>
#include <memory>
#include <unordered_map>

#include "matrix_node.hpp"
#include "matrix_iterator.hpp"

/*!
\brief HW_06 namespace
\details Matrix task
*/
namespace HW_06
{

/*!
\brief N dimension matrix
\tparam T - Type of data in matrix
\tparam N - sparse number
\tparam D - Dimension of matrix
*/
template <class T, T N=T(), size_t D = 2>
class Matrix
{
using Matrix_t = typename Matrix_Coordinate<D>::type;				///< Matrix coordinate
using Matrix_Value_t = typename Matrix_Coordinate<D, T>::type;		///< Matrix coordinate + Value

/*!
\brief Custom Hash class to key of Matrix coordinate
*/
struct Matrix_Hash
{
	size_t operator()(const Matrix_t &s) const
	{
		std::stringstream ss;
		Get_Matrix_Coordinate<std::tuple_size<Matrix_t>::value, Matrix_t>()(s, ss);
		return std::hash<std::string>()(ss.str());
	}
};

public:
	Matrix() = default;
	Matrix(const Matrix& other);

	Matrix& operator=(const Matrix& other);

	/*!
	\brief get access to matrix node
	\param[in] index matrix node index
	\return return matrix node
	*/
	Matrix& operator[](const size_t index);

	/*!
	\brief get access to matrix value stored in node
	\return return value
	*/
	operator const T();

	/*!
	\brief write new value in matrix node
	\param[in] _data input
	\return return reference value in matrix node
	*/
	const T& operator=(const T& _data);

	/*!
	\brief clear matrix
	*/
	void clear();

	/*!
	\brief get actual stored elements in matrix
	*/
	size_t size() const;

	/*!
	\brief begin iterator
	\return return Matrix_Iterator
	*/
	auto begin();

	/*!
	\brief end iterator
	\return return Matrix_Iterator
	*/
	auto end();

private:
	const T sparse_data = N;							///< Sparse number
	std::unordered_map<Matrix_t, T, Matrix_Hash> data;	///< Matrix data buffer

	mutable std::vector<size_t> coordinate;				///< Current coordinate to get access to data
};


template <class T, T N, size_t D>
Matrix<T, N, D>::Matrix(const Matrix& other)
{
	this->data = other.data;
	other.coordinate.clear();
}

template <class T, T N, size_t D>
Matrix<T, N, D>& Matrix<T, N, D>::operator[](const size_t index)
{
	if (this->coordinate.size() != D)
		this->coordinate.emplace_back(index);

	return *this;
}

template <class T, T N, size_t D>
Matrix<T, N, D>& Matrix<T, N, D>::operator=(const Matrix& other)
{
	this->data = other.data;
	other.coordinate.clear();

	return *this;
}


template <class T, T N, size_t D>
Matrix<T, N, D>::operator const T()
{
	if (this->coordinate.size() != D)
		return this->sparse_data;

	Matrix_t dest;
	if (!Set_Matrix_Coordinate<std::tuple_size<Matrix_t>::value, Matrix_t, std::vector<size_t>>()(dest, this->coordinate))
		return this->sparse_data;

	auto iter = this->data.find(dest);

	if (iter == this->data.end())
		return this->sparse_data;

	return iter->second;
}

template <class T, T N, size_t D>
const T& Matrix<T, N, D>::operator=(const T& _data)
{
	if (this->coordinate.size() != D)
		return this->sparse_data;

	Matrix_t dest;
	if (!Set_Matrix_Coordinate<std::tuple_size<Matrix_t>::value, Matrix_t, std::vector<size_t>>()(dest, this->coordinate))
		return this->sparse_data;

	auto iter = this->data.find(dest);

	if (iter == this->data.end() && _data == this->sparse_data)
		return this->sparse_data;

	if (_data == this->sparse_data)
	{
		this->data.erase(iter);
		return this->sparse_data;
	}

	this->data[dest] = _data;
	return this->data[dest];
}

template <class T, T N, size_t D>
size_t Matrix<T, N, D>::size() const
{
	return this->data.size();
}

template <class T, T N, size_t D>
void Matrix<T, N, D>::clear()
{
	this->data.clear();
}

template <class T, T N, size_t D>
auto Matrix<T, N, D>::begin()
{
	return Matrix_Iterator<typename std::unordered_map<Matrix_t, T, Matrix_Hash>::iterator, Matrix_Value_t>(data.begin(), data.end());
}

template <class T, T N, size_t D>
auto Matrix<T, N, D>::end()
{
	return Matrix_Iterator<typename std::unordered_map<Matrix_t, T, Matrix_Hash>::iterator, Matrix_Value_t>(data.end(), data.end());
}

}
