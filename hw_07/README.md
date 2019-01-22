#### bulk (Home work №7)
Create application with package command processing

## Task

Command read from stdin line by line
Command processing by blocks
Application must logging to file

### Build, Test & Run
```
cmake -H. -Bbuild -DCMAKE_BUILD_TYPE=Release
cmake --build build --target package
build/bulk
```

### Installation deb package
```
echo "deb http://ppa.launchpad.net/ubuntu-toolchain-r/test/ubuntu trusty main" | sudo tee -a /etc/apt/sources.list
echo "deb https://dl.bintray.com/ranihilator/projects_for_home_work trusty main" | sudo tee -a /etc/apt/sources.list
sudo apt-get update && sudo apt-get install libstdc++6 home_work-bulk
```
