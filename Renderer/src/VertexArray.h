#pragma once
#include<VertexBuffer.h>
class VertexArrayLayout;


class VertexArray
{
private:
	unsigned int m_RenderedID;

public:
	VertexArray();
	~VertexArray();
	

	void AddBuffer(const VertexBuffer& vb, const VertexArrayLayout& layout);
	void Bind() const;
	void UnBind() const;
};