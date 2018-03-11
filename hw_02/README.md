# ip_filter

[![Build Status](https://travis-ci.org/Ranihilator/projects_for_home_work.svg?branch=master)](https://travis-ci.org/Ranihilator/projects_for_home_work)

### Задание №1
Программа из стандартного ввода читает данные. 
Данные хранятся построчно.
Каждая строка состоит из трех полей разделенных одним символом табуляции и завершается символом конца строки.
text1 \t text2 \t text3 \n
Поля text2 и text3 игнорируются. 
поле text1 имеет следующую структуру (ip4 address): n1.n2.n3.n4 где n1..4 - число от 0 до 255

Необходимо загрузить список ip-адресов в память и вывести в следующем порядке:
Список адресов отсортированных в обратном лексикографическом порядке адресов. Одна строка один адрес.

Пример лексикографической сортировки (по первому числу, затем по второму и так далее):
1.1.1.1
1.2.1.1
1.10.1.1
Соответственно обратная:
1.10.1.1
1.2.1.1
1.1.1.1

Сразу продолжается список адресов первый байт которых равен 1. 
Порядок сортировки не меняется. Одна строка один адрес. Списки ничем не разделяются. 

Сразу продолжается список адресов первый байт которых равен 46, а второй 70. 
Порядок сортировки не меняется. Одна строка один адрес. Списки ничем не разделяются. 

Сразу продолжается список адресов любой байт которых равен 46. Порядок сортировк

### Задание №2
http://acm.timus.ru/author.aspx?id=246783


### Сборка, тест и выполнение
```shell
   cmake -H. -Bbuild
   cd build
   cmake --build . --target ip_filter_testing
   cmake --build . --target package
   ctest -V
   cat ../ip.tsv | ip_filter > out.tsv
   md5sum out.tsv
```
### Установка пакета deb
```shell
    echo "deb http://ppa.launchpad.net/ubuntu-toolchain-r/test/ubuntu trusty main" | sudo tee -a /etc/apt/sources.list
    echo "deb https://dl.bintray.com/ranihilator/projects_for_home_work trusty main" | sudo tee -a /etc/apt/sources.list
    sudo apt-get update && sudo apt-get install libstdc++6 ip_filter
```
