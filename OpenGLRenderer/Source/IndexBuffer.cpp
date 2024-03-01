#include "IndexBuffer.h"

#include "GL/glew.h"

IndexBuffer::IndexBuffer(void* indices, u64 count)
	:m_Count(count)
{
	glGenBuffers(1, &m_OpenGLID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_OpenGLID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(u32), indices, GL_STATIC_DRAW);  // Only 32-bit indices for now
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &m_OpenGLID);
}

void IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_OpenGLID);
}
