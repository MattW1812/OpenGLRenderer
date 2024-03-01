#pragma once

#include "Defines.h"

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void Bind() const;

private:
	u32 m_ID = NULL;
};