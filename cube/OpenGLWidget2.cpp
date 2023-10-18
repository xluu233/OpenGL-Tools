//
// Created by xlu on 2023/10/16.
//

#include "../cube/OpenGLWidget2.h"

OpenGLWidget2::OpenGLWidget2(QWidget *parent) : QOpenGLWidget(parent){
    //设置采样率
    auto newFormat = this->format();
    newFormat.setSamples(16);
    this->setFormat(newFormat);

    setMinimumSize(1200,800);
    startTimer(1000 / 60);

    m_camera.move(-6, 0, 3);
    m_camera.look(0, 30, 0);
    m_camera.update();

    m_light.setPos({ 10, 3 , 0 });
    m_light.setColor(QColor(120, 34, 65));

    installEventFilter(&m_camera);
}

OpenGLWidget2::~OpenGLWidget2() {
    delete m_model;
}

void OpenGLWidget2::initializeGL() {
    initializeOpenGLFunctions();
    //glClearColor(0, 0.5, 0.7, 1);
    //auto _color = m_light.color() * 0.1;
    //glClearColor(_color.x(), _color.y(), _color.z(), 1);
    glClearColor(0, 0, 0, 1);

    m_model = new Dice();
    m_model->setCamera(&m_camera);
    m_model->setLight(&m_light);
    m_model->setPos({ 0, 0, 0 });
    m_model->init();

}


void OpenGLWidget2::paintGL() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


    m_model->paint();

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    QPainter _painter(this);
    auto _rect = this->rect();
    _painter.setPen(Qt::green);
    _painter.drawLine(_rect.center() + QPoint{ 0, 5 }, _rect.center() + QPoint{ 0, 15 });
    _painter.drawLine(_rect.center() + QPoint{ 0, -5 }, _rect.center() + QPoint{ 0, -15 });
    _painter.drawLine(_rect.center() + QPoint{ 5, 0 }, _rect.center() + QPoint{ 15, 0 });
    _painter.drawLine(_rect.center() + QPoint{ -5, 0 }, _rect.center() + QPoint{ -15, 0 });

    _painter.drawText(QPoint{ 5, 15 }, QString("摄像机位置: (%1, %2, %3)")
            .arg(m_camera.pos().x(), 0, 'f', 3).arg(m_camera.pos().y(), 0, 'f', 3).arg(m_camera.pos().z(), 0, 'f', 3));
    _painter.drawText(QPoint{ 5, 30 }, QString("摄像机角度: (%1, %2, %3)")
            .arg(m_camera.yaw(), 0, 'f', 3).arg(m_camera.pitch(), 0, 'f', 3).arg(m_camera.roll(), 0, 'f', 3));
}

void OpenGLWidget2::resizeGL(int w, int h) {
    m_projection.setToIdentity();
    m_projection.perspective(60, (float)w/h, 0.001, 1000);
    m_model->setProjection(m_projection);
}

void OpenGLWidget2::timerEvent(QTimerEvent *event) {
    m_camera.update();
    float _speed = 0.1;
    float _y = m_model->rotate().y() + _speed;
    if (_y >= 360)
        _y -= 360;
    m_model->setRotate({ 0, _y, 0 });
    _speed += 0.1;
    m_model->setPos(m_light.pos());
    repaint();
}
