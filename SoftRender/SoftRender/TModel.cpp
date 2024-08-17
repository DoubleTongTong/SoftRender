#include "TModel.h"
#include <iostream>
#include <filesystem>

TModel::TModel(TSoftRenderer& sr, const std::string path)
	: m_sr(sr)
{
	LoadModel(path);
}

void TModel::LoadModel(const std::string& path)
{
	std::filesystem::path filePath = std::filesystem::absolute(path);
	m_modelDirectory = filePath.parent_path().string();

	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(
		path,
		aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cerr << "Error: " << importer.GetErrorString() << std::endl;
		assert(0);
		return;
	}

	m_rootNode = ProcessNode(scene->mRootNode, scene);
}

void TModel::Draw(const tmath::Mat4f& transform, TLambertianShader* shader)
{
	m_rootNode->Draw(transform, shader);
}

std::unique_ptr<TNode> TModel::ProcessNode(aiNode* node, const aiScene* scene)
{
	std::unique_ptr<TNode> tNode = std::make_unique<TNode>(ConvertToMatrix(node->mTransformation));

	for (uint32_t i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		tNode->AddMesh(ProcessMesh(mesh, scene));
	}

	for (uint32_t i = 0; i < node->mNumChildren; i++)
	{
		tNode->AddChild(ProcessNode(node->mChildren[i], scene));
	}

	return tNode;
}

std::unique_ptr<TMesh> TModel::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<TMesh::Vertex> vertices;
	std::vector<uint32_t> indices;
	uint32_t textureID = 0;

	for (uint32_t i = 0; i < mesh->mNumVertices; i++)
	{
		TMesh::Vertex vertex;
		vertex.position = tmath::Vec3f(
			mesh->mVertices[i].x,
			mesh->mVertices[i].y,
			mesh->mVertices[i].z
		);
		vertex.normal = tmath::Vec3f(
			mesh->mNormals[i].x,
			mesh->mNormals[i].y,
			mesh->mNormals[i].z
		);

		if (mesh->mTextureCoords[0])
		{
			vertex.texCoords = tmath::Vec2f(
				mesh->mTextureCoords[0][i].x,
				mesh->mTextureCoords[0][i].y
			);
		}
		else
		{
			vertex.texCoords = tmath::Vec2f(0, 0);
		}

		vertices.push_back(vertex);
	}

	for (uint32_t i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (uint32_t j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		textureID = LoadMaterialTexture(material, aiTextureType_DIFFUSE, scene);
	}

	return std::make_unique<TMesh>(m_sr, vertices, indices, textureID);
}

uint32_t TModel::LoadMaterialTexture(aiMaterial* material, aiTextureType type, const aiScene* scene)
{
	uint32_t textureID = 0;
	aiString aiPath;

	if (material->Get(AI_MATKEY_TEXTURE(type, 0), aiPath) == AI_SUCCESS)
	{
		std::string pathKey = aiPath.C_Str();
		if (m_textureCache.find(pathKey) != m_textureCache.end())
			return m_textureCache[pathKey];

		TImage img;
		const aiTexture* texture = scene->GetEmbeddedTexture(aiPath.C_Str());
		if (texture)
			img = LoadEmbeddedTexture(texture);
		else
			img = LoadTextureFromFile(aiPath);

		textureID = CreateTexture(img);

		m_textureCache[pathKey] = textureID;
	}

	return textureID;
}

TImage TModel::LoadEmbeddedTexture(const aiTexture* texture)
{
	uint32_t size = 0;
	if (texture->mHeight == 0)
		size = texture->mWidth;
	else
		size = texture->mWidth * texture->mHeight;

	return TImage::LoadFromMemoryBuffer((unsigned char*)texture->pcData, size);
}

TImage TModel::LoadTextureFromFile(const aiString& aiPath)
{
	std::filesystem::path texturePath = std::filesystem::path(m_modelDirectory).append(aiPath.C_Str());
	return TImage::LoadFromFile(texturePath.string().c_str());
}

uint32_t TModel::CreateTexture(const TImage& img)
{
	uint32_t textureID;
	m_sr.GenTextures(1, &textureID);
	m_sr.BindTexture(textureID);

	m_sr.TexParameter(TTextureParam::WrapS, (int)TTextureWrapMode::Repeat);
	m_sr.TexParameter(TTextureParam::WrapT, (int)TTextureWrapMode::Repeat);
	m_sr.TexParameter(TTextureParam::Filter, (int)TTextureFilterMode::Linear);

	m_sr.TexImage2D(img.GetWidth(), img.GetHeight(), img.GetData());

	return textureID;
}

tmath::Mat4f TModel::ConvertToMatrix(const aiMatrix4x4& m)
{
	return tmath::Mat4f({
		m.a1, m.b1, m.c1, m.d1,
		m.a2, m.b2, m.c2, m.d2,
		m.a3, m.b3, m.c3, m.d3,
		m.a4, m.b4, m.c4, m.d4,
		});
}