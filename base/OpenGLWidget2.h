#pragma once

#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>
#include "Camera.h"
#include "Light.h"
#include "Model.h"
#include "Dice.h"
#include <qpainter.h>

class OpenGLWidget2 : public QOpenGLWidget, public QOpenGLExtraFunctions
{
	Q_OBJECT

public:
	OpenGLWidget2(QWidget *parent = nullptr) ;
	~OpenGLWidget2();
protected:
	virtual void initializeGL() override;
	virtual void resizeGL(int w, int h) override;
	virtual void paintGL() override;

	virtual void timerEvent(QTimerEvent *event);

private:
	QMatrix4x4 m_projection;

	Camera m_camera;
	Light m_light;
    Model* m_model;
};
