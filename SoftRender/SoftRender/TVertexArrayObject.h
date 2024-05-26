#pragma once

#include "TBufferObject.h"
#include <unordered_map>


enum class TAttributeType
{
	Float
};

struct TVertexAttribute
{
	TAttributeType type;
	uint32_t count;
	uint32_t stride;
	uint32_t offset;

	TVertexAttribute();
	TVertexAttribute(TAttributeType type, uint32_t count, uint32_t stride, uint32_t offset);
};

struct TVertexAttribBinding
{
	TBufferObject* buffer;
	TVertexAttribute attribute;

	TVertexAttribBinding();
	TVertexAttribBinding(TBufferObject* buffer, TVertexAttribute attribute);
};

class TVertexArrayObject
{
public:
	TVertexArrayObject(uint32_t id);

	void AddVertexAttribBinding(uint32_t index, TBufferObject* buffer, const TVertexAttribute& attribute);
	const TVertexAttribBinding* GetVertexAttribBinding(uint32_t index) const;

	/* Debug */
	void Print() const;
private:
	uint32_t m_id;
	std::unordered_map<uint32_t, TVertexAttribBinding> m_bindings;
};