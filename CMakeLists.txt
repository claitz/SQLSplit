cmake_minimum_required(VERSION 3.17)
project(SQLSplit)

set(CMAKE_CXX_STANDARD 17)

#set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

add_executable(SQLSplit main.cpp FileUtil.h FileUtil.cpp)

# Link stdc++fs for older gcc versions (< 9)
if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 9.0)
    target_link_libraries(SQLSplit stdc++fs)
endif()