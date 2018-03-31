#!/bin/bash
ACTION="${1}"
if [[ ${ACTION} == 'build' ]]; then
echo "Building..."

mkdir dist hw_01/build hw_02/build hw_03/build

echo "Building hw_01"
cmake -Hhw_01 -Bhw_01/build
cmake --build hw_01/build
cmake --build hw_01/build --target helloworld_test
cmake --build hw_01/build --target package
sh -c 'cd hw_01/build && ctest -V'
mv hw_01/build/*.deb dist/

echo "Building hw_02"
cmake -Hhw_02 -Bhw_02/build
cmake --build hw_02/build
cmake --build hw_02/build --target ip_filter_testing
cmake --build hw_02/build --target package
sh -c 'cd hw_02/build && ctest -V'
mv hw_02/build/*.deb dist/
cat hw_02/ip.tsv | hw_02/build/ip_filter > hw_02/out.tsv
md5sum hw_02/out.tsv

echo "Building hw_03"
cmake -Hhw_03 -Bhw_03/build
cmake --build hw_03/build
cmake --build hw_03/build --target allocator_testing
cmake --build hw_03/build --target package
sh -c 'cd hw_03/build && ctest -V'
mv hw_03/build/*.deb dist/
ltrace -e malloc -e free hw_03/build/allocator
valgrind --leak-check=full hw_03/build/allocator

elif if [[ ${ACTION} == 'deploy' ]]; then
    echo "Deploying..."
    curl -T dist/helloworld-1.0.$TRAVIS_BUILD_NUMBER-Linux.deb -u $BINTRAY_USER:$BINTRAY_API_KEY -H "X-Bintray-Debian-Distribution:trusty" -H "X-Bintray-Debian-Component:main" -H "X-Bintray-Debian-Architecture:amd64" https://api.bintray.com/content/$BINTRAY_USER/projects_for_home_work/helloworld/$TRAVIS_BUILD_NUMBER/pool/h/helloworld/helloworld-1.0.$TRAVIS_BUILD_NUMBER-Linux.deb;deb_distribution=trusty;deb_component=main;deb_architecture=amd64;publish=1
    curl -X POST -u $BINTRAY_USER:$BINTRAY_API_KEY https://api.bintray.com/content/$BINTRAY_USER/projects_for_home_work/helloworld/$TRAVIS_BUILD_NUMBER/publish

    curl -T dist/ip_filter-1.0.$TRAVIS_BUILD_NUMBER-Linux.deb -u $BINTRAY_USER:$BINTRAY_API_KEY -H "X-Bintray-Debian-Distribution:trusty" -H "X-Bintray-Debian-Component:main" -H "X-Bintray-Debian-Architecture:amd64" https://api.bintray.com/content/$BINTRAY_USER/projects_for_home_work/ip_filter/1.0/pool/i/ip_filter/ip_filter-1.0.$TRAVIS_BUILD_NUMBER-Linux.deb;deb_distribution=trusty;deb_component=main;deb_architecture=amd64;publish=1
    curl -X POST -u $BINTRAY_USER:$BINTRAY_API_KEY https://api.bintray.com/content/$BINTRAY_USER/projects_for_home_work/ip_filter/1.0/publish

    curl -T dist/allocator-1.0.$TRAVIS_BUILD_NUMBER-Linux.deb -u $BINTRAY_USER:$BINTRAY_API_KEY -H "X-Bintray-Debian-Distribution:trusty" -H "X-Bintray-Debian-Component:main" -H "X-Bintray-Debian-Architecture:amd64" https://api.bintray.com/content/$BINTRAY_USER/projects_for_home_work/allocator/1.0/pool/a/allocator/allocator-1.0.$TRAVIS_BUILD_NUMBER-Linux.deb;deb_distribution=trusty;deb_component=main;deb_architecture=amd64;publish=1

    curl -X POST -u $BINTRAY_USER:$BINTRAY_API_KEY https://api.bintray.com/content/$BINTRAY_USER/projects_for_home_work/allocator/1.0/publish

fi
