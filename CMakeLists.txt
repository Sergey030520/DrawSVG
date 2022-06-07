cmake_minimum_required(VERSION 3.20)
project(DrawSvg)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "C:/Qt/5.15.2/mingw81_64/lib/cmake")
set(MY_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(MY_UI_DIR ${CMAKE_SOURCE_DIR}/ui)

find_package(Qt5 PATHS C:/Qt/Qt-5.15.2 COMPONENTS
        Core
        Gui
        Widgets
        Xml
        Svg
        REQUIRED QUIET)

add_subdirectory(src)