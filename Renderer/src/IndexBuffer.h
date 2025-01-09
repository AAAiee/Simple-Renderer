#pragma once
class IndexBuffer
{
private:
	unsigned int m_RendererId;
	unsigned int m_Count;

public:

	IndexBuffer(const unsigned int& count, const unsigned int* data);
	~IndexBuffer();

	void Bind() const;
	void UnBind() const;

	inline unsigned int GetCount() const { return m_Count; }
};