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
#include "qgl_window/TriangleWindow.h"
#include "qgl_window/SimpleTriangleWindow.h"
#include "qgl_window/SomeTriangleWindow.h"
#include "glfw_test/GLFW_TwoTriangle.h"
#include "qgl_widget/VaoTestWidget.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    //on_btn_create_gl_clicked就是默认的btn_create_gl点击事件的默认槽函数了，不需要绑定
    //connect(ui->btn_create_gl,&QPushButton::clicked, this, on_btn_create_gl_clicked());

    /**
     * 创建GLFW
     */
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

    connect(ui->btn_create_glfw_3,&QPushButton::clicked, this, [&](){
        GLFW_TwoTriangle *w = new GLFW_TwoTriangle();
        w->showGL();
        delete w;
    });

    connect(ui->btn_create_qglwidget,&QPushButton::clicked, this, [&](){
        //在这里必须new，否则栈内存对象会闪退
        QGL_WidgetInWindow *w = new QGL_WidgetInWindow(this);
        w->show();
    });

    //qt5官方demo中对qgl_window实现
    connect(ui->btn_create_qglwindow,&QPushButton::clicked, this,[&](){
        QSurfaceFormat format;
        format.setSamples(16);

        TriangleWindow *w = new TriangleWindow();
        w->setFormat(format);
        w->resize(800,600);
        w->show();

        //旋转动画
        w->setAnimating(true);
    });

    //三角形
    connect(ui->btn_create_triangle,&QPushButton::clicked, this,[&](){
        SimpleTriangleWindow *w = new SimpleTriangleWindow();
        w->show();
    });

    connect(ui->btn_create_triangle_2,&QPushButton::clicked, this,[&](){
        SomeTriangleWindow *w = new SomeTriangleWindow();
        w->show();
    });

    connect(ui->btn_vao_test,&QPushButton::clicked, this,[&](){
        VaoTestWidget *w = new VaoTestWidget();
        w->show();
    });

}

MainWindow::~MainWindow() {
    delete ui;
}
