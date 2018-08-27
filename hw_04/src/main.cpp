/*! \file
    \brief Develop function to print conditional ip address.

    Address may be represented in random integer type.
	Represent of address do not depending from sign of type. Output is high-ordered byte sequence
    Outputting by byte, beginning from senior byte.
    As a delimiter use '.'

    Address may be represent in string. Output as is

	Address may be represented as container such a std::list, std::vector.
	Output all element of tuple and delim them

	Additional: Address may be represented as std::tuple on condition all type is same.
	Output all element of tuple and delim them
*/

#include "print.h"
#include "version_library.h"
using namespace HW_04::PRINT;

/*!
\brief Start program

\see print_ip()

\param[in] argc argument's count
\param[in] argv array of arguments
\return process code
*/
int main(int argc, char* argv[])
{
    if (argc > 1)
    {
    	if (std::string(argv[1]) == "-v")
			HW_01::version();
		else
		{
			std::cout << "Usage:" << std::endl;
			std::cout << "	print_ip without arguments to run" << std::endl;
			std::cout << "	print_ip -v Current version print" << std::endl;
			std::cout << std::endl;
		}

		return 0;
    }

	/// Output integer type
	/// \code
	print_ip(static_cast<uint8_t>(-1));
	print_ip(static_cast<int16_t>(0));
	print_ip(static_cast<int32_t>(2130706433));
	print_ip(static_cast<int64_t>(8875824491850138409));
	/// \endcode
	std::cout << std::endl;
	/// Output string
	/// \code
	try
	{
		print_ip(std::string("1.2.3.4"));
	}
	catch (std::bad_alloc)
	{
		std::cout << "error allocate memory in string" << std::endl;
	}
	/// \endcode

	std::cout << std::endl;
	/// Output container
	/// \code
	try
    {
		print_ip(std::vector<int32_t> {1, 2, 3, 4, 5, 6});
		print_ip(std::vector<std::list<int32_t>> {{-1, 0, 1, 2, 3, 4},{-5, 6, 7, 8, 9, 10}});
		print_ip(std::list<int64_t> {5, 10, 15, 20, 30});
		print_ip(std::vector<int8_t> {-1, 1, 127, -128, 64, -64});
		print_ip(std::list<int32_t> {256, 4096, 8192, 2048, 128});
		print_ip(std::list<std::string> {"1","2","3","12"});
	}
	catch (std::bad_alloc)
	{
		std::cout << "error allocate memory in container" << std::endl;
	}
	/// \endcode

	std::cout << std::endl;
	/// Output tuple
	/// \code
	try
    {
		print_ip(std::make_tuple(256, "4096", (int64_t)8192, 2048, "128", '5', -256, (int32_t)-1024, -4096, "-8192"));
	}
	catch (std::bad_alloc)
	{
		std::cout << "error allocate memory in container during copy from tuple" << std::endl;
	}
	/// \endcode

	return 0;
}
