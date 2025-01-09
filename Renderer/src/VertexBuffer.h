#pragma once
class VertexBuffer
{
private:
	unsigned int m_RendererId;
	unsigned int m_Size;

public:
	VertexBuffer(const unsigned int& size, const float* data);


	~VertexBuffer();

	void Bind() const ;
	void UnBind() const;
};