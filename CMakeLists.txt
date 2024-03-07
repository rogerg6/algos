# set minimum cmake version
cmake_minimum_required(VERSION 3.11 FATAL_ERROR)

# project name and language
project(algos LANGUAGES CXX)

# require C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_VERBOSE_MAKEFILE ON)  # 显示详细编译输出
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
add_definitions(-DUNIT_TEST)

# head files
include_directories(${CMAKE_SOURCE_DIR}/unittest/timer)
include_directories(${CMAKE_SOURCE_DIR}/linked_list)
include_directories(${CMAKE_SOURCE_DIR}/list)
include_directories(${CMAKE_SOURCE_DIR}/stack)
include_directories(${CMAKE_SOURCE_DIR}/queue)
include_directories(${CMAKE_SOURCE_DIR}/hash)
include_directories(${CMAKE_SOURCE_DIR}/tree)
include_directories(${CMAKE_SOURCE_DIR}/heap)
include_directories(${CMAKE_SOURCE_DIR}/graph)
include_directories(${CMAKE_SOURCE_DIR}/search)
include_directories(${CMAKE_SOURCE_DIR}/sort)
include_directories(${CMAKE_SOURCE_DIR}/divide_conquer)
include_directories(${CMAKE_SOURCE_DIR}/backtracking)
include_directories(${CMAKE_SOURCE_DIR}/dynamic_programming)

# 设置可执行文件输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# gtest
find_package(GTest REQUIRED)
if(GTest_FOUND)
    message(STATUS "gtest found")
    include_directories(${GTest_INCLUDE_DIRS})
else()
    message(STATUS "gtest not found")
endif()

file(GLOB SOURCES unittest/*.cc)

# 遍历每个源文件，为每个源文件生成对应的可执行文件
foreach(SOURCE ${SOURCES})
    # 获取源文件的名称（不带路径和扩展名）
    get_filename_component(EXEC_NAME ${SOURCE} NAME_WE)
    
    # 添加可执行文件，并指定源文件
    add_executable(${EXEC_NAME} ${SOURCE} unittest/timer/timer.cc)
    target_link_libraries(${EXEC_NAME} gtest gtest_main )
    
    # 安装可执行文件到指定目录
    install(TARGETS ${EXEC_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
endforeach()


