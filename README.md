## Overview
Finite difference method for option pricing based on Implementing Derivative Models Les Clewlow, Chris Strickland.

## Builds

```
git clone https://github.com/i05nagai/FiniteDifferences.git
cd FiniteDifferences
git submodule init
git submnodule update
```

Build static lib `libfd.a`

```
mkdir build
cd build
cmake ..
make
```

Build `main.cpp` as an executable `fd_test`

```
mkdir build
cd build
cmake .. -DFD_BUILD_TEST=ON 
make
./fd_test
```
