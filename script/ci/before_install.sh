#!/bin/bash

set -x

echo $LANG
echo $LC_ALL
ls -la

if [ "$TRAVIS_OS_NAME" == "osx" -a "$CXX" == "g++" ]; then
  gcc --version
  g++ --version
  brew update
  brew install gcc@5 || brew link --overwrite gcc@5
  gcc --version
  g++ --version
  export CXX="g++"
fi

# valgrind does not work in osx so we only test with valgrind on linux
if [ "$TRAVIS_OS_NAME" == "linux" ]; then
  export BASEPATH=`pwd`
  mkdir ${BASEPATH}/usr 
  export PATH="${BASEPATH}/usr/bin:$PATH" 
  export LD_LIBRARY_PATH="${BASEPATH}/usr/lib:$LD_LIBRARY_PATH"
  wget http://valgrind.org/downloads/valgrind-3.12.0.tar.bz2 
  tar xjf valgrind-3.12.0.tar.bz2 
  cd valgrind-3.12.0 
  ./configure --prefix=${BASEPATH}/usr > /dev/null 
  make -j3 > /dev/null 
  make install > /dev/null 
  cd .. 
  valgrind --version
fi
