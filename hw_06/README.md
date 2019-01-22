#### matrix (Home work №6)
Create 2x - dimension sparse matrix

## Task

Create 2x matrix
Matrix have sparse elements
Matrix can return size
Matrix can iterrate all node
Matrix can return default value from sparse space

### Build, Test & Run
```
cmake -H. -Bbuild -DCMAKE_BUILD_TYPE=Release
cmake --build build --target matrix_test
cmake --build build --target package
build/matrix
```

### Installation deb package
```
echo "deb http://ppa.launchpad.net/ubuntu-toolchain-r/test/ubuntu trusty main" | sudo tee -a /etc/apt/sources.list
echo "deb https://dl.bintray.com/ranihilator/projects_for_home_work trusty main" | sudo tee -a /etc/apt/sources.list
sudo apt-get update && sudo apt-get install libstdc++6 home_work-matrix
```
