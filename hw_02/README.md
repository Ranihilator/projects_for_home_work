#### ip_filter (Home work №2)
Application sort ip address

## Task
Application read data from stdin.
Data store by line.
Every line consist in 3 field, where each field's delimiter symbol \t and ending line \n.
text1 \t text2 \t text3 \n
field text2 and text3 is ignoring
field text1 have next struct (ip4 address): n1.n2.n3.n4 where n1..4 - is number from 0 to 255

It's need loading ip address list from memory and output in next order:
ip address list must be sorting in back lexicographic order. One line is one address.

Example of lexicographic sort order (by first number, two, three and etc.)
1.1.1.1
1.2.1.1
1.10.1.1
respectively backward sort:
1.10.1.1
1.2.1.1
1.1.1.1

At once continue list of address where first byte equal 1
Sort order not changing. One line is one address. The list is not dividing.

At once continue list of address where first byte equal 46 and second byte equal 70
Sort order not changing. One line is one address. The list is not dividing.

At once continue list of address where any byte equal 70.
Sort order not changing. One line is one address. The list is not dividing.

## Build, Test & Run
```shell
   cmake -H. -Bbuild -DCMAKE_BUILD_TYPE=Release
   cmake --build build --target ip_filter_testing
   cmake --build build --target package
   sh -c 'cd build && ctest -V'
   cat ./ip.tsv | build/ip_filter > out.tsv
   md5sum ./out.tsv
```
### Installation deb package
```shell
    echo "deb http://ppa.launchpad.net/ubuntu-toolchain-r/test/ubuntu trusty main" | sudo tee -a /etc/apt/sources.list
    echo "deb https://dl.bintray.com/ranihilator/projects_for_home_work trusty main" | sudo tee -a /etc/apt/sources.list
    sudo apt-get update && sudo apt-get install libstdc++6 home_work-ip_filter
```
