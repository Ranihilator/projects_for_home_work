#!/bin/bash

build()
{
    echo "Building $1"
    mkdir -p $1/build
    cmake -H$1 -B$1/build
    cmake --build $1/build
    cmake --build $1/build --target $2
    cmake --build $1/build --target package
    sh -c 'cd $1/build && ctest -V'
    mv $1/build/*.deb dist/
}

ACTION="${1}"

if [[ ${ACTION} == 'build' ]]; then

    echo "Building..."
    mkdir -p dist

    build hw_01 helloworld_test
    
    build hw_02 ip_filter_testing
    cat hw_02/ip.tsv | hw_02/build/ip_filter > hw_02/out.tsv
    md5sum hw_02/out.tsv

    build hw_03 allocator_testing
    ltrace -e malloc -e free hw_03/build/allocator
    valgrind --leak-check=full hw_03/build/allocator

elif [[ ${ACTION} == 'deploy' ]]; then

    echo "Deploying..."

    curl -T dist/helloworld-1.0.$TRAVIS_BUILD_NUMBER-Linux.deb -u $BINTRAY_USER:$BINTRAY_API_KEY -H "X-Bintray-Debian-Distribution:trusty" -H "X-Bintray-Debian-Component:main" -H "X-Bintray-Debian-Architecture:amd64" https://api.bintray.com/content/$BINTRAY_USER/projects_for_home_work/helloworld/$TRAVIS_BUILD_NUMBER/pool/h/helloworld/helloworld-1.0.$TRAVIS_BUILD_NUMBER-Linux.deb;deb_distribution=trusty;deb_component=main;deb_architecture=amd64;publish=1
    curl -X POST -u $BINTRAY_USER:$BINTRAY_API_KEY https://api.bintray.com/content/$BINTRAY_USER/projects_for_home_work/helloworld/$TRAVIS_BUILD_NUMBER/publish

    curl -T dist/ip_filter-1.0.$TRAVIS_BUILD_NUMBER-Linux.deb -u $BINTRAY_USER:$BINTRAY_API_KEY -H "X-Bintray-Debian-Distribution:trusty" -H "X-Bintray-Debian-Component:main" -H "X-Bintray-Debian-Architecture:amd64" https://api.bintray.com/content/$BINTRAY_USER/projects_for_home_work/ip_filter/1.0/pool/i/ip_filter/ip_filter-1.0.$TRAVIS_BUILD_NUMBER-Linux.deb;deb_distribution=trusty;deb_component=main;deb_architecture=amd64;publish=1
    curl -X POST -u $BINTRAY_USER:$BINTRAY_API_KEY https://api.bintray.com/content/$BINTRAY_USER/projects_for_home_work/ip_filter/1.0/publish

    curl -T dist/allocator-1.0.$TRAVIS_BUILD_NUMBER-Linux.deb -u $BINTRAY_USER:$BINTRAY_API_KEY -H "X-Bintray-Debian-Distribution:trusty" -H "X-Bintray-Debian-Component:main" -H "X-Bintray-Debian-Architecture:amd64" https://api.bintray.com/content/$BINTRAY_USER/projects_for_home_work/allocator/1.0/pool/a/allocator/allocator-1.0.$TRAVIS_BUILD_NUMBER-Linux.deb;deb_distribution=trusty;deb_component=main;deb_architecture=amd64;publish=1

    curl -X POST -u $BINTRAY_USER:$BINTRAY_API_KEY https://api.bintray.com/content/$BINTRAY_USER/projects_for_home_work/allocator/1.0/publish

fi
