#include "main.h"
using namespace PRINT;

int main()
{
    std::tuple<int,int,int,int> a{1,2,3,4};

    print_ip(static_cast<char>(-1));
    print_ip(static_cast<short>(0));
    print_ip(static_cast<int>(2130706433));
    print_ip(static_cast<long>(8875824491850138409));

    print_ip(std::vector<char>{1,2,3,4});
    print_ip(std::list<short>{5,6,7,8});

    print_ip(std::string("1.2.3.4"));

    print_ip(std::make_tuple(1,2,3,4));

    return 0;
}
