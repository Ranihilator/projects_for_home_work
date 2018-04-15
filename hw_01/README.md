#### hello_world (Home work №1)
Application with library, print version and build number

## Build, Test & Run
```shell
   cmake -H. -Bbuild -DCMAKE_BUILD_TYPE=Release
   cmake --build build
   cmake --build build --target helloworld_test
   cmake --build build --target package
   sh -c 'cd build && ctest -V'
   helloworld_cli
   helloworld_test
```

### docs generate
```shell
    doxygen
```

### Installation deb package
```shell
    echo "deb http://ppa.launchpad.net/ubuntu-toolchain-r/test/ubuntu trusty main" | sudo tee -a /etc/apt/sources.list
    echo "deb https://dl.bintray.com/ranihilator/projects_for_home_work trusty main" | sudo tee -a /etc/apt/sources.list
    sudo apt-get update && sudo apt-get install libstdc++6 home_work-helloworld
```
