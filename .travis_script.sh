#!/bin/bash

curl -T dist/ip_filter-1.0.$TRAVIS_BUILD_NUMBER-Linux.deb -u $BINTRAY_USER:$BINTRAY_API_KEY -H "X-Bintray-Debian-Distribution:trusty" -H "X-Bintray-Debian-Component:main" -H "X-Bintray-Debian-Architecture:amd64" https://api.bintray.com/content/$BINTRAY_USER/projects_for_home_work/ip_filter/1.0/pool/h/ip_filter/ip_filter-1.0.$TRAVIS_BUILD_NUMBER-Linux.deb;deb_distribution=trusty;deb_component=main;deb_architecture=amd64;publish=1

curl -X POST -u $BINTRAY_USER:$BINTRAY_API_KEY https://api.bintray.com/content/$BINTRAY_USER/projects_for_home_work/ip_filter/1.0/publish
