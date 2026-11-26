cmake_minimum_required(VERSION 4.4.5)

set(CMAKE_C_COMPILER clang CACHE FILEPATH "C compiler")
set(CMAKE_CXX_COMPILER clang++ CACHE FILEPATH "C++ compiler")
set(CMAKE_LINKER_TYPE LLD CACHE STRING "Object linker")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE BOOL "Compiler
commands")

# One day these will be removed!
set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "f35a9ac6-8463-4d38-8eec-5d6008153e7d")
set(CMAKE_CXX_MODULE_STD ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")

set(DRAGONFLY_NAME "DragonFly" CACHE STRING "Name of this project" FORCE)
project(${DRAGONFLY_NAME} LANGUAGES C CXX)

if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  set(DRAGONFLY_TOP_LEVEL ON CACHE BOOL "If this project is top project!" FORCE)
else()
  set(DRAGONFLY_TOP_LEVEL OFF CACHE BOOL "If this project is top project!" FORCE)
endif()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_compile_options(
  -fvisibility=hidden
  -Wno-reserved-identifier
  -Wno-reserved-module-identifier
)

add_subdirectory(DragonFly)
if (DRAGONFLY_TOP_LEVEL)
  add_subdirectory(SandBox)
endif()
