# projects_for_home_work
[![Build Status](https://travis-ci.org/Ranihilator/projects_for_home_work.svg?branch=master)](https://travis-ci.org/Ranihilator/projects_for_home_work)

Репозиторий для домашних работ

### Установка всех пакетов deb 

```shell
    echo "deb http://ppa.launchpad.net/ubuntu-toolchain-r/test/ubuntu trusty main" | sudo tee -a /etc/apt/sources.list
    echo "deb https://dl.bintray.com/ranihilator/projects_for_home_work trusty main" | sudo tee -a /etc/apt/sources.list
    sudo apt-get update && sudo apt-get install libstdc++6 helloworld ip_filter allocator
```
