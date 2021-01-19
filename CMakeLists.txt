cmake_minimum_required(VERSION 3.5)

project(EasyHosts LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

find_package(PkgConfig)
pkg_search_module(SQLITE3 REQUIRED sqlite3)
include_directories(${SQLITE3_INCLUDE_DIRS})

add_executable(EasyHost
        main.cpp
        widget.cpp
        widget.h
        widget.ui)
target_link_libraries(EasyHost PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

add_executable(core core.cpp)
target_link_libraries(core ${SQLITE3_LIBRARIES})