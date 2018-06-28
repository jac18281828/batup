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
  src/compressor.h
  src/decompressor.h
  src/properties.h
  src/wordordercomp.h
  src/wordordercomp.cpp
  src/wordorderdecomp.h
  src/wordorderdecomp.cpp
  src/properties.cpp
  src/app.h
  src/app.cpp  
  src/compapp.h
  src/compapp.cpp
  src/decompapp.h
  src/decompapp.cpp
)

include_directories(${CMAKE_SOURCE_DIR}/src)

add_executable(batup ${BATUP_SOURCE} src/main.cpp)

target_link_libraries(batup -lm )

add_executable(batdown ${BATUP_SOURCE} src/main.cpp)

target_link_libraries(batdown -lm )

enable_testing()

add_executable(propertiestest test/propertiestest.cpp ${BATUP_SOURCE})
target_include_directories(propertiestest PRIVATE ${GTEST_INCLUDE})
target_link_libraries(propertiestest ${GTEST_LIBRARY} -lstdc++ -lpthread -lm )

add_test(
  NAME PropertiesTest
  COMMAND propertiestest
  )

add_executable(byteordertest test/byteordertest.cpp ${BATUP_SOURCE})
target_include_directories(byteordertest PRIVATE ${GTEST_INCLUDE})
target_link_libraries(byteordertest ${GTEST_LIBRARY} -lstdc++ -lpthread -lm )

add_test(
  NAME ByteOrderTest
  COMMAND byteordertest
  )



add_executable(wordordercomptest test/wordordercomptest.cpp ${BATUP_SOURCE})
target_include_directories(wordordercomptest PRIVATE ${GTEST_INCLUDE})
target_link_libraries(wordordercomptest ${GTEST_LIBRARY} -lstdc++ -lpthread -lm )

add_test(
  NAME WordOrderCompTest
  COMMAND wordordercomptest
  )

add_executable(wordorderdecomptest test/wordorderdecomptest.cpp ${BATUP_SOURCE})
target_include_directories(wordorderdecomptest PRIVATE ${GTEST_INCLUDE})
target_link_libraries(wordorderdecomptest ${GTEST_LIBRARY} -lstdc++ -lpthread -lm )

add_test(
  NAME WordOrderDecompTest
  COMMAND wordorderdecomptest
  )

