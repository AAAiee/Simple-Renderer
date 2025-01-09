#include "IndexBuffer.h"
#include "Log.h"

IndexBuffer::IndexBuffer(const unsigned int& count, const unsigned int* data)
	:m_Count(count)
{
	GLLOGCALL(glGenBuffers(1, &m_RendererId));
	GLLOGCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId));
	GLLOGCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer()
{
	GLLOGCALL(glDeleteBuffers(1, &m_RendererId));
}

void IndexBuffer::Bind() const
{
	GLLOGCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId));
}

void IndexBuffer::UnBind() const
{
	GLLOGCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}


