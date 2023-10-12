//
// Created by xlu on 2023/10/10.
//

#ifndef OPENGL_TOOLS_GLFW_WINDOWS_HPP
#define OPENGL_TOOLS_GLFW_WINDOWS_HPP

#include "base/GLFW_Base.h"

/**
 * 使用GLFW库来创建OpenGL窗口，因为Qt已经支持OpenGL窗口，之后的示例不会采用此方案
 */
class GLFW_Windows : public GLFW_Base{

public:
    GLFW_Windows()
    {
        log("init");
    }

    ~GLFW_Windows()
    {
        log("deleted~");
    }

    void log(const std::string& str) override
    {
        std::cout << "[GLFW_Windows]  " << str << std::endl;
    }

    void processInput(GLFWwindow *window)
    {
        if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
    }

    void showGL() override
    {
        //循环绘制
        while (!glfwWindowShouldClose(glfWindow))
        {
            processInput(glfWindow);

            //重新绘制的时候清除color
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            //交换颜色缓冲,迭代绘制窗口
            glfwSwapBuffers(glfWindow);
            //检查有没有触发什么事件（比如键盘输入、鼠标移动等）
            glfwPollEvents();
        }
        //销毁当前窗口
        glfwDestroyWindow(glfWindow);
    }
};


#endif //OPENGL_TOOLS_GLFW_WINDOWS_HPP
