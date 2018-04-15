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
	print_ip(static_cast<char>(-1));
	print_ip(static_cast<short>(0));
	print_ip(static_cast<int>(2130706433));
	print_ip(static_cast<long>(8875824491850138409));
	/// \endcode

	std::cout << std::endl;
	/// Output string
	/// \code
	print_ip(std::string("abc 12.52.13.44 fsafsaf 127.0.0.1 efg"));
	/// \endcode

	std::cout << std::endl;
	/// Output container
	/// \code
	print_ip(std::vector<int> {-1, 2130706433, 127, -128, 64, -64});
	print_ip(std::list<long> {256, 8875824491850138409, 8192, 2048, 128});
	print_ip(std::vector<char> {-1, 1, 127, -128, 64, -64});
	print_ip(std::list<short> {256, 4096, 8192, 2048, 128});
	/// \endcode

	std::cout << std::endl;
	/// Output tuple
	/// \code
	print_ip(std::make_tuple(256, 4096, 8192, 2048, 128, -1, -256, -1024, -4096, -8192));
	/// \endcode

	return 0;
}
