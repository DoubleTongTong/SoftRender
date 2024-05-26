#include "TVertexArrayObject.h"
#include <assert.h>
#include <iostream>

TVertexAttribute::TVertexAttribute()
	: type(TAttributeType::Float),
	  count(0), stride(0), offset(0)
{
}

TVertexAttribute::TVertexAttribute(TAttributeType type, uint32_t count, uint32_t stride, uint32_t offset)
	: type(type), count(count), stride(stride), offset(offset)
{
}

TVertexAttribBinding::TVertexAttribBinding()
	: buffer(NULL), attribute()
{
}

TVertexAttribBinding::TVertexAttribBinding(TBufferObject* buffer, TVertexAttribute attribute)
	: buffer(buffer), attribute(attribute)
{
}

TVertexArrayObject::TVertexArrayObject(uint32_t id)
	: m_id(id)
{
}

void TVertexArrayObject::AddVertexAttribBinding(uint32_t index, TBufferObject* buffer, const TVertexAttribute& attribute)
{
	m_bindings[index] = TVertexAttribBinding(buffer, attribute);
}

const TVertexAttribBinding* TVertexArrayObject::GetVertexAttribBinding(uint32_t index) const
{
	auto it = m_bindings.find(index);
	assert(it != m_bindings.end());

	return &(it->second);
}

void TVertexArrayObject::Print() const
{
	std::cout << "VertexArray ID: " << m_id << "\n";
	std::cout << "----------------------------------------\n";
	for (auto it = m_bindings.begin(); it != m_bindings.end(); it++)
	{
		std::cout << "  Attrib Index: " << it->first << "\n";
		std::cout << "  Type: " << (int)it->second.attribute.type << "\n";
		std::cout << "  Count: " << it->second.attribute.count << "\n";
		std::cout << "  Stride: " << it->second.attribute.stride << "\n";
		std::cout << "  Offset: " << it->second.attribute.offset << "\n";
		std::cout << "  Bound Buffer: ";
		it->second.buffer->Print();
		std::cout << "----------------------------------------\n";
	}
}