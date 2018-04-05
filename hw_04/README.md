# print_ip (Home work №4)

### Задание
Реализовать функцию печати условного ip-адреса.
Адрес может быть представлен в виде произвольного целочисленного типа.
Представление не зависит от знака типа. Выводить побайтово начиная со
старшего с символом . в качестве разделителя.
Адрес может быть представлен в виде строки. Выводится как есть.
Адрес может быть представлен в виде контейнеров std::list, std::vector.
Выводится содержимое контейнера поэлементно и разделяется


### Сборка, тест и выполнение
```shell
   cmake -H. -Bbuild
   cmake --build build --target print_ip_test
   cmake --build build --target package
   sh -c 'cd build && ctest -V'
   build/print_ip
```
### Установка пакета deb
```shell
    echo "deb http://ppa.launchpad.net/ubuntu-toolchain-r/test/ubuntu trusty main" | sudo tee -a /etc/apt/sources.list
    echo "deb https://dl.bintray.com/ranihilator/projects_for_home_work trusty main" | sudo tee -a /etc/apt/sources.list
    sudo apt-get update && sudo apt-get install libstdc++6 home_work-print_ip
```
