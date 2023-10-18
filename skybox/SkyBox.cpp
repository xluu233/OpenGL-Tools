#include <iostream>
#include "SkyBox.h"
#include "stb_image.h"

SkyBox::SkyBox(QOpenGLExtraFunctions *func) : m_func(func), m_vertexShader(QOpenGLShader::Vertex),
                                              m_fragmentShader(QOpenGLShader::Fragment) {
    initBuffer();
    initShader();
    initTexture();
}

SkyBox::~SkyBox() {
    m_arrayBuf.destroy();
}

void SkyBox::initBuffer() {
    GLfloat skyboxVertices[] = { // Positions
            -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f,
            1.0f, -1.0f,

            -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f,
            -1.0f, 1.0f,

            1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f, 1.0f, -1.0f,
            -1.0f,

            -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f, 1.0f, -1.0f, -1.0f,
            1.0f,

            -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f,
            -1.0f,

            -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f
    };
    m_vertexCount = sizeof skyboxVertices / sizeof skyboxVertices[0];
    m_arrayBuf.create();

    m_func->glGenVertexArrays(1, &m_vao);
    m_func->glBindVertexArray(m_vao);

    m_arrayBuf.bind();
    m_arrayBuf.allocate(skyboxVertices, sizeof skyboxVertices);
    const int positionLocation = 0;
    m_func->glEnableVertexAttribArray(positionLocation);
    m_func->glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, nullptr);

    m_func->glBindVertexArray(0);
}

int SkyBox::initShader() {
    if (!m_vertexShader.compileSourceFile("..\\resource\\shader\\skybox_vs.glsl")) {
        qWarning() << m_vertexShader.log();
    }
    if (!m_fragmentShader.compileSourceFile("..\\resource\\shader\\skybox_fs.glsl")) {
        qWarning() << m_fragmentShader.log();
    }
    return 0;
}

void SkyBox::initTexture() {
/*    std::vector<std::string> faces{
            "F:\\OpenGL\\OpenGL-Tools\\resource\\skybox\\right.jpg",
            "F:\\OpenGL\\OpenGL-Tools\\resource\\skybox\\left.jpg",
            "F:\\OpenGL\\OpenGL-Tools\\resource\\skybox\\top.jpg",
            "F:\\OpenGL\\OpenGL-Tools\\resource\\skybox\\bottom.jpg",
            "F:\\OpenGL\\OpenGL-Tools\\resource\\skybox\\back.jpg",
            "F:\\OpenGL\\OpenGL-Tools\\resource\\skybox\\front.jpg",
    };*/
    std::vector<std::string> faces{
            "..\\resource\\skybox\\right.jpg",
            "..\\resource\\skybox\\left.jpg",
            "..\\resource\\skybox\\top.jpg",
            "..\\resource\\skybox\\bottom.jpg",
            "..\\resource\\skybox\\back.jpg",
            "..\\resource\\skybox\\front.jpg",
    };
    m_func->glGenTextures(1, &m_cubeTexture);
    m_func->glBindTexture(GL_TEXTURE_CUBE_MAP, m_cubeTexture);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++) {
        unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data) {
            m_func->glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB,
                                 GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        } else {
            std::cout << "CubeMap texture failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    m_func->glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    m_func->glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    m_func->glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    m_func->glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    m_func->glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

void SkyBox::draw(QOpenGLShaderProgram *program, const QMatrix4x4 &model, const QMatrix4x4 &view,
                  const QMatrix4x4 &project) {
    m_func->glDepthFunc(GL_LEQUAL);
    program->removeAllShaders();
    program->addShader(&m_vertexShader);
    program->addShader(&m_fragmentShader);
    if (!program->link()) {
        qWarning() << program->log();
        return;
    }
    if (!program->bind()) {
        qWarning() << program->log();
        return;
    }
    m_func->glBindVertexArray(m_vao);

    m_func->glActiveTexture(GL_TEXTURE0);
    m_func->glBindTexture(GL_TEXTURE_CUBE_MAP, m_cubeTexture);

    program->setUniformValue("projection", project);
    program->setUniformValue("view", view);
    program->setUniformValue("model", model);
    program->setUniformValue("skyBox", 0);

    m_func->glDrawArrays(GL_TRIANGLES, 0, m_vertexCount);
    m_func->glDepthFunc(GL_LESS);
}
