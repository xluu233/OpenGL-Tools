//
// Created by xlu on 2023/10/13.
//

#ifndef OPENGL_TOOLS_GLFW_TRIANGLE_H
#define OPENGL_TOOLS_GLFW_TRIANGLE_H

#include <valarray>
#include "base/GLFW_Base.h"

class GLFW_Triangle : public GLFW_Base
{
public:
    GLFW_Triangle() : GLFW_Base()
    {
        log("init");
    }

    ~GLFW_Triangle()
    {
        log("deleted~");
    }

    void log(const std::string& str) override
    {
        std::cout << "[GLFW_Triangle]  " << str << std::endl;
    }

    void processInput(GLFWwindow *window)
    {
        if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
    }

    void showGL() override
    {

        //顶点着色器代码
        const char* vertexShaderSource = "#version 330 core\n"
                                         "layout (location = 0) in vec3 aPos;\n"
                                         "void main()\n"
                                         "{\n"
                                         "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                         "}\0";


        //片段着色器代码
        const char* fragShaderSource = "#version 330 core\n"
                                       "out vec4 FragColor;\n"
                                       "void main()\n"
                                       "{\n"
                                       "   FragColor = vec4(1.0f, 0.8f, 0.1f, 1.0f);\n"
                                       "}\0";

        float vertices[] = {
                0.5f, 0.5f, 0.0f,   // 右上角
                0.5f, -0.5f, 0.0f,  // 右下角
                0.0f,0.0f,0.0f, //中心点
                -0.5f, 0.5f, 0.0f,   // 左上角
                -0.5f, -0.5f, 0.0f, // 左下角
        };

        unsigned int indices[] = {
                // 注意索引从0开始!
                // 此例的索引(0,1,2,3)就是顶点数组vertices的下标，
                // 这样可以由下标代表顶点组合成矩形

                0, 1, 2, // 第一个三角形
                2, 3, 4  // 第二个三角形
        };

        unsigned int VBO, VAO, EBO = 0;
        unsigned int shaderProgram = 0;


        //setup1: 生成VBO,VAO对象
        //unsigned int VBO, VAO;
        glGenBuffers(1, &EBO);
        glGenBuffers(1, &VBO);
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        //1.1 把新创建的缓冲绑定到GL_ARRAY_BUFFER（缓冲内存）目标上
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        //1.2 把顶点数据复制到缓冲的内存中
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


        //1.3: 链接顶点属性,
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);	//参数非常多
        glEnableVertexAttribArray(0);

        //解绑VBO,VAO
        //glBindBuffer(GL_ARRAY_BUFFER, 0);
        //glBindVertexArray(0);

        //setup2:现在顶点数据已经存储在内存中了，需要通过着色器处理这些数据

        //2.1 创建顶点着色器
        unsigned int vertexShader;
        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        //着色器源码附加到着色器对象上
        glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
        //编译着色器代码
        glCompileShader(vertexShader);

        //2.2 片段着色器
        unsigned int fragShader;
        fragShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragShader, 1, &fragShaderSource, nullptr);
        glCompileShader(fragShader);

        //setup3: 把两个着色器对象链接到一个用来渲染的着色器程序中

        //3.1 创建一个程序，并返回新创建程序对象的ID引用
        //unsigned int shaderProgram;
        shaderProgram = glCreateProgram();
        //3.2 把着色器附加到程序上
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragShader);
        glLinkProgram(shaderProgram);

        //激活程序
        glUseProgram(shaderProgram);

        //把着色器对象链接到程序对象以后，可以删除着色器了
        glDeleteShader(vertexShader);
        glDeleteShader(fragShader);

        //循环绘制
        while (!glfwWindowShouldClose(glfWindow))
        {
            processInput(glfWindow);

            //重新绘制的时候清除color
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            //线条模式
            //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

            // 更新uniform颜色
            float timeValue = glfwGetTime();
            float greenValue = sin(timeValue) / 2.0f + 0.5f;
            int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
            glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

            // draw our first triangle
            glUseProgram(shaderProgram);
            glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
            //glDrawArrays(GL_TRIANGLES, 0, 3);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            // glBindVertexArray(0); // no need to unbind it every time

            //交换颜色缓冲,迭代绘制窗口
            glfwSwapBuffers(glfWindow);
            //检查有没有触发什么事件（比如键盘输入、鼠标移动等）
            glfwPollEvents();
        }

        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteProgram(shaderProgram);

        //销毁当前窗口
        glfwDestroyWindow(glfWindow);
    }

};
#endif //OPENGL_TOOLS_GLFW_TRIANGLE_H
