# hello_world (Home work №1)
it just hello world.

### Сборка, тест и выполнение
```shell
   cmake -H. -Bbuild
   cmake --build build
   cmake --build build --target helloworld_test
   cmake --build build --target package
   sh -c 'cd build && ctest -V'
   helloworld_cli
   helloworld_test
```

### Генерация документации
```shell
    doxygen
```

### Установка пакета deb
```shell
    echo "deb http://ppa.launchpad.net/ubuntu-toolchain-r/test/ubuntu trusty main" | sudo tee -a /etc/apt/sources.list
    echo "deb https://dl.bintray.com/ranihilator/projects_for_home_work trusty main" | sudo tee -a /etc/apt/sources.list
    sudo apt-get update && sudo apt-get install libstdc++6 home_work-helloworld
```
