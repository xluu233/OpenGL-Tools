#pragma once
#include "../base/GLHelper.h"

class SkyBox
{
public:
	explicit SkyBox(QOpenGLExtraFunctions* func);
	~SkyBox();
	void draw(QOpenGLShaderProgram *program,const QMatrix4x4& model, const QMatrix4x4& view, const QMatrix4x4& project);

private:
	void initBuffer();
	int initShader();
	void initTexture();

private:
    QOpenGLExtraFunctions*	  m_func;
	QOpenGLBuffer m_arrayBuf;
	QOpenGLShader m_vertexShader;
	QOpenGLShader m_fragmentShader;

	quint32		  m_cubeTexture;
	quint32		  m_vao;
	int			  m_vertexCount = 0;
};
