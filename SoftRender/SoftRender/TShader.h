#pragma once

#include "TVector.h"
#include "TMatrix.h"
#include "TVertexArrayObject.h"
#include <functional>

class TShaderContext
{
public:
	TShaderContext(const TVertexArrayObject* vao);

	template<typename T>
	void GetAttribute(uint32_t location, T& out) const
	{
		const TVertexAttribBinding* binding = m_vao->GetVertexAttribBinding(location);

		uint32_t stride = binding->attribute.stride;
		uint32_t offset = stride * m_currentVertexIndex + binding->attribute.offset;

		uint8_t* buffer = (uint8_t*)binding->buffer->GetBufferData() + offset;

		memcpy(&out, buffer, sizeof(T));
	}

	void SetVertexIndex(uint32_t index);
private:
	const TVertexArrayObject* m_vao;
	uint32_t m_currentVertexIndex;
};

struct TVertexShaderOutput
{
	tmath::Vec4f position;

	bool useColor;
	tmath::Vec4f color;

	bool useUV;
	tmath::Vec2f uv;

	TVertexShaderOutput();
	virtual ~TVertexShaderOutput();
};

struct TVertexShaderOutputPrivate : public TVertexShaderOutput
{
	TVertexShaderOutputPrivate Lerp(const TVertexShaderOutputPrivate& other, float t) const;
};

struct TFragmentShaderOutput
{
	tmath::Vec4f color;
};

using FragmentShaderFunction = std::function<void(const TVertexShaderOutput&, TFragmentShaderOutput&)>;

class TShader
{
public:
	virtual ~TShader();
	virtual void VertexShader(const TShaderContext& context, TVertexShaderOutput& output) = 0;
	virtual void FragmentShader(const TVertexShaderOutput& input, TFragmentShaderOutput& output) = 0;
};
