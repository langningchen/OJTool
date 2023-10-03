cmake_minimum_required(VERSION 3.9)
project(OJTool)

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++14 -pthread")

add_executable(main
    Lib/Exception.cpp
    Lib/Curl.cpp
    Lib/StringOperation.cpp
    Lib/tinyxml/tinyxml.cpp
    Lib/tinyxml/tinyxmlerror.cpp
    Lib/tinyxml/tinyxmlparser.cpp
    Lib/tinyxml/tinystr.cpp
    main.cpp
    Tool.cpp
    Luogu.cpp
    Etiger.cpp
    XMOJ.cpp
    USACO.cpp
    Codeforces.cpp
    UVa.cpp
    AtCoder.cpp
)
target_include_directories(main PUBLIC Lib)

find_library(LIBCURL curl REQUIRED)
find_library(LIBJPEG jpeg REQUIRED)
find_library(LIBTIDY tidy REQUIRED)
set(LIBS
    ${LIBCURL}
    ${LIBJPEG}
    ${LIBTIDY}
)
target_link_libraries(main PRIVATE ${LIBS})
