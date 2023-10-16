#include "Camera.h"

#include <QKeyEvent>
#include <QMouseEvent>
#include <QOpenGLWidget>

Camera::Camera(QObject *parent)
	: QObject(parent)
{
}

Camera::~Camera()
{
}

void Camera::look(float yaw, float pitch, float roll)
{
	m_yaw += yaw;
	while (m_yaw >= 360)
		m_yaw -= 360;
	while (m_yaw < 0)
		m_yaw += 360;
	m_pitch += pitch;
	if (m_pitch > 89)
		m_pitch = 89;
	if (m_pitch < -89)
		m_pitch = -89;
	{
		QVector3D _front{ 0,0,-1 };
		QMatrix4x4 _mat;
		_mat.setToIdentity();
		_mat.rotate(m_pitch, 1, 0, 0);
		_mat.rotate(m_yaw, 0, 1, 0);
		m_front = _front * _mat;
	}
	m_roll += roll;
	while (m_roll >= 360)
		m_roll -= 360;
	while (m_roll < 0)
		m_roll += 360;
	{
		QVector3D _up{ 0,1,0 };
		QMatrix4x4 _mat;
		_mat.setToIdentity();
		_mat.rotate(m_roll, 0, 0, 1);
		m_up = _up * _mat;
	}
}

void Camera::move(float x, float y, float z)
{
	auto _right = QVector3D::crossProduct(m_front, m_up).normalized();
	auto _front = QVector3D::crossProduct(m_up, _right).normalized();
	m_pos += _front * x;
	m_pos += _right * y;
	m_pos += m_up * z;
}

void Camera::resetLook()
{
	m_front = { 0,0,-1 };
}

void Camera::resetRotate()
{
	m_up = { 0,1,0 };
}

void Camera::resetMove()
{
	m_pos = { 0,0,0 };
}

void Camera::resetAll()
{
	resetLook();
	resetRotate();
	resetMove();
}

void Camera::update()
{
	auto _move = m_move.normalized() * m_moveSpeed;
	move(_move.x(), _move.y(), _move.z());

	m_view.setToIdentity();
	m_view.lookAt(m_pos, m_pos + m_front, m_up);
}

bool Camera::eventFilter(QObject *obj, QEvent *ev)
{
	auto _widget = qobject_cast<QOpenGLWidget *>(obj);
	if (_widget)
	{
		if (ev->type() == QEvent::KeyPress)
		{
			auto event = static_cast<QKeyEvent *>(ev);
			if (event->key() == Qt::Key_Escape)
			{
				_widget->setMouseTracking(false);
				_widget->setCursor(Qt::ArrowCursor);
			}
			else if (event->key() == Qt::Key_W)
			{
				m_move.setX(1);
			}
			else if (event->key() == Qt::Key_S)
			{
				m_move.setX(-1);
			}
			else if (event->key() == Qt::Key_A)
			{
				m_move.setY(-1);
			}
			else if (event->key() == Qt::Key_D)
			{
				m_move.setY(1);
			}
			else if (event->key() == Qt::Key_Space)
			{
				m_move.setZ(1);
			}
			else if (event->key() == Qt::Key_C)
			{
				m_move.setZ(-1);
			}
		}
		else if (ev->type() == QEvent::KeyRelease)
		{
			auto event = static_cast<QKeyEvent *>(ev);
			if (event->key() == Qt::Key_W)
			{
				m_move.setX(0);
			}
			else if (event->key() == Qt::Key_S)
			{
				m_move.setX(0);
			}
			else if (event->key() == Qt::Key_A)
			{
				m_move.setY(0);
			}
			else if (event->key() == Qt::Key_D)
			{
				m_move.setY(0);
			}
			else if (event->key() == Qt::Key_Space)
			{
				m_move.setZ(0);
			}
			else if (event->key() == Qt::Key_C)
			{
				m_move.setZ(0);
			}
		}
		else if (ev->type() == QEvent::MouseButtonPress)
		{
			auto _lastPos = _widget->mapToGlobal(_widget->rect().center());
			QCursor::setPos(_lastPos);

			_widget->setMouseTracking(true);
			_widget->setCursor(Qt::BlankCursor);
		}
		else if (ev->type() == QEvent::MouseMove)
		{
			auto event = static_cast<QMouseEvent *>(ev);
			auto _lastPos = _widget->mapToGlobal(_widget->rect().center());
			QCursor::setPos(_lastPos);

			auto _move = event->globalPos() - _lastPos;
			look(_move.x() * m_lookSpeed, _move.y() * m_lookSpeed, 0);
		}
		else if (ev->type() == QEvent::Leave)
		{
			_widget->setMouseTracking(false);
			_widget->setCursor(Qt::ArrowCursor);
		}
	}
	return false;
}
