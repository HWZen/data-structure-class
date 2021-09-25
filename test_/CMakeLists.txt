cmake_minimum_required(VERSION 3.08)
project(google_test_unit)

set(GTEST_PATH E:\\Github\\googletest\\build\\lib\\Debug)

set(CMAKE_CXX_STANDARD 17)
if(MSVC)
    # Use the static C library for all build types
    foreach(var
            CMAKE_C_FLAGS CMAKE_C_FLAGS_DEBUG CMAKE_C_FLAGS_RELEASE
            CMAKE_C_FLAGS_MINSIZEREL CMAKE_C_FLAGS_RELWITHDEBINFO
            CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
            CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO
            )
        if(${var} MATCHES "/MD")
            # 正则表达式替换/MD为/MT
            string(REGEX REPLACE "/MD" "/MT" ${var} "${${var}}")
        endif()
    endforeach()
endif(MSVC)
include_directories(../)
include_directories(../../googletest/googletest/include)
link_directories(../../googletest/build/lib/Debug)

set(LIB ${GTEST_PATH}/gtestd.lib ${GTEST_PATH}/gtest_maind.lib)
#add_subdirectory(../../googletest gtest_lib)
add_executable(test test.cpp)
if (CMAKE_HOST_UNIX)
    target_link_libraries(test gtest gtest_main pthread)
elseif(CMAKE_HOST_WIN32)
    target_link_libraries(test ${LIB})
endif()