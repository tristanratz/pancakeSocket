cmake_minimum_required(VERSION 3.6)

# include hunter gate
include("cmake/HunterGate.cmake")
HunterGate(
        URL "https://github.com/ruslo/hunter/archive/v0.16.15.tar.gz"
        SHA1 "6974c2150fc0d3b09de3ad1efcbf15d360647ffa"
)


# setup project
project(pancakeSocket)
set(CMAKE_CXX_STANDARD 11)

# get src files
file(GLOB SOURCE_FILES *.cpp)
file(GLOB LINKEDLIST LinkedList/*.cpp)
file(GLOB TEST_FILES tests/*.cpp)

# add dependencies
hunter_add_package(GTest)
find_package(GTest CONFIG REQUIRED)
set(LÍBS pthread)

include_directories(${PROJECT_NAME}Test
        ${CMAKE_CURRENT_SOURCE_DIR})


# app
add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${LINKEDLIST} ${CMAKE_CURRENT_SOURCE_DIR}/Log/Log.cpp)
target_link_libraries(${PROJECT_NAME}  pthread)

# test
list(REMOVE_ITEM SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
add_definitions(-DBOOST_TEST_DYN_LINK)
add_executable(${PROJECT_NAME}Test
        ${SOURCE_FILES}
        ${LINKEDLIST}
        ${TEST_FILES}
        ${CMAKE_CURRENT_SOURCE_DIR}/Log/Log.cpp)

target_link_libraries(${PROJECT_NAME}Test
        PUBLIC  pthread
        GTest::main)
