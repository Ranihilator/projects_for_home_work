/*!
\file
\brief Develop application to sorting ip address

In input stream ip address, application outputing it's to lexicographic sorting
- IP address in backward order.
- IP address in backward order, where first byte equal 1
- IP address in backward order, where first byte equal 46 and second byte equal 70
- IP address in backward order, where any byte equal 46
*/

#include "filter.h"

using namespace HW_02::FILTER;

/*!
\brief Start program

\see print_ip()

\param[in] argc argument's count
\param[in] argv array of arguments
\return process code
*/
int main(int argc, char* argv[])
{
	/// Regex value to search ip address in input stream
	/// \code
	std::regex ip_filter (FILTER_REGEX);
	/// \endcode

	/// IP Address containers
	/// \code
	auto data = IP_Address_Sort();
	auto data_filter_task1 = IP_Address_Sort(1);
	auto data_filter_task2 = IP_Address_Sort(46, 70);
	auto data_filter_task3 = IP_Address_Sort_Any(46);
	/// \endcode

	/// Filling container
	/// \code
	for(std::string line; std::getline(std::cin, line);)
	{
		auto value = ip_address<uint8_t>();
		try
		{
			value = split_ip(line, ip_filter);
			data << value;
			data_filter_task1 << value;
			data_filter_task2 << value;
			data_filter_task3 << value;
		}
		catch (std::invalid_argument &e)
		{}
	}
	/// \endcode

	/// \code output result from containers
	std::cout << data.dump().str();
	std::cout << data_filter_task1.dump().str();
	std::cout << data_filter_task2.dump().str();
	std::cout << data_filter_task3.dump().str();
	/// \endcode

	return 0;


}
