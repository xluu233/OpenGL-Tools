//
// Created by xlu on 2023/10/13.
//

#ifndef OPENGL_TOOLS_GLFW_TWOTRIANGLE_H
#define OPENGL_TOOLS_GLFW_TWOTRIANGLE_H

#include "base/GLFW_Base.h"

class  GLFW_TwoTriangle : public GLFW_Base
{
public:
    GLFW_TwoTriangle(){}

    void processInput(GLFWwindow *window)
    {
        if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
    }

    void showGL()
    {

    }

};
#endif //OPENGL_TOOLS_GLFW_TWOTRIANGLE_H
