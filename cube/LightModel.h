#pragma once


#include "../base/Model.h"

class LightModel : public Model
{
public:
	LightModel();
	~LightModel();
public:
	virtual void init() override;
	virtual void update() override;
	virtual void paint() override;
private:
	float *m_vertexBuffer = nullptr;
	int m_vertexCount = 0;
	int m_row = 0;
	int m_col = 0;
};

