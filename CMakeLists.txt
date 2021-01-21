cmake_minimum_required(VERSION 3.5)

project(EasyHosts LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Core Sql REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Core Sql REQUIRED)

#find_package(PkgConfig)

add_executable(EasyHost
        src/main.cpp
        src/widget.cpp
        src/widget.h
        src/widget.ui)
target_link_libraries(EasyHost PRIVATE
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::Core)

add_executable(core src/core.cpp)
target_link_libraries(core PRIVATE
        Qt${QT_VERSION_MAJOR}::Sql)