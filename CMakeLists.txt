cmake_minimum_required (VERSION 2.8.8)

message(STATUS "******************************************************************")
message(STATUS "CMAKE_SOURCE_DIR->" ${CMAKE_SOURCE_DIR})
message(STATUS "PROJECT_SOURCE_DIR->)" ${PROJECT_SOURCE_DIR})
message(STATUS "******************************************************************")

set(PROJECT_NAME_ mini-ncnn)
project (${PROJECT_NAME_})

set(EXEC_NAME ncnn.exe)
set(EXEC_SRC ./src/main.cpp)
set(LIB mini_ncnn)
set(SHARE_LIB mini-ncnn-share)
set(GPU_SHARE_LIB gpu-share)
set(STATIC_LIB mini-ncnn-static)




option(DEBUG         "open debug information"  OFF)
option(GOOGLE_CUDA   "Set to switch to build use GOOGLE_CUDA"  ON)

set(DEBUG 1)
set(GOOGLE_CUDA 0)
if (GOOGLE_CUDA)
    add_definitions(-DGOOGLE_CUDA)
    add_definitions(-DEIGEN_USE_GPU)
    message(STATUS "Use GOOGLE_CUDA")
else()
    message(STATUS "Dont Use GOOGLE_CUDA")
endif()

if (DEBUG)
    add_definitions(-DDZHANG_DEBUG)
    message(STATUS "Use DEBUG")
else()
    message(STATUS "Dont Use DEBUG")
endif()


find_package(CUDA REQUIRED)
include_directories(${CUDA_INCLUDE_DIRS})
set(CMAKE_CXX_STANDARD 11)
set(NCNN_INCLUDE ${CMAKE_SOURCE_DIR}/src/ncnn)
set(OPENCV_INCLUDE /usr/local/include/)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11 -W -Wsign-compare -Wmissing-field-initializers")
add_compile_options(-Wsign-compare)

#aux_source_directory(./src DIR_SRCS)
#FILE(GLOB_RECURSE DIR_SRCS "./src/*.cpp" "./src/*.h")

aux_source_directory(${CMAKE_SOURCE_DIR}/src MAIN_SRC)
set(DIR_SRCS ${MAIN_SRC})



FIND_LIBRARY(STATIC_LIBS libncnn.a ${CMAKE_SOURCE_DIR}/lib)
link_directories(${CMAKE_SOURCE_DIR}/lib)
link_directories(/usr/local/lib64)

include_directories(
    src/include
    src/
    /usr/local
    ${NCNN_INCLUDE}/include
)


#set(CUDA_NVCC_FLAGS "--expt-relaxed-constexpr")

add_library(${SHARE_LIB} SHARED ${DIR_SRCS}) #STATIC #SHARED
add_library(${STATIC_LIB} STATIC ${DIR_SRCS}) #STATIC #SHARED

#SET_TARGET_PROPERTIES (${SHARE_LIB) PROPERTIES OUTPUT_NAME ${LIB})
#SET_TARGET_PROPERTIES (${STATIC_LIB) PROPERTIES OUTPUT_NAME ${LIB})

add_executable(${EXEC_NAME} ${EXEC_SRC} ${DIR_SRCS})

#cuda_add_library(${GPU_SHARE_LIB} SHARED ${DIR_GPU_SRCS}) #STATIC #SHARED
#cuda_add_executable(${EXEC_NAME} ${EXEC_SRC} ${DIR_SRCS} ${DIR_GPU_SRCS})

target_link_libraries(${EXEC_NAME} ${STATIC_LIBS} )

#find_package(OpenCV REQUIRED)
#include_directories(${OpenCV_INCLUDE_DIRS})
#target_link_libraries(${PROJECT_NAME_} tensorflow_framework ${OpenCV_LIBS})
