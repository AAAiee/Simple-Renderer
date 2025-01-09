#include "Log.h"
#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const unsigned int& size, const float* data)
	:m_Size(size)
{
	GLLOGCALL(glGenBuffers(1, &m_RendererId));
	GLLOGCALL(glBindBuffer(GL_ARRAY_BUFFER, m_RendererId));
	GLLOGCALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
	GLLOGCALL(glDeleteBuffers(1, &m_RendererId));
}

void VertexBuffer::Bind() const
{
	GLLOGCALL(glBindBuffer(GL_ARRAY_BUFFER, m_RendererId));
}

void VertexBuffer::UnBind() const
{
	GLLOGCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}


