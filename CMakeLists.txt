project(batup CXX)

cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Wall -Werror")

add_definitions(-DDATA_PATH="${CMAKE_SOURCE_DIR}/data")

set(GTEST_PATH ${CMAKE_SOURCE_DIR}/3rdparty/googletest)
set(GTEST_INCLUDE ${GTEST_PATH}/include)
find_library(GTEST_LIBRARY
  NAMES gtest
  HINTS ${GTEST_PATH}/lib)

if(NOT GTEST_LIBRARY)
  message( FATAL_ERROR "GTEST required")
endif()

set(BATUP_SOURCE
)

include_directories(${CMAKE_SOURCE_DIR}/src)

add_executable(batup ${BATUP_SOURCE} src/main.cpp)

target_link_libraries(batup -lm )

enable_testing()

add_executable(test test/test.cpp ${BATUP_SOURCE})
target_include_directories(test PRIVATE ${GTEST_INCLUDE})
target_link_libraries(test ${GTEST_LIBRARY} -lstdc++ -lpthread -lm )

add_test(
  NAME TradeStreamTest
  COMMAND tradestreamtest
  )


