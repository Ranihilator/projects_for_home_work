/*!
\file
\brief matrix iterator header

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

namespace HW_06
{

#if 0

using std::unordered_map;
using std::unique_ptr;
using std::vector;

template <class T, class D>
struct Matrix_Iterator;

template <class T, T N = T()>
class Matrix;

/*!
\brief Main type of matrix environment
\tparam T Type of data elements in matrix
*/
template <class T>
using Matrix_Space = unordered_map<size_t, unique_ptr<T>>;

/*!
\brief Matrix Iterator class
\details Iterator can iterate all live elements in matrix
\tparam M Matrix passed type
\tparam T Type of data elements in matrix
*/
template <class M, class T>
class Matrix_Iterator
{
public:
	Matrix_Iterator(Matrix_Space<M>* sequences_ptr, T sparse_number);

	Matrix_Iterator& operator++();
	M& operator=(const T& _data);
	M& operator*();
	M* operator->();
	bool operator!=(const Matrix_Iterator& other);
	bool operator==(const Matrix_Iterator& other);

private:
	static std::vector<M*> list;
	typename std::vector<M*>::iterator pos;
};

template <class M, class T>
std::vector<M*> Matrix_Iterator<M, T>::list;

template <class M, class T>
Matrix_Iterator<M, T>::Matrix_Iterator(Matrix_Space<M>* sequences_ptr, T sparse_number)
{
	if (sequences_ptr == nullptr)
	{
		this->pos = this->list.end();
		return;
	}

	std::function<void(Matrix_Space<M>&)> iterate = [&](Matrix_Space<M>& sequences)
	{
		for (const auto &i : sequences)
		{
			auto* ptr = std::get<1>(i).get();
			if (ptr == nullptr)
				continue;

			if (ptr->sequences.size() == 0 && ptr->data.get() != nullptr)
			{
				if (*ptr->data.get() != sparse_number)
				this->list.emplace_back(ptr);
			}

			if (ptr->sequences.size() != 0 && ptr->data.get() == nullptr)
				iterate(ptr->sequences);
		}
	};

	iterate(*sequences_ptr);
	this->pos = this->list.begin();
};

template <class M, class T>
bool Matrix_Iterator<M, T>::operator!=(const Matrix_Iterator<M, T>& other)
{
	return !(*this == other);
}

template <class M, class T>
bool Matrix_Iterator<M, T>::operator==(const Matrix_Iterator<M, T>& other)
{
	return (this->pos == other.pos);
}

template <class M, class T>
M* Matrix_Iterator<M, T>::operator->()
{
	if  (this->pos == this->end)
		return nullptr;

	return *this->pos;
}

template <class M, class T>
M& Matrix_Iterator<M, T>::operator*()
{
	return **this->pos;
}

template <class M, class T>
M& Matrix_Iterator<M, T>::operator=(const T& _data)
{
	*this->pos = _data;

	return **this->pos;
}

template <class M, class T>
Matrix_Iterator<M, T>& Matrix_Iterator<M, T>::operator++()
{
	if  (this->pos == this->list.end())
		return *this;

	this->pos++;
	return *this;
}
#endif
}
