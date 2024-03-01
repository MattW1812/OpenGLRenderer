#include "VertexBuffer.h"

#include "GL/glew.h"

VertexBuffer::VertexBuffer(void* vertices, u64 size)
{
	glGenBuffers(1, &m_OpenGLID);
	glBindBuffer(GL_ARRAY_BUFFER, m_OpenGLID);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_OpenGLID);
}

void VertexBuffer::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_OpenGLID);
}
