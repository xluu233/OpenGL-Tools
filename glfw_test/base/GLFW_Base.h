//
// Created by BugMaker on 2023/10/9.
//

#ifndef OPENGL_TOOLS_GLFW_BASE_H
#define OPENGL_TOOLS_GLFW_BASE_H

#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <windows.h>


//窗口宽高设置
extern unsigned int SCR_WIDTH;
extern unsigned int SCR_HEIGHT;

/*
 * 基于GLFW库创建窗口，此类为抽象窗口类
 */
class GLFW_Base {

private:
    int initGL();

public:
    GLFW_Base();

    virtual ~GLFW_Base();

    virtual void showGL() = 0;

    virtual void log(const std::string& str)
    {
        std::cout << "[GLFW_Base]  " << str << std::endl;
    }

public:
    GLFWwindow* glfWindow;
};


#endif //OPENGL_TOOLS_GLFW_BASE_H
