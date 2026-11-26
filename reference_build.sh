#! /bin/bash

mkdir -p ./build

clang++ --std=c++23 --stdlib=libc++ \
  --precompile /usr/share/libc++/v1/std.cppm \
  -o ./DragonFly/public/std.pcm \
  -Wno-reserved-identifier -Wno-reserved-module-identifier

clang++ --std=c++23 --stdlib=libc++ \
  --precompile ./DragonFly/public/public_api.cppm \
  -DBUILD_SDK=1 -o ./DragonFly/public/public_api.pcm
clang++ --std=c++23 --stdlib=libc++ \
  -fmodule-file=public_api='./DragonFly/public/public_api.pcm' \
  -fmodule-file=std='./DragonFly/public/std.pcm' \
  -I ./DragonFly/public/ \
  ./DragonFly/private/private_imp.cpp -shared -fPIC -fvisibility=hidden \
  -DBUILD_SDK=1 -O0 -g -o ./build/libmodule.so

clang++ --std=c++23 --stdlib=libc++ \
  -fmodule-file=std='./DragonFly/public/std.pcm' \
  -fmodule-file=public_api='./DragonFly/public/public_api.pcm' \
  ./SandBox/main.cpp \
  -L./build -lmodule \
  -rpath '$ORIGIN' \
  -O0 -g -o ./build/main
