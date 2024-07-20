cmake_minimum_required(VERSION 3.9)
project(OJTool)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pthread")
set(CMAKE_CXX_STANDARD 17)

aux_source_directory(. SOURCE_FILES)
add_executable(OJTool
    ${SOURCE_FILES}
    Lib/tinyxml/tinystr.cpp
    Lib/tinyxml/tinyxml.cpp
    Lib/tinyxml/tinyxmlerror.cpp
    Lib/tinyxml/tinyxmlparser.cpp
)
target_include_directories(OJTool PUBLIC .)
target_include_directories(OJTool PUBLIC Lib)

find_library(LIBCURL curl REQUIRED)
find_library(LIBJPEG jpeg REQUIRED)
find_library(LIBTIDY tidy REQUIRED)
set(LIBS
    ${LIBCURL}
    ${LIBJPEG}
    ${LIBTIDY}
)
target_link_libraries(OJTool PRIVATE ${LIBS})
