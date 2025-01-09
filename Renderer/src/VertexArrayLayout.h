#pragma once

#include <vector>
#include "Log.h"

struct VertextBufferElement
{
	unsigned int type;
	unsigned int count;
	bool normalized; 

	static unsigned int GetSizeOfType(unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT: return 4;
		case GL_UNSIGNED_INT: return 4;
		case GL_UNSIGNED_BYTE: return 1;
		}
		ASSERT(false);
		return 0;
	}
};
class VertexArrayLayout
{

private:
	std::vector<VertextBufferElement> m_Elements;
	unsigned int m_Stride;
	

public:
	VertexArrayLayout()
		:m_Stride(0) {}


	~VertexArrayLayout() = default;

	inline unsigned int GetStride() const { return m_Stride; }
	inline const std::vector<VertextBufferElement>& GetElements() const { return m_Elements; }

	template<typename T> 
	void Push(unsigned int count)
	{
		static_assert(false);
	}

	template<>
	void Push<float>(unsigned int count)
	{
		m_Elements.push_back({ GL_FLOAT, count, false});
		m_Stride += VertextBufferElement::GetSizeOfType(GL_FLOAT) * count;
	}


	template<>
	void Push<unsigned int >(unsigned int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_INT, count, false });
		m_Stride += VertextBufferElement::GetSizeOfType(GL_UNSIGNED_INT) * count ;
	}

	template<>
	void Push<unsigned char >(unsigned int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_BYTE, count, true });
		m_Stride += VertextBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE) * count;
	}
};

