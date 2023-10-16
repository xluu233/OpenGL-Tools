//
// Created by xlu on 2023/10/9.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include "mainwindow.h"
#include "ui_MainWindow.h"
#include "glfw_test/base/GLFW_Base.h"
#include "glfw_test/GLFW_Windows.hpp"
#include "glfw_test/GLFW_Triangle.h"
#include "qgl_widget/qgl_widgetinwindow.h"
#include "qgl_window/SimpleTriangleWindow.h"
#include "qgl_window/SomeTriangleWindow.h"
#include "glfw_test/GLFW_TwoTriangle.h"
#include "qgl_widget/VaoTestWidget.h"
#include "qgl_window/QVerture.h"
#include "qgl_window/QCubeWindow.h"
#include "base/OpenGLWidget.h"
#include "base/OpenGLWidget2.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    //on_btn_create_gl_clicked就是默认的btn_create_gl点击事件的默认槽函数了，不需要绑定
    //connect(ui->btn_create_gl,&QPushButton::clicked, this, on_btn_create_gl_clicked());

    /*---------------GLFW--------------------------------*/
    connect(ui->btn_create_glfw_1,&QPushButton::clicked, this, [&](){
        GLFW_Base *glBase = new GLFW_Windows();
        glBase->showGL();
        delete glBase;
    });

    connect(ui->btn_create_glfw_2,&QPushButton::clicked, this, [&](){
        GLFW_Triangle *w = new GLFW_Triangle();
        w->showGL();
        delete w;
    });
    /*---------------GLFW END--------------------------------*/


    //创建QOpenGL Widget
    connect(ui->btn_create_qglwidget,&QPushButton::clicked, this, [&](){
        QGL_WidgetInWindow *w = new QGL_WidgetInWindow(this);
        w->show();
    });

    //三角形
    connect(ui->btn_create_triangle,&QPushButton::clicked, this,[&](){
        SimpleTriangleWindow *w = new SimpleTriangleWindow();
        w->show();
    });

    //多个三角形
    connect(ui->btn_create_triangle_2,&QPushButton::clicked, this,[&](){
        SomeTriangleWindow *w = new SomeTriangleWindow();
        w->show();
    });

    //vao test
    connect(ui->btn_vao_test,&QPushButton::clicked, this,[&](){
        VaoTestWidget *w = new VaoTestWidget();
        w->show();
    });

    //Qt API实现纹理
    connect(ui->btn_create_verture,&QPushButton::clicked, this,[&](){
        QVerture *w = new QVerture();
        w->show();
    });

    connect(ui->btn_create_cube,&QPushButton::clicked, this,[&](){
        QCubeWindow *w = new QCubeWindow();
        w->show();
    });

    connect(ui->btn_create_cube_2,&QPushButton::clicked, this,[&](){
        OpenGLWidget *w = new OpenGLWidget();
        w->show();
    });

    connect(ui->btn_create_cube_3,&QPushButton::clicked, this,[&](){
        OpenGLWidget2 *w = new OpenGLWidget2();
        w->show();
    });


}

MainWindow::~MainWindow() {
    delete ui;
}
