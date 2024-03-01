#pragma once

#include "Defines.h"


class VertexBuffer
{
public:
	VertexBuffer(void* vertices, u64 size);
	~VertexBuffer();

	void Bind();

private:
	u32 m_OpenGLID = NULL;
};