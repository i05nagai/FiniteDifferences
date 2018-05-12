#!/usr/bin/env bash

set -x

# Install a newer CMake version
curl -sSL https://cmake.org/files/v3.6/cmake-3.6.1-Linux-x86_64.sh -o install-cmake.sh
chmod +x install-cmake.sh
./install-cmake.sh --prefix=~/.local --skip-license
export PATH=~/.local/bin:${PATH};
