#pragma once

#include <map>
#include <type_traits>

namespace HW_06
{

template <class T, T DV=T()>
class Matrix
{
static_assert(std::is_integral<T>::value, "type must be is integral");
public:
	Matrix();

	size_t size() const;

	Matrix& operator [](T idx);
};

}
