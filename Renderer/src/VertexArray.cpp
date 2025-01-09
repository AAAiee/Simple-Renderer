#include "VertexArray.h"
#include <Log.h>
#include "VertexArrayLayout.h"

VertexArray::VertexArray()
{
	GLLOGCALL(glGenVertexArrays(1, &m_RenderedID));
}

VertexArray::~VertexArray()
{
	GLLOGCALL(glDeleteVertexArrays(1, &m_RenderedID));
}

void VertexArray:: AddBuffer(const VertexBuffer& vb, const VertexArrayLayout& layout)
{
	Bind();
	vb.Bind();
	const auto& elements = layout.GetElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i]; 
		GLLOGCALL(glEnableVertexAttribArray(i));
		GLLOGCALL(glVertexAttribPointer(i, element.count, element.type,
			(element.normalized) ? GL_TRUE : GL_FALSE, layout.GetStride() ,reinterpret_cast<const void*>(offset) ));
		offset += element.count * VertextBufferElement::GetSizeOfType(element.type);
	}
}

void VertexArray::Bind() const
{
	GLLOGCALL(glBindVertexArray(m_RenderedID));
}

void VertexArray::UnBind() const
{
	GLLOGCALL(glBindVertexArray(0));
}
