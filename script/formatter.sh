#!/bin/bash

path_to_repository=$(cd $(dirname ${0});cd ..;pwd)

filelist=$(find ${path_to_repository}/fd -name '*.cc' -or -name '*.h')
for filename in ${filelist}; do
  echo "format ${filename}"
  clang-format -i ${filename}
done
