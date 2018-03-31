# allocator (Home work №3)

### Задание
Реализовать свой аллокатор памяти, который позволит выполнять
операцию reserve для контейнера std::map. Аллокатор должен параметризоваться
количеством выделяемых за раз элементов. Освобождение конкретного
элемента не предполагается - аллокатор должен освобождать всю память
самостоятельно. 

Реализовать свой контейнер, который по аналогии с контейнерами stl
параметризуется аллокатором. Контейнер должен иметь две возможности,
добавить новый элемент и обойти контейнер в одном направлении.


### Сборка, тест и выполнение
```shell
   cmake -H. -Bbuild
   cd build
   cmake --build . --target allocator_test
   cmake --build . --target package
   ctest -V
   ltrace -e malloc -e free ./allocator
   valgrind --leak-check=full ./allocator
```
### Установка пакета deb
```shell
    echo "deb http://ppa.launchpad.net/ubuntu-toolchain-r/test/ubuntu trusty main" | sudo tee -a /etc/apt/sources.list
    echo "deb https://dl.bintray.com/ranihilator/projects_for_home_work trusty main" | sudo tee -a /etc/apt/sources.list
    sudo apt-get update && sudo apt-get install libstdc++6 allocator
```
