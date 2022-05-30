cmake_minimum_required(VERSION 3.20)

add_executable(DrawSvg main.cpp mainwindow.cpp ${MY_INCLUDE_DIR}/mainwindow.h
        ${MY_UI_DIR}/gui.ui GraphicScene.cpp ${MY_INCLUDE_DIR}/GraphicScene.h SvgRenderer.cpp
        ${MY_INCLUDE_DIR}/SvgRenderer.h Map.cpp
        ${MY_INCLUDE_DIR}/Map.h MapJsonLoader.cpp ${MY_INCLUDE_DIR}/MapJsonLoader.h)

target_link_libraries(DrawSvg
        PRIVATE
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Xml
        Qt5::Svg
        )

qt5_import_plugins(DrawSvg INCLUDE_BY_TYPE imageformats Qt5::QGifPlugin Qt5::QJpegPlugin Qt5::QPngPlugin)


if (WIN32)
    set(DEBUG_SUFFIX)
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
                "${QT_INSTALL_PATH}/bin/Qt5${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()

target_include_directories(DrawSvg PUBLIC ${MY_INCLUDE_DIR})