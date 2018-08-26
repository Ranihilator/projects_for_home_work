/*!
\file
\brief matrix nodes header

*/
#pragma once

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
	bool operator()(D &dest, S &src)
	{
		if (src.empty())
			return false;

		std::get< index - 1 > (dest) = src.back();
		src.pop_back();

		return Set_Matrix_Coordinate < index - 1, D, S, size> ()(dest, src);
	}
};

template<class D, class S, size_t size>
struct Set_Matrix_Coordinate<0, D, S, size>
{
	bool operator()(D &dest, S &src)
	{
		return true;
	}
};

}
