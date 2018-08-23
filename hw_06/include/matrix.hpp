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

/*!
\brief Matrix class
\details N dimension sequency chain matrix
\tparam T Type of data elements in matrix
\tparam N Replace digit (sparse number) in matrix
*/
template <class T, T N>
class Matrix
{
friend Matrix_Iterator<Matrix, T>;

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
	operator const T() const;

	/*!
	\brief write new value in matrix node
	\param[in] _data input
	\return return reference value in matrix node
	*/
	T& operator=(const T& _data);

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

	/*!
	\brief clear matrix
	*/
	void clear();

	/*!
	\brief get actual stored elements in matrix
	*/
	size_t size() const;

private:
	Matrix_Space<Matrix> sequences;					/// sequences chain matrix nodes
	unique_ptr<T> data;								/// value in matrix node
};

template <class T, T N>
Matrix<T, N>& Matrix<T, N>::operator[](size_t index)
{
	Matrix* ptr = nullptr;

	try
	{
		auto coordinate = this->sequences.find(index);

		if (coordinate == this->sequences.end())
			this->sequences[index] = unique_ptr<Matrix>(new Matrix);

		ptr = this->sequences[index].get();

		if (ptr == nullptr)
			return *this;
	}
	catch (...)
	{
		return *this;
	}

	return *ptr;
}

template <class T, T N>
T& Matrix<T, N>::operator=(const T& _data)
{
	this->data.reset(new T(_data));
}

template <class T, T N>
Matrix<T, N>::operator const T() const
{
	T* ptr = this->data.get();

	if (ptr == nullptr)
		return N;

	return *ptr;
}

template <class T, T N>
size_t Matrix<T, N>::size() const
{
	size_t _size = 0;
	for (const auto &i : this->sequences)
	{
		Matrix* ptr = std::get<1>(i).get();
		if (ptr == nullptr)
			continue;

		if (ptr->sequences.size() == 0 && ptr->data.get() != nullptr)
		{
			if (*ptr->data.get() != N)
			_size++;
		}

		if (ptr->sequences.size() != 0 && ptr->data.get() == nullptr)
			_size += ptr->size();
	}

	return _size;
}

template <class T, T N>
void Matrix<T, N>::clear()
{
	this->sequences.clear();
	this->data.reset(nullptr);
}

template <class T, T N>
auto Matrix<T, N>::begin()
{
	return Matrix_Iterator<Matrix, T>(&(this->sequences), N);
}

template <class T, T N>
auto Matrix<T, N>::end()
{
	return Matrix_Iterator<Matrix, T>(nullptr, N);
}

}
