#include "LoadModelWidget.h"

LoadModelWidget::LoadModelWidget(QWidget *parent)
    : QOpenGLWidget(parent)
    , camera(this)
{
    timer.setInterval(18);
    connect(&timer,&QTimer::timeout,this,static_cast<void (LoadModelWidget::*)()>(&LoadModelWidget::update));
    timer.start();

    QSurfaceFormat format;
    format.setSamples(50);
    setFormat(format);
}
LoadModelWidget::~LoadModelWidget()
{

}

void LoadModelWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(1.0f,1.0f,1.0f,1.0f);
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,":/resource/shader/assimp_model_vs.glsl");
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,":/resource/shader/assimp_model_vs.glsl");
    shaderProgram.link();

    model = AssModel::createModel("F:\\OpenGL\\LearnOpenGL-Notes\\resource\\nanosuit\\nanosuit.obj",context(),&shaderProgram);

    glEnable(GL_DEPTH_TEST);
    camera.init();
}

void LoadModelWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    QMatrix4x4 projection;
    projection.perspective(45.0f,width()/(float)height(),0.1f,500.0f);
    shaderProgram.setUniformValue("projection",projection);
    shaderProgram.setUniformValue("view",camera.getView());
    model->draw();
}

void LoadModelWidget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
}

bool LoadModelWidget::event(QEvent*e){
    camera.handle(e);
    return QWidget::event(e);
}

