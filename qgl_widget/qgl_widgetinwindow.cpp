//
// Created by xlu on 2023/10/10.
//

// You may need to build the project (run Qt uic code generator) to get "ui_QGL_WidgetInWindow.h" resolved

#include "qgl_widgetinwindow.h"
#include "ui_QGL_WidgetInWindow.h"
#include <QOpenGLWidget>
#include "SimpleQGLWidget.h"

QGL_WidgetInWindow::QGL_WidgetInWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::QGL_WidgetInWindow) {
    ui->setupUi(this);

    SimpleQGLWidget *gl_widget = new SimpleQGLWidget(this);
    gl_widget->setGeometry(QRect(0,00,400,300));
    gl_widget->show();
    //指针创建的在这里不能delete, 为什么show不是阻塞操作？
    //delete gl_widget;

    //error!
//    SimpleQGLWidget w();
//    w.show();

}

QGL_WidgetInWindow::~QGL_WidgetInWindow() {
    delete ui;
}
