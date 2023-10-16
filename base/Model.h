#pragma once

#include <QMatrix4x4>

#include <QOpenGLExtraFunctions>
#include <QOpenGLVertexArrayObject> 
#include <QOpenGLBuffer> 
#include <QOpenGLShaderProgram> 
#include <QOpenGLTexture>
#include "Camera.h"
#include "Light.h"

struct Vertex
{
	QVector3D pos;      //顶点数据
	QVector2D texture;  //纹理坐标
	QVector3D normal;   //法向量
};

static const int VertexFloatCount = 8;

struct Material
{
	float ambient = 1;          //环境光
	float diffuse = 0;          //漫反射
	float specular = 0;         //镜面反射
	float shininess = 16;       //最终计算出来的镜面反射的效果。值越大，光斑越明显。
};


class Model : public QOpenGLExtraFunctions
{
public:
	Model();
	~Model();
public:
	void setScale(float val) { m_scale = val; }
	void setRotate(const QVector3D &rotate) { m_rotate = rotate; }
	void setPos(const QVector3D &pos) { m_pos = pos; }
	float scale() { return m_scale; }
	QVector3D rotate() { return m_rotate; }
	QVector3D pos() { return m_pos; }
public:
	void setVertices(const QVector<Vertex> &vertices) { m_vertices = vertices; }
	void setTexture(QOpenGLTexture *texture, int index = -1);
	void setShaderProgram(QOpenGLShaderProgram *program) { m_program = program; }
	void setMaterial(const Material &material, int index  = -1);
public:
	void setCamera(Camera *camera) { m_camera = camera; }
	void setProjection(const QMatrix4x4 &projection) { m_projection = projection; }
	void setLight(Light *light) { m_light = light; }
public:
	QMatrix4x4 model();
public:
	virtual void init();
	virtual void update();
	virtual void paint();
protected:
	QVector3D m_pos{ 0,0,0 };
	QVector3D m_rotate{ 0,0,0 };
	float m_scale = 1;

	QVector<Vertex> m_vertices;
	QMap<int, QOpenGLTexture*> m_textures;
	QMap<int, Material> m_materials;

	QOpenGLVertexArrayObject m_vao;
	QOpenGLBuffer m_vbo;
	QOpenGLShaderProgram *m_program = nullptr;

	QMatrix4x4 m_projection;
	Camera *m_camera = nullptr;
	Light *m_light = nullptr;
};
