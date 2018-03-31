# hello_world
it just hello world.

run cmake,compile,and run application
```shell
   cmake -H. -Bbuild
   cd build
   cmake --build .
   ctest -V
   helloworld_cli
   helloworld_test
```

generated doxygen documentation to doc folder
```shell
    doxygen
```

### Установка пакета deb
```shell
    echo "deb http://ppa.launchpad.net/ubuntu-toolchain-r/test/ubuntu trusty main" | sudo tee -a /etc/apt/sources.list
    echo "deb https://dl.bintray.com/ranihilator/projects_for_home_work trusty main" | sudo tee -a /etc/apt/sources.list
    sudo apt-get update && sudo apt-get install libstdc++6 helloworld
```
