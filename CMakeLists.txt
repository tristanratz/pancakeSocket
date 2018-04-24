cmake_minimum_required(VERSION 3.10)
project(pancakeSocket)

set(CMAKE_CXX_STANDARD 11)

file(GLOB SOURCE_FILES *.cpp /LinkedList/*.cpp)

#set(SOURCE_FILES *.cpp)

add_executable(pancakeSocket ${SOURCE_FILES})

find_library (LIBSTDCXX NAMES stdc++)

add_compile_options(-stdlib=libstdc++)

target_link_libraries(${PROJECT_NAME} ${LIBSTDCXX} ${YOUR_OTHER_LIBRARIES})