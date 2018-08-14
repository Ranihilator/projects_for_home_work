#### simple_uml (Home work №5)
Create UML diagram from simple vector graph editor

## Task

Simple UML design functional:
Create new documents
Import documents from file
Export documents to file
Create simple graph elements
Delete simple graph elements

### Build, Test & Run
```
cmake -H. -Bbuild -DCMAKE_BUILD_TYPE=Release
cmake --build build --target package
build/simple_uml
```

### Installation deb package
```
echo "deb http://ppa.launchpad.net/ubuntu-toolchain-r/test/ubuntu trusty main" | sudo tee -a /etc/apt/sources.list
echo "deb https://dl.bintray.com/ranihilator/projects_for_home_work trusty main" | sudo tee -a /etc/apt/sources.list
sudo apt-get update && sudo apt-get install libstdc++6 home_work-simple_uml
```
