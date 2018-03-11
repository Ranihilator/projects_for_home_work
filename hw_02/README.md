# ip_filter
This repository for home work project's

run cmake,compile,and run application
```shell
   cmake -H. -Bbuild
   cd build
   cmake --build . --target ip_filter_testing
   cmake --build . --target package
   ctest -V
   cat ip.tsv | ip_filter > out.tsv
```
