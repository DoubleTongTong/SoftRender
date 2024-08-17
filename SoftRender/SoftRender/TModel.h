#pragma once

#include "TNode.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include <unordered_map>

class TModel
{
public:
	TModel(TSoftRenderer& sr, const std::string path);
	void Draw(const tmath::Mat4f& transform, TLambertianShader* shader);

private:
	void LoadModel(const std::string& path);

	std::unique_ptr<TNode> ProcessNode(aiNode* node, const aiScene* scene);
	std::unique_ptr<TMesh> ProcessMesh(aiMesh* mesh, const aiScene* scene);
	uint32_t LoadMaterialTexture(aiMaterial* material, aiTextureType type, const aiScene* scene);
	TImage LoadEmbeddedTexture(const aiTexture* texture);
	TImage LoadTextureFromFile(const aiString& aiPath);

private:
	tmath::Mat4f ConvertToMatrix(const aiMatrix4x4& m);
	uint32_t CreateTexture(const TImage& img);

private:
	TSoftRenderer& m_sr;
	std::unique_ptr<TNode> m_rootNode;

	std::string m_modelDirectory;
	std::unordered_map<std::string, uint32_t> m_textureCache;
};