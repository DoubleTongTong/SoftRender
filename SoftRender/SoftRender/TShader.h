#pragma once

#include "TVector.h"
#include "TMatrix.h"
#include "TVertexArrayObject.h"
#include "TTexture.h"
#include <functional>
#include <variant>
#include <unordered_map>

class TShaderContext
{
public:
	TShaderContext(const TVertexArrayObject* vao, const TTexture* texture);

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

	tmath::Vec4f texture(const tmath::Vec2f& uv) const;
private:
	const TVertexArrayObject* m_vao;
	const TTexture* m_texture;
	uint32_t m_currentVertexIndex;
};

using TShaderVariable = std::variant<tmath::Vec2f, tmath::Vec3f, tmath::Vec4f>;
struct TVertexShaderOutput
{
	tmath::Vec4f builtin_position;
	std::unordered_map<std::string, TShaderVariable> variables;

	TVertexShaderOutput();
	virtual ~TVertexShaderOutput();
};

struct TVertexShaderOutputPrivate : public TVertexShaderOutput
{
	float invW;

	TVertexShaderOutputPrivate();
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
	virtual void FragmentShader(
		const TShaderContext& context,
		const TVertexShaderOutput& input,
		TFragmentShaderOutput& output) = 0;
};
