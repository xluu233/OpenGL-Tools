cmake_minimum_required(VERSION 3.10)
project(OpenGL_Tools)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_PREFIX_PATH "C:/App/Qt/Qt6/6.4.3/mingw_64")

#set(CMAKE_PREFIX_PATH "C:/App/Qt/Qt6/6.4.3/msvc2019_64")

find_package(Qt6 COMPONENTS
        Core
        Gui
        OpenGLWidgets
        Widgets
        REQUIRED)



#set(ASSIMP_LIB_DIR ${PROJECT_SOURCE_DIR}/libs/)
#include_directories(${ASSIMP_LIB_DIR})


#第三方库头文件和动态库
#INCLUDE_DIRECTORIES(include)
#include_directories(${PROJECT_SOURCE_DIR}/include/assimp)
include_directories(${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_SOURCE_DIR}/libs)


#link_directories(libs/assimp-vc143-mtd.dll)

#link_directories(libs/assimp-vc143-mtd.lib)
#link_directories("F:/OpenGL/OpenGL-Tools/libs/assimp-vc143-mtd.dll")
#link_directories("F:/OpenGL/OpenGL-Tools/libs/assimp-vc143-mtd.lib")

#include(FetchContent)
#set(FETCHCONTENT_BASE_DIR ${PROJECT_SOURCE_DIR}/libs CACHE PATH "Missing description." FORCE)
#FetchContent_Declare(assimp GIT_REPOSITORY https://github.com/assimp/assimp.git GIT_TAG master)
#set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
#set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
#set(ASSIMP_INJECT_DEBUG_POSTFIX OFF CACHE BOOL "" FORCE)
#set(ASSIMP_INSTALL OFF CACHE BOOL "" FORCE)
#FetchContent_MakeAvailable(assimp)

#target_include_directories(OpenGL_Tools PRIVATE libs/assimp-src/include)
#target_link_libraries(OpenGL_Tools assimp)


add_executable(OpenGL_Tools
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui

        qgl_widget/qgl_widgetinwindow.cpp
        qgl_widget/qgl_widgetinwindow.h
        qgl_widget/qgl_widgetinwindow.ui
        qgl_widget/SimpleQGLWidget.h
        qgl_widget/VaoTestWidget.h
        qgl_widget/VaoTestWidget.cpp

        qgl_window/SimpleTriangleWindow.h
        qgl_window/SomeTriangleWindow.h
        qgl_window/QVerture.cpp
        qgl_window/QVerture.h
        qgl_window/QCubeWindow.h
        base/QCamera.cpp
        base/QCamera.h
        base/Light.cpp
        base/Light.h
        base/Model.cpp
        base/Model.h

        cube/LightModel.cpp
        cube/LightModel.h
        cube/Dice.cpp
        cube/Dice.h
        cube/OpenGLWidget.cpp
        cube/OpenGLWidget.h
        cube/OpenGLWidget2.cpp
        cube/OpenGLWidget2.h

        base/GLHelper.h
        src/stb_image.cpp
        base/camera_glm.hpp

        skybox/SkyBox.h
        skybox/SkyBox.cpp
        skybox/TWindow.h
        skybox/TWindow.cpp

        assimp/camera2.cpp
        assimp/camera2.h
        assimp/LoadModelWidget.cpp
        assimp/LoadModelWidget.h
        assimp/model/AssModel.cpp
        assimp/model/AssModel.h
        assimp/model/assimp_helper.h
        assimp/model/AssMesh.cpp
        assimp/model/AssMesh.h)


#添加资源文件
set(shaders_resource_files
        "resource/shader/fshader.glsl"
        "resource/shader/fshader2.glsl"
        "resource/shader/fshader3.glsl"

        "resource/shader/vshader.glsl"
        "resource/shader/vshader3.glsl"
        "resource/shader/vao_v_s.glsl"
        "resource/shader/vao_f_s.glsl"
        "resource/shader/3_verture_vs.glsl"
        "resource/shader/3_verture_fs.glsl"
        "resource/shader/cube_fs.glsl"
        "resource/shader/cube_vs.glsl"
        "resource/shader/common_fs.glsl"
        "resource/shader/common_vs.glsl"
        "resource/shader/common_light_fs.glsl"
        "resource/shader/common_light_vs.glsl"
        "resource/shader/skybox_fs.glsl"
        "resource/shader/skybox_vs.glsl"
        "resource/shader/assimp_model_fs.glsl"
        "resource/shader/assimp_model_vs.glsl"
        )

qt6_add_resources(OpenGL_Tools "shaders"
        PREFIX "/"
        FILES ${shaders_resource_files}
        )

set(image_resource_files
        "resource/image/cachemem.png"
        "resource/image/cube.png"
        "resource/image/cube2.png"
        "resource/image/world-map.jpg"
        "resource/skybox/back.jpg"
        "resource/skybox/bottom.jpg"
        "resource/skybox/cube.png"
        "resource/skybox/front.jpg"
        "resource/skybox/left.jpg"
        "resource/skybox/right.jpg"
        "resource/skybox/top.jpg"
        )

qt6_add_resources(OpenGL_Tools "image"
        PREFIX "/"
        FILES ${image_resource_files}
        )


target_link_libraries(
        OpenGL_Tools
        Qt::Core
        Qt::Gui
        Qt::OpenGL
        Qt::OpenGLWidgets
        Qt::Widgets
        ${PROJECT_SOURCE_DIR}/libs/libassimp-5.dll
        ${PROJECT_SOURCE_DIR}/libs/libzlibstatic.a
)


#set(ASSIMP_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include/assimp)
#set(ASSIMP_LIBRARY ${PROJECT_SOURCE_DIR}/include/libs/assimp-vc143-mtd.lib)
#
#target_link_libraries(OpenGL_Tools ${ASSIMP_INCLUDE_DIR})
#target_link_libraries(OpenGL_Tools ${ASSIMP_LIBRARY})


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
