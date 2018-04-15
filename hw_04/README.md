#### print_ip (Home work №4)
Application print ip address

## Task

Develop function to print conditional ip address.

Address may be represented in random integer type.
Represent of address do not depending from sign of type. Output is high-ordered byte sequence
Outputting by byte, beginning from senior byte.
As a delimiter use '.'

Address may be represent in string. Output as is

Address may be represented as container such a std::list, std::vector.
Output all element of tuple and delim them

Additional: Address may be represented as std::tuple on condition all type is same.
Output all element of tuple and delim them

### Build, Test & Run
```
cmake -H. -Bbuild -DCMAKE_BUILD_TYPE=Release
cmake --build build --target print_ip_test
cmake --build build --target package
sh -c 'cd build && ctest -V'
build/print_ip
```

### Installation deb package
```
echo "deb http://ppa.launchpad.net/ubuntu-toolchain-r/test/ubuntu trusty main" | sudo tee -a /etc/apt/sources.list
echo "deb https://dl.bintray.com/ranihilator/projects_for_home_work trusty main" | sudo tee -a /etc/apt/sources.list
sudo apt-get update && sudo apt-get install libstdc++6 home_work-print_ip
```
