#!/bin/bash -x

set -x

build_dir=$1
if [[ -z ${build_dir} ]]; then
  build_dir="build"
fi

#make dir if not exists
if [[ ! -d ${build_dir} ]]; then
  mkdir ${build_dir}
fi

ret=$?
if [ $ret -ne 0 ]; then
    exit $ret
fi

#cd build
cd ${build_dir}
ret=$?
if [ $ret -ne 0 ]; then
    exit $ret
fi

#cmake
cmake ..  -DCMAKE_BUILD_TYPE=${BUILD_TYPE} $FD_BUILD_TEST 
ret=$?
if [ $ret -ne 0 ]; then
    exit $ret
fi

#make
make
ret=$?
if [ $ret -ne 0 ]; then
    exit $ret
fi

#make test
ctest --verbose
ret=$?
if [ $ret -ne 0 ]; then
    exit $ret
fi

exit 0
