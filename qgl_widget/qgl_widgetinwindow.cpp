//
// Created by xlu on 2023/10/10.
//

// You may need to build the project (run Qt uic code generator) to get "ui_QGL_WidgetInWindow.h" resolved

#include "qgl_widgetinwindow.h"
#include "ui_QGL_WidgetInWindow.h"
#include <QOpenGLWidget>
#include "QGL_Widget.hpp"

QGL_WidgetInWindow::QGL_WidgetInWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::QGL_WidgetInWindow) {
    ui->setupUi(this);
    qDebug() << "QGL_WidgetInWindow init";
    QGL_Widget *gl_widget = new QGL_Widget(this);
    gl_widget->setGeometry(QRect(0,00,400,300));
    gl_widget->show();

}

QGL_WidgetInWindow::~QGL_WidgetInWindow() {
    delete ui;
}
