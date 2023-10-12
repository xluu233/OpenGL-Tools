//
// Created by xlu on 2023/10/10.
//

#ifndef OPENGL_TOOLS_QGL_WIDGETINWINDOW_H
#define OPENGL_TOOLS_QGL_WIDGETINWINDOW_H

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class QGL_WidgetInWindow; }
QT_END_NAMESPACE

class QGL_WidgetInWindow : public QMainWindow {
Q_OBJECT

public:
    explicit QGL_WidgetInWindow(QWidget *parent = nullptr);

    ~QGL_WidgetInWindow() override;

private:
    Ui::QGL_WidgetInWindow *ui;
};


#endif //OPENGL_TOOLS_QGL_WIDGETINWINDOW_H
