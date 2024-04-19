cmake_minimum_required(VERSION 3.16)

project(AIVis VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (MINGW)
    add_compile_options(-Wa,-mbig-obj)
endif()

add_subdirectory(application)
add_subdirectory(interface)

# add_subdirectory(3rdparty/ublas)

# set(HDF5_LIBRARIES E:/libs/HDF_Group/HDF5/1.14.3/lib)
# set(HDF5_INCLUDE_DIRS E:/libs/HDF_Group/HDF5/1.14.3/include)

# add_subdirectory(3rdparty/HighFive)
add_subdirectory(impl)
