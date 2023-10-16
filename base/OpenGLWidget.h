#pragma once

#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>
#include "Camera.h"
#include "Light.h"
#include "Model.h"

class OpenGLWidget : public QOpenGLWidget, public QOpenGLExtraFunctions
{
	Q_OBJECT

public:
	OpenGLWidget(QWidget *parent = nullptr);
	~OpenGLWidget();
protected:
	virtual void initializeGL() override;
	virtual void resizeGL(int w, int h) override;
	virtual void paintGL() override;

	virtual void timerEvent(QTimerEvent *event);

private:
	QMatrix4x4 m_projection;

	Camera m_camera;
	Light m_light;
	QVector<Model *> m_models;
	Model *m_lightModel;
};
