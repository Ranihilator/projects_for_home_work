#!/bin/bash

ACTION="${1}"

if [[ ${ACTION} == 'build' ]]; then

    echo "Building..."

    mkdir -p dist
    cmake -H. -Bbuild
    cmake --build build
    cmake --build build --target
    cmake --build build --target package

    sh -c 'cd build/hw_01 && ctest -V'
    sh -c 'cd build/hw_02 && ctest -V'
    sh -c 'cd build/hw_03 && ctest -V'
    sh -c 'cd build/hw_04 && ctest -V'

    mv build/*.deb dist/

    doxygen

    cat hw_02/ip.tsv | build/hw_02/ip_filter > hw_02/out.tsv
    md5sum hw_02/out.tsv

    ltrace -e malloc -e free build/hw_03/allocator
    valgrind --leak-check=full build/hw_03/allocator

elif [[ ${ACTION} == 'deploy' ]]; then

    echo "Deploying..."

#    curl -T dist/home_work-1.0.$TRAVIS_BUILD_NUMBER-amd64-helloworld.deb -u $BINTRAY_USER:$BINTRAY_API_KEY -H "X-Bintray-Debian-Distribution:trusty" -H "X-Bintray-Debian-Component:main" -H "X-Bintray-Debian-Architecture:amd64" https://api.bintray.com/content/$BINTRAY_USER/projects_for_home_work/helloworld/1.0/pool/h/helloworld/helloworld-1.0.$TRAVIS_BUILD_NUMBER-Linux.deb;deb_distribution=trusty;deb_component=main;deb_architecture=amd64;publish=1
#    curl -X POST -u $BINTRAY_USER:$BINTRAY_API_KEY https://api.bintray.com/content/$BINTRAY_USER/projects_for_home_work/helloworld/1.0/publish

#    curl -T dist/home_work-1.0.$TRAVIS_BUILD_NUMBER-amd64-ip_filter.deb -u $BINTRAY_USER:$BINTRAY_API_KEY -H "X-Bintray-Debian-Distribution:trusty" -H "X-Bintray-Debian-Component:main" -H "X-Bintray-Debian-Architecture:amd64" https://api.bintray.com/content/$BINTRAY_USER/projects_for_home_work/ip_filter/1.0/pool/i/ip_filter/ip_filter-1.0.$TRAVIS_BUILD_NUMBER-Linux.deb;deb_distribution=trusty;deb_component=main;deb_architecture=amd64;publish=1
#    curl -X POST -u $BINTRAY_USER:$BINTRAY_API_KEY https://api.bintray.com/content/$BINTRAY_USER/projects_for_home_work/ip_filter/1.0/publish

#    curl -T dist/home_work-1.0.$TRAVIS_BUILD_NUMBER-amd64-allocator.deb -u $BINTRAY_USER:$BINTRAY_API_KEY -H "X-Bintray-Debian-Distribution:trusty" -H "X-Bintray-Debian-Component:main" -H "X-Bintray-Debian-Architecture:amd64" https://api.bintray.com/content/$BINTRAY_USER/projects_for_home_work/allocator/1.0/pool/a/allocator/allocator-1.0.$TRAVIS_BUILD_NUMBER-Linux.deb;deb_distribution=trusty;deb_component=main;deb_architecture=amd64;publish=1

#    curl -X POST -u $BINTRAY_USER:$BINTRAY_API_KEY https://api.bintray.com/content/$BINTRAY_USER/projects_for_home_work/allocator/1.0/publish

    curl -T dist/home_work-1.0.$TRAVIS_BUILD_NUMBER-amd64-helloworld.deb -u $BINTRAY_USER:$BINTRAY_API_KEY "https://api.bintray.com/content/$BINTRAY_USER/projects_for_home_work/helloworld/1.0/pool/h/helloworld-1.0.$TRAVIS_BUILD_NUMBER-Linux.deb;deb_distribution=trusty;deb_component=main;deb_architecture=amd64;publish=1"

    curl -T dist/home_work-1.0.$TRAVIS_BUILD_NUMBER-amd64-ip_filter.deb -u $BINTRAY_USER:$BINTRAY_API_KEY "https://api.bintray.com/content/$BINTRAY_USER/projects_for_home_work/ip_filter/1.0/pool/i/ip_filter-1.0.$TRAVIS_BUILD_NUMBER-Linux.deb;deb_distribution=trusty;deb_component=main;deb_architecture=amd64;publish=1"

    curl -T dist/home_work-1.0.$TRAVIS_BUILD_NUMBER-amd64-allocator.deb -u $BINTRAY_USER:$BINTRAY_API_KEY "https://api.bintray.com/content/$BINTRAY_USER/projects_for_home_work/allocator/1.0/pool/a/allocator-1.0.$TRAVIS_BUILD_NUMBER-Linux.deb;deb_distribution=trusty;deb_component=main;deb_architecture=amd64;publish=1"

    curl -T dist/home_work-1.0.$TRAVIS_BUILD_NUMBER-amd64-print_ip.deb -u $BINTRAY_USER:$BINTRAY_API_KEY "https://api.bintray.com/content/$BINTRAY_USER/projects_for_home_work/print_ip/1.0/pool/p/print_ip-1.0.$TRAVIS_BUILD_NUMBER-Linux.deb;deb_distribution=trusty;deb_component=main;deb_architecture=amd64;publish=1"


fi
