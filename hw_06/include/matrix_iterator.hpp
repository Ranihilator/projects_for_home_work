/*!
\file
\brief matrix iterator header

*/
#pragma once

namespace HW_06
{

template <class T, class M, class MV, class H>
class Matrix_Iterator
{
public:
	Matrix_Iterator(std::unordered_map<M, T, H> &_data, const T& _sparse_data);
	Matrix_Iterator& operator++();
	MV& operator=(const T& _data);
	MV& operator*();
	MV* operator->();
	bool operator!=(const Matrix_Iterator& other);
	bool operator==(const Matrix_Iterator& other);

private:
	typename std::unordered_map<M, T, H>::iterator pos;
	const T& sparse_data;
	MV itertor_value;

	std::unordered_map<M, T, H> &data;
};

template <class T, class M, class MV, class H>
Matrix_Iterator<T, M, MV, H>::Matrix_Iterator(std::unordered_map<M, T, H> &_data, const T& _sparse_data):
	data(_data), sparse_data(_sparse_data)
{
	this->pos = this->data.begin();
}

template <class T, class M, class MV, class H>
Matrix_Iterator<T, M, MV, H>& Matrix_Iterator<T, M, MV, H>::operator++()
{
	if  (this->pos == this->data.end())
		return *this;

	this->pos++;
	return *this;
}

template <class T, class M, class MV, class H>
MV& Matrix_Iterator<T, M, MV, H>::operator=(const T& _data)
{
	if (_data == this->sparse_data)
	{
		itertor_value = std::tuple_cat(std::get<0>(this->pos), _data);

		this->data.erase(this->pos++);

		return itertor_value;
	}

	std::get<1>(this->pos) = _data;

	itertor_value = std::tuple_cat(std::get<0>(this->pos), std::get<1>(this->pos));

	return itertor_value;
}

template <class T, class M, class MV, class H>
MV& Matrix_Iterator<T, M, MV, H>::operator*()
{
	itertor_value = std::tuple_cat(std::get<0>(this->pos), std::get<1>(this->pos));

	return itertor_value;
}

template <class T, class M, class MV, class H>
MV* Matrix_Iterator<T, M, MV, H>::operator->()
{
	itertor_value = std::tuple_cat(std::get<0>(this->pos), std::get<1>(this->pos));

	return &itertor_value;
}

template <class T, class M, class MV, class H>
bool Matrix_Iterator<T, M, MV, H>::operator!=(const Matrix_Iterator<T, M, MV, H>& other)
{
	return !(*this == other);
}

template <class T, class M, class MV, class H>
bool Matrix_Iterator<T, M, MV, H>::operator==(const Matrix_Iterator<T, M, MV, H>& other)
{
	return (this->pos == other.pos);
}

}
