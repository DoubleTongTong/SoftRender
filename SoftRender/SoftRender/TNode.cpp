#include "TNode.h"

TNode::TNode(const tmath::Mat4f& transformMatrix)
	: m_localMatrix(transformMatrix)
{
}

void TNode::AddMesh(std::unique_ptr<TMesh> mesh)
{
	m_meshes.push_back(std::move(mesh));
}

void TNode::AddChild(std::unique_ptr<TNode> child)
{
	m_children.push_back(std::move(child));
}

void TNode::Draw(const tmath::Mat4f& transform, TLambertianShader* shader)
{
	tmath::Mat4f finalTransform = transform * m_localMatrix;
	for (auto& mesh : m_meshes)
		mesh->Draw(finalTransform, shader);

	for (auto& child : m_children)
		child->Draw(finalTransform, shader);
}
