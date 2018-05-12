#!/bin/bash

set -x

if [ "$TRAVIS_OS_NAME" == "linux" ]; then
  script/ci/travis_cmake_setup.sh
fi

# /usr/bin/gcc is 4.6 always, but gcc-X.Y is available
if [ "$TRAVIS_OS_NAME" == "linux" -a "$CXX" == "g++" ]; then
    export CXX="g++-4.8" CC="gcc-4.8";
fi

if [ "${BUILD_TYPE}" == "Coverage" -a "${TRAVIS_OS_NAME}" == "linux" ]; then
    PATH=~/.local/bin:${PATH};
    pip install --user --upgrade pip;
    pip install --user cpp-coveralls;
fi

# /usr/bin/clang is 3.4, lets override with modern one.
#- if [ "$CXX" = "clang++" ] && [ "$TRAVIS_OS_NAME" = "linux" ]; then export CXX="clang++-3.7" CC="clang-3.7"; fi
echo ${PATH}
echo ${CXX}
${CXX} --version
${CXX} -v
cmake --version
