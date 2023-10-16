#include "OpenGLWidget.h"
#include "LightModel.h"
#include "Dice.h"
#include <QDebug>
#include <QOpenGLDebugLogger>
#include <limits>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QPainter>


OpenGLWidget::OpenGLWidget(QWidget *parent)
	: QOpenGLWidget(parent)
{
    //设置采样率
	auto newFormat = this->format();
	newFormat.setSamples(16);
	this->setFormat(newFormat);

    setMinimumSize(1200,800);
	startTimer(1000 / 60);

	m_camera.move(-6, 0, 3);
	m_camera.look(0, 30, 0);
	m_camera.update();

	m_light.setPos({ 10, 3 , 0 });
	m_light.setColor(QColor(120, 34, 65));

	installEventFilter(&m_camera);
}

OpenGLWidget::~OpenGLWidget()
{
}

void OpenGLWidget::initializeGL()
{
	initializeOpenGLFunctions();
	//glClearColor(0, 0.5, 0.7, 1);
	//auto _color = m_light.color() * 0.1;
	//glClearColor(_color.x(), _color.y(), _color.z(), 1);
	glClearColor(0, 0, 0, 1);

	for (int i = 0; i < 3; ++i)
	{
		auto _dice = new Dice();
		_dice->setCamera(&m_camera);
		_dice->setLight(&m_light);
		_dice->setPos({ 0, i * 3.f, 0 });
		_dice->init();
		m_models << _dice;
	}


	m_lightModel = new LightModel();
	m_lightModel->setCamera(&m_camera);
	m_lightModel->setLight(&m_light);
	m_lightModel->setPos(m_light.pos());
	//m_lightModel->setScale(0.1);
	m_lightModel->init();
}

void OpenGLWidget::resizeGL(int w, int h)
{
	m_projection.setToIdentity();
	m_projection.perspective(60, (float)w/h, 0.001, 1000);
	for (auto dice : m_models)
	{
		dice->setProjection(m_projection);
	}
	m_lightModel->setProjection(m_projection);
}

void OpenGLWidget::paintGL()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	for (auto dice : m_models)
	{
		dice->paint();
	}

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	m_lightModel->paint();

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	QPainter _painter(this);
	auto _rect = this->rect();
	_painter.setPen(Qt::green);
	_painter.drawLine(_rect.center() + QPoint{ 0, 5 }, _rect.center() + QPoint{ 0, 15 });
	_painter.drawLine(_rect.center() + QPoint{ 0, -5 }, _rect.center() + QPoint{ 0, -15 });
	_painter.drawLine(_rect.center() + QPoint{ 5, 0 }, _rect.center() + QPoint{ 15, 0 });
	_painter.drawLine(_rect.center() + QPoint{ -5, 0 }, _rect.center() + QPoint{ -15, 0 });

	_painter.drawText(QPoint{ 5, 15 }, QString("摄像机位置: (%1, %2, %3)")
		.arg(m_camera.pos().x(), 0, 'f', 3).arg(m_camera.pos().y(), 0, 'f', 3).arg(m_camera.pos().z(), 0, 'f', 3));
	_painter.drawText(QPoint{ 5, 30 }, QString("摄像机角度: (%1, %2, %3)")
		.arg(m_camera.yaw(), 0, 'f', 3).arg(m_camera.pitch(), 0, 'f', 3).arg(m_camera.roll(), 0, 'f', 3));
}

void OpenGLWidget::timerEvent(QTimerEvent *event)
{
	m_camera.update();
	float _speed = 0.1;
	for (auto dice : m_models)
	{
		float _y = dice->rotate().y() + _speed;
		if (_y >= 360)
			_y -= 360;
		dice->setRotate({ 0, _y, 0 });
		_speed += 0.1;
	}
	//auto _h = m_light.color().hsvHue() + 1;
	//if (_h >= 360)
	//	_h -= 360;
	//m_light.setColor(QColor::fromHsv(_h, 255, 255));

	m_lightModel->setPos(m_light.pos());
	repaint();
}
