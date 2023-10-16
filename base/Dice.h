#pragma once

#include "Model.h"

class Dice : public Model
{
public:
	Dice();
	~Dice();
public:
	virtual void init() override;
	virtual void update() override;
	virtual void paint() override;
private:
	float *m_vertexBuffer = nullptr;
	int m_vertexCount = 0;
};
