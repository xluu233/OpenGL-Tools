cmake_minimum_required(VERSION 3.10)
project(OpenGL_Tools)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_PREFIX_PATH "C:/App/Qt/Qt6/6.4.3/mingw_64")

find_package(Qt6 COMPONENTS
        Core
        Gui
        OpenGLWidgets
        Widgets
        REQUIRED)

add_executable(OpenGL_Tools
        main.cpp
        src/glad.c
        glfw_test/base/GLFW_Base.cpp
        glfw_test/base/GLFW_Base.h
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        glfw_test/GLFW_Windows.hpp
        qgl_widget/QGL_Widget.hpp
        qgl_widget/qgl_widgetinwindow.cpp
        qgl_widget/qgl_widgetinwindow.h
        qgl_widget/qgl_widgetinwindow.ui
        ${RESOURCE_FILES}
        qgl_window/QGL_Window.h
        qgl_window/QGL_Window.h
        qgl_window/TriangleWindow.cpp
        qgl_window/TriangleWindow.h
        qgl_window/QGL_Window.cpp
        qgl_window/SimpleTriangleWindow.h
        qgl_window/SomeTriangleWindow.h
        qgl_window/VertexCubeWindow.hpp glfw_test/GLFW_Triangle.h glfw_test/GLFW_TwoTriangle.h qgl_widget/VaoTestWidget.h qgl_widget/VaoTestWidget.cpp)

#添加资源文件
set(shaders_resource_files
        "resource/shader/fshader.glsl"
        "resource/shader/fshader2.glsl"
        "resource/shader/fshader3.glsl"

        "resource/shader/vshader.glsl"
        "resource/shader/vshader3.glsl"
        "resource/shader/vao_v_s.glsl"
        "resource/shader/vao_f_s.glsl"
        )



qt6_add_resources(OpenGL_Tools "shaders"
        PREFIX "/"
        FILES ${shaders_resource_files}
        )

#第三方库头文件和动态库
INCLUDE_DIRECTORIES(include)
link_directories(libs)

target_link_libraries(
        OpenGL_Tools
        ${PROJECT_SOURCE_DIR}/libs/glfw3.dll
        Qt::Core
        Qt::Gui
        Qt::OpenGL
        Qt::OpenGLWidgets
        Qt::Widgets
)


if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
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