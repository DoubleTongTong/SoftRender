#include "TMesh.h"

TMesh::TMesh(
	TSoftRenderer& sr,
	const std::vector<Vertex>& vertices,
	const std::vector<uint32_t>& indices,
	uint32_t m_textureID)
	: m_sr(sr), m_tex(m_textureID)
{
	m_sr.GenVertexArrays(1, &m_vao);
	m_sr.GenBuffers(1, &m_vbo);
	m_sr.GenBuffers(1, &m_ebo);

	m_sr.BindVertexArray(m_vao);

	m_sr.BindBuffer(TBufferType::ArrayBuffer, m_vbo);
	m_sr.BufferData(TBufferType::ArrayBuffer, vertices.size() * sizeof(Vertex), (void*)vertices.data());
	m_sr.VertexAttribPointer(0, 3, sizeof(Vertex), offsetof(Vertex, position));
	m_sr.VertexAttribPointer(1, 3, sizeof(Vertex), offsetof(Vertex, normal));
	m_sr.VertexAttribPointer(2, 2, sizeof(Vertex), offsetof(Vertex, texCoords));

	m_sr.BindBuffer(TBufferType::ElementArrayBuffer, m_ebo);
	m_sr.BufferData(TBufferType::ElementArrayBuffer, indices.size() * sizeof(uint32_t), (void*)indices.data());
	m_indicesCount = indices.size();
}

void TMesh::Draw(const tmath::Mat4f& transform, TLambertianShader* shader)
{
	shader->modelMatrix = transform;

	m_sr.BindVertexArray(m_vao);
	m_sr.BindBuffer(TBufferType::ArrayBuffer, m_vbo);
	m_sr.BindBuffer(TBufferType::ElementArrayBuffer, m_ebo);
	m_sr.BindTexture(m_tex);

	m_sr.DrawElements(TDrawMode::Triangles, m_indicesCount, 0);
}