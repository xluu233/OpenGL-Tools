#pragma once

#include <QObject>
#include <QVector3D>
#include <QColor>

class Light : public QObject
{
	Q_OBJECT

public:
	Light();
	~Light();
public:
	void setPos(const QVector3D &pos) { m_pos = pos; }
	QVector3D pos() { return m_pos; }

	void setColor(const QColor &color)  { m_color = color; }
	QColor color() { return m_color; }
protected:
	QVector3D m_pos{ 0,0,0 };
	QColor m_color;
};
