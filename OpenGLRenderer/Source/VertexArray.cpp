#include "VertexArray.h"

#include <GL/glew.h>

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_ID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_ID);
}

void VertexArray::Bind() const
{
	glBindVertexArray(m_ID);
}
