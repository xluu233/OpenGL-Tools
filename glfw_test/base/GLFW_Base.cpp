//
// Created by BugMaker on 2023/10/9.
//

#include "GLFW_Base.h"

unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 600;

GLFW_Base::GLFW_Base() {
    std::cout << "GLFW_Base init" << std::endl;
    initGL();
}

GLFW_Base::~GLFW_Base() {
    std::cout << "GLFW_Base deleted~" << std::endl;
    //glfWindow不需要delete,应为在glfwTerminate()中会删除一切gl资源。
    //终止GLFW：在我们使用完毕后，需要在程序退出前及时的终止它
    glfwTerminate();
}

int GLFW_Base::initGL() {
    //初始化glfw
    glfwInit();
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //初始化窗口
    glfWindow = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", nullptr, nullptr);
    if (glfWindow == nullptr)
    {
        std::cout << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }

    //设置上下文为当前
    glfwMakeContextCurrent(glfWindow);

    //初始化glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "glad failed to init" << std::endl;
        return -1;
    }

    //注册窗口监听函数
    glfwSetFramebufferSizeCallback(glfWindow, [](GLFWwindow* window, int width, int height){
        std::cout << "size changed, width:" << width << " height:" << height << std::endl;
        SCR_WIDTH = width;
        SCR_HEIGHT = height;
        //重新设置窗口大小
        glViewport(0, 0, width, height);
    });

    //错误信息
    glfwSetErrorCallback([](int error_code, const char* description){
        std::cout << "Error: " << error_code << "      description:" << description << std::endl;
    });

    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
    return 0;
}
