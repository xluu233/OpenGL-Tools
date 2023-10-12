//
// Created by xlu on 2023/10/11.
//

#ifndef OPENGL_TOOLS_QGL_WINDOW_H
#define OPENGL_TOOLS_QGL_WINDOW_H

#include <QWindow>
#include <QOpenGLFunctions>

QT_BEGIN_NAMESPACE
class QPainter;
class QOpenGLContext;
class QOpenGLPaintDevice;
QT_END_NAMESPACE

/**
 * Qt5中的例程：openglwindow，是采用继承QWindow类和QOpenGLFunctions类，来实现OpenGL窗口的显示和渲染的，
 * 在新版本的Qt中，可采用继承QOpenGLWindow类和QOpenGLFunctions类来实现。
 */
class QGL_Window : public QWindow, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit QGL_Window(QWindow* parent = nullptr);

    ~QGL_Window();

    virtual void render(QPainter *painter);
    virtual void render();
    virtual void initialize();

    void setAnimating(bool animating);

    void log(const QString& str)
    {
        qDebug() << "[QGL_Window]" << str;
    }

public slots:
    void renderLater();
    void renderNow();

protected:
    bool event(QEvent *event) override;
    void exposeEvent(QExposeEvent *event) override;

private:
    bool m_animating = false;
    QOpenGLContext *m_context = nullptr;
    QOpenGLPaintDevice *m_device = nullptr;

};

#endif //OPENGL_TOOLS_QGL_WINDOW_H
