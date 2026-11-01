cmake_minimum_required(VERSION 3.16)

project(Qt6Learn VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()

qt_add_executable(Qt6Learn
    main.cpp
    theme.cpp
    theme.h
    config.h
)

target_link_libraries(Qt6Learn PRIVATE
    Qt6::Widgets
)

set_target_properties(Qt6Learn PROPERTIES
    WIN32_EXECUTABLE OFF
    MACOSX_BUNDLE OFF
    ANDROID_MIN_SDK_VERSION 28
    QT_ANDROID_TARGET_SDK_VERSION 36
    QT_ANDROID_COMPILE_SDK_VERSION 36
)
