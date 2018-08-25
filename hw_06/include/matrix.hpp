/*!
\file
\brief matrix header

*/
#pragma once

#include "matrix_iterator.hpp"

/*!
\brief HW_06 namespace
\details Matrix task
*/
namespace HW_06
{


template<size_t N, class... REST>
struct Matrix_Coordinate
{
	using type = typename Matrix_Coordinate<N-1, size_t, REST...>::type;
};

template<class... REST>
struct Matrix_Coordinate<0, REST...>
{
	using type = std::tuple<REST...>;
};

template<size_t index, class T, size_t size = index>
struct Get_Matrix_Coordinate
{
	void operator()(const T &arg, std::stringstream &buffer) const
	{
		Get_Matrix_Coordinate < index - 1, T, size> ()(arg, buffer);
		buffer << std::get < index - 1 > (arg);

		if (index < size)
			buffer << ":";
	}
};

template<class T, size_t size>
struct Get_Matrix_Coordinate<0, T, size>
{
	void operator()(const T &arg, std::stringstream &buffer) const
	{}
};

template<size_t index, class D, class S, size_t size = index>
struct Set_Matrix_Coordinate
{
	void operator()(D &dest, S &src)
	{
		std::get< index - 1 > (dest) = src[index - 1];
		Set_Matrix_Coordinate < index - 1, D, S, size> ()(dest, src);
	}
};

template<class D, class S, size_t size>
struct Set_Matrix_Coordinate<0, D, S, size>
{
	void operator()(D &dest, S &src)
	{}
};


template <class T, T N=T(), size_t D = 2>
class Matrix
{
using Matrix_t = typename Matrix_Coordinate<D>::type;

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

	/*!
	\brief get access to matrix node
	\param[in] index matrix node index
	\return return matrix node
	*/
	Matrix& operator[](size_t index);

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
	const T sparse_data = N;
	std::vector<size_t> coordinate;
	std::unordered_map<Matrix_t, T, Matrix_Hash> data;
};

template <class T, T N, size_t D>
Matrix<T, N, D>& Matrix<T, N, D>::operator[](size_t index)
{
	this->coordinate.emplace_back(index);
	return *this;
}

template <class T, T N, size_t D>
Matrix<T, N, D>::operator const T()
{
	Matrix_t dest;
	std::vector<size_t> src(std::move(this->coordinate));
	Set_Matrix_Coordinate<std::tuple_size<Matrix_t>::value, Matrix_t, std::vector<size_t>>()(dest, src);

	auto iter = this->data.find(dest);

	if (iter == this->data.end())
		return N;

	return iter->second;
}

template <class T, T N, size_t D>
const T& Matrix<T, N, D>::operator=(const T& _data)
{
	Matrix_t dest;
	std::vector<size_t> src(std::move(this->coordinate));
	Set_Matrix_Coordinate<std::tuple_size<Matrix_t>::value, Matrix_t, std::vector<size_t>>()(dest, src);

	if (_data == N)
		return this->sparse_data;

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
}

template <class T, T N, size_t D>
auto Matrix<T, N, D>::end()
{
}

}
