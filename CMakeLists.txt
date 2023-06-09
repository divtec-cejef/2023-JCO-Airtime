cmake_minimum_required(VERSION 3.24)

set(UIS src/mainfrm.ui)

# Find Qt6
file(GLOB QT_INSTALL_PATH C:/Qt/6.*)

set(CMAKE_PREFIX_PATH ${QT_INSTALL_PATH}/mingw_64)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC TRUE)

set(CMAKE_CXX_COMPILER "C:/Qt/Tools/mingw1120_64/bin/g++.exe")

project(2023-JCO-Airtime LANGUAGES CXX)

# set cmake make program
set(CMAKE_MAKE_PROGRAM "C:/Qt/Tools/mingw1120_64/bin/mingw32-make.exe")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

include_directories(src)

add_executable(2023-JCO-Airtime
        src/2023-JCO-Airtime.pro
        src/gamecanvas.cpp src/gamecanvas.h
        src/gamecore.cpp src/gamecore.h
        src/gamescene.cpp src/gamescene.h
        src/gameview.cpp src/gameview.h
        src/main.cpp
        src/mainfrm.cpp src/mainfrm.h src/mainfrm.ui
        src/resources.cpp src/resources.h
        src/sprite.cpp src/sprite.h
        src/spritetickhandler.cpp src/spritetickhandler.h
        src/utilities.cpp src/utilities.h
        src/Player.cpp src/Player.h
        src/PhysicsEntity.cpp src/PhysicsEntity.h
        src/AdvancedCollisionSprite.cpp src/AdvancedCollisionSprite.h
        src/DirectionalEntityCollider.cpp src/DirectionalEntityCollider.h
        src/LevelLoader.cpp src/LevelLoader.h
        src/AnimatedSprite.cpp src/AnimatedSprite.h
        src/LevelTrigger.cpp src/LevelTrigger.h
        src/Collectible.cpp src/Collectible.h
        src/DashRefill.cpp src/DashRefill.h
        src/Particle.cpp src/Particle.h
        src/MovingPlatform.cpp src/MovingPlatform.h)

target_link_libraries(2023-JCO-Airtime
        Qt::Core
        Qt::Gui
        Qt6::Widgets
        )

qt_import_plugins(${PROJECT_NAME} INCLUDE Qt6::QSvgPlugin)

if (WIN32)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core Gui Widgets)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()
