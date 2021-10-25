set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall -fPIC")


project(angka C)
cmake_minimum_required(VERSION 3.1)

file(GLOB agx_src
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/*.c
)

file(GLOB agv_src
        ${CMAKE_CURRENT_SOURCE_DIR}/src/visual/*.c
)

FIND_PACKAGE(PkgConfig REQUIRED)
PKG_CHECK_MODULES(GTK REQUIRED gtk+-3.0)

INCLUDE_DIRECTORIES(${GTK_INCLUDE_DIRS})
LINK_DIRECTORIES(${GTK_LIBRARY_DIRS})
ADD_DEFINITIONS(${GTK_CFLAGS_OTHER})
message(STATUS ${GTK_LIBRARIES})

add_library(agx STATIC ${agx_src})
add_library(agv STATIC ${agv_src})

target_include_directories(agx
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_BINARY_DIR})

target_link_directories(agx PUBLIC ${GTK_LIBRARY_DIRS})
target_link_libraries(agx PUBLIC ${GTK_LIBRARIES})

target_include_directories(agv
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_BINARY_DIR})

target_link_directories(agv PUBLIC ${GTK_LIBRARY_DIRS})
target_link_libraries(agv PUBLIC ${GTK_LIBRARIES})

find_package(PythonLibs)

find_package(SWIG)
include(UseSWIG)

set (UseSWIG_TARGET_NAME_PREFERENCE STANDARD)
swig_add_library(angkapy
    LANGUAGE python
    SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/python/angka.i)

set_property(TARGET angkapy PROPERTY SWIG_USE_TARGET_INCLUDE_DIRECTORIES TRUE)
target_include_directories(angkapy
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${PYTHON_INCLUDE_PATH}
)

target_link_directories(angkapy
    PUBLIC
    ${PYTHON_LIBRARY_PATH}
)

if(WIN32)
set(SWIG_WIN_INCLUDE_DIRECTORIES C:/msys64/usr/share/swig/4.0.2)
set(Python_NumPy_INCLUDE_DIR C:/ProgramData/Miniconda3/Lib/site-packages/numpy/core/include)
set(Python_NumPy_LINK_DIR C:/ProgramData/Miniconda3/Lib/site-packages/numpy/core/lib)
target_include_directories(angkapy
    PUBLIC
    ${SWIG_WIN_INCLUDE_DIRECTORIES}
    ${SWIG_WIN_INCLUDE_DIRECTORIES}/python
    ${Python_NumPy_INCLUDE_DIR})
target_link_directories(angkapy
    PUBLIC
    ${Python_NumPy_LINK_DIR})
target_link_libraries(angkapy
    PUBLIC
    npymath)
endif()

target_link_libraries(angkapy
    PUBLIC 
        agx
        agv
        ${PYTHON_LIBRARIES}    
)