//
// Created by xlu on 2023/10/9.
//

#ifndef OPENGL_TOOLS_MAINWINDOW_H
#define OPENGL_TOOLS_MAINWINDOW_H

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

private:
    Ui::MainWindow *ui;
    QWidget *w = nullptr;

private slots:

};


#endif //OPENGL_TOOLS_MAINWINDOW_H
