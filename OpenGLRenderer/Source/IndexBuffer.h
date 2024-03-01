#pragma once

#include "Defines.h"

class IndexBuffer
{
public:
	IndexBuffer(void* indices, u64 count);
	~IndexBuffer();

	void Bind() const;

	inline u64 GetCount() const { return m_Count; }

private:
	u32 m_OpenGLID = NULL;
	u64 m_Count = 0;
};