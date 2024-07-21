#include "TShader.h"

TShaderContext::TShaderContext(const TVertexArrayObject* vao, const TTexture* texture)
	: m_vao(vao), m_texture(texture), m_currentVertexIndex(0)
{
}

void TShaderContext::SetVertexIndex(uint32_t index)
{
	m_currentVertexIndex = index;
}

tmath::Vec4f TShaderContext::texture(const tmath::Vec2f& uv) const
{
	return m_texture->Sample(uv);
}

TShader::~TShader()
{
}

TVertexShaderOutput::TVertexShaderOutput()
{
}

TVertexShaderOutput::~TVertexShaderOutput()
{
}

TVertexShaderOutputPrivate::TVertexShaderOutputPrivate()
	: TVertexShaderOutput()
{
}

TVertexShaderOutputPrivate TVertexShaderOutputPrivate::Lerp(const TVertexShaderOutputPrivate& other, float t) const
{
	TVertexShaderOutputPrivate res;

	res.builtin_position = this->builtin_position * (1 - t) + other.builtin_position * t;

	for (const auto& var : this->variables)
	{
		const std::string& name = var.first;

		std::visit([&](const auto& var1, const auto var2) {
			using T1 = std::decay_t<decltype(var1)>;
			using T2 = std::decay_t<decltype(var2)>;
			if constexpr (std::is_same_v<T1, T2>)
			{
				res.variables[name] = var1 * (1 - t) + var2 * t;
			}
		}, var.second, other.variables.at(name));
	}

	return res;
}