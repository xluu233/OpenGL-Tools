#include "Model.h"

Model::Model()
{
}

Model::~Model()
{
}

void Model::setTexture(QOpenGLTexture *texture, int index)
{
	if (index == -1)
	{
		if (m_textures.isEmpty())
		{
			index = 0;
		}
		else
		{
			index = m_textures.keys().last() + 1;
		}
	}
	m_textures.insert(index, texture);
}

void Model::setMaterial(const Material &material, int index)
{
	if (index == -1)
	{
		if (m_materials.isEmpty())
		{
			index = 0;
		}
		else
		{
			index = m_materials.keys().last() + 1;
		}
	}
	m_materials.insert(index, material);
}

QMatrix4x4 Model::model()
{
	QMatrix4x4 _mat;
	_mat.setToIdentity();
	_mat.translate(m_pos);
	_mat.rotate(m_rotate.x(), 1, 0, 0);
	_mat.rotate(m_rotate.y(), 0, 1, 0);
	_mat.rotate(m_rotate.z(), 0, 0, 1);
	_mat.scale(m_scale);
	return _mat;
}

void Model::init()
{
}

void Model::update()
{
}

void Model::paint()
{
}
