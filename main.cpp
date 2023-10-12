#include <QApplication>
#include <QPushButton>
#include <iostream>
#include "mainwindow.h"
#include "GLFW/glfw3.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();
    return QApplication::exec();
}
