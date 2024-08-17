#pragma once
#include "TMesh.h"
#include <memory>

class TNode
{
public:
	TNode(const tmath::Mat4f& transformMatrix);

	void AddMesh(std::unique_ptr<TMesh> mesh);
	void AddChild(std::unique_ptr<TNode> child);

	void Draw(const tmath::Mat4f& transform, TLambertianShader* shader);

private:
	tmath::Mat4f m_localMatrix;

	std::vector<std::unique_ptr<TMesh>> m_meshes;
	std::vector<std::unique_ptr<TNode>> m_children;
};