#pragma once
#include "TMatrix.h"
#include "TSoftRenderer.h"
#include "TLambertianShader.h"

#include <vector>

class TMesh
{
public:
	struct Vertex
	{
		tmath::Vec3f position;
		tmath::Vec3f normal;
		tmath::Vec2f texCoords;
	};

	TMesh(
		TSoftRenderer& sr,
		const std::vector<Vertex>& vertices,
		const std::vector<uint32_t>& indices,
		uint32_t m_textureID);

	void Draw(const tmath::Mat4f& transform, TLambertianShader* shader);
private:
	uint32_t m_vao;
	uint32_t m_vbo;
	uint32_t m_ebo;
	uint32_t m_tex;
	uint32_t m_indicesCount;

	TSoftRenderer& m_sr;
};