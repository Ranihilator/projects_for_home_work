#!/bin/bash

ACTION="${1}"

if [[ ${ACTION} == 'build' ]]; then

    echo "Building..."

    doxygen -u
    doxygen
    
    mkdir -p dist doc build
    cmake -H. -Bbuild
    cmake --build build
    cmake --build build --target
    cmake --build build --target package

    sh -c 'cd build/hw_01 && ctest -V'
    sh -c 'cd build/hw_02 && ctest -V'
    sh -c 'cd build/hw_03 && ctest -V'
    sh -c 'cd build/hw_04 && ctest -V'
    sh -c 'cd build/hw_06 && ctest -V'

    mv build/*.deb dist/

    cat hw_02/ip.tsv | build/hw_02/ip_filter > hw_02/out.tsv
    md5sum hw_02/out.tsv

    ltrace -e malloc -e free build/hw_03/allocator
    valgrind --leak-check=full build/hw_03/allocator

    build/hw_04/print_ip
    build/hw_06/matrix

elif [[ ${ACTION} == 'deploy' ]]; then

    echo "Deploying..."

    curl -T dist/home_work-1.0.$TRAVIS_BUILD_NUMBER-amd64-helloworld.deb -u $BINTRAY_USER:$BINTRAY_API_KEY "https://api.bintray.com/content/$BINTRAY_USER/projects_for_home_work/helloworld/1.0/pool/h/helloworld-1.0.$TRAVIS_BUILD_NUMBER-Linux.deb;deb_distribution=trusty;deb_component=main;deb_architecture=amd64;publish=1"

    curl -T dist/home_work-1.0.$TRAVIS_BUILD_NUMBER-amd64-ip_filter.deb  -u $BINTRAY_USER:$BINTRAY_API_KEY "https://api.bintray.com/content/$BINTRAY_USER/projects_for_home_work/ip_filter/1.0/pool/i/ip_filter-1.0.$TRAVIS_BUILD_NUMBER-Linux.deb;deb_distribution=trusty;deb_component=main;deb_architecture=amd64;publish=1"

    curl -T dist/home_work-1.0.$TRAVIS_BUILD_NUMBER-amd64-allocator.deb  -u $BINTRAY_USER:$BINTRAY_API_KEY "https://api.bintray.com/content/$BINTRAY_USER/projects_for_home_work/allocator/1.0/pool/a/allocator-1.0.$TRAVIS_BUILD_NUMBER-Linux.deb;deb_distribution=trusty;deb_component=main;deb_architecture=amd64;publish=1"

    curl -T dist/home_work-1.0.$TRAVIS_BUILD_NUMBER-amd64-print_ip.deb   -u $BINTRAY_USER:$BINTRAY_API_KEY "https://api.bintray.com/content/$BINTRAY_USER/projects_for_home_work/print_ip/1.0/pool/p/print_ip-1.0.$TRAVIS_BUILD_NUMBER-Linux.deb;deb_distribution=trusty;deb_component=main;deb_architecture=amd64;publish=1"

    curl -T dist/home_work-1.0.$TRAVIS_BUILD_NUMBER-amd64-matrix.deb   -u $BINTRAY_USER:$BINTRAY_API_KEY "https://api.bintray.com/content/$BINTRAY_USER/projects_for_home_work/matrix/1.0/pool/p/matrix-1.0.$TRAVIS_BUILD_NUMBER-Linux.deb;deb_distribution=trusty;deb_component=main;deb_architecture=amd64;publish=1"

fi
