#pragma once

#include "TRasterizer.h"
#include "TBufferObject.h"
#include "TVertexArrayObject.h"
#include "TTexture.h"
#include "TShader.h"
#include <unordered_map>
#include <queue>

class TSoftRenderer
{
public:
	TSoftRenderer();
	void SetRasterizer(uint32_t* pBits, int width, int height);
	int GetRenderWidth();
	int GetRenderHeight();

public:
	void SetBlend(bool enable);
	void SetTexture(const TImage* texture);
	void SetSampleMode(TSampleMode mode);
	void SetWrapMode(TWrapMode mode);

	void ClearColor(TRGBA color);
	void ClearDepth(float depth);

	void Enable(TEnableCap cap);
	void CullFace(TCullFace mode);
	void FrontFace(TFrontFace mode);

	void DepthFunc(TDepthFunc func);

	void GenBuffers(uint32_t n, uint32_t* buffers);
	void DeleteBuffers(uint32_t n, uint32_t* buffers);
	void GenVertexArrays(uint32_t n, uint32_t* arrays);
	void DeleteVertexArrays(uint32_t n, uint32_t* arrays);

	void BindBuffer(TBufferType target, uint32_t buffer);
	void BufferData(TBufferType target, uint32_t size, void* data);
	void BindVertexArray(uint32_t array);

	void GenTextures(uint32_t n, uint32_t* textures);
	void BindTexture(uint32_t texture);
	void TexImage2D(int width, int height, void* data);
	void TexParameter(TTextureParam pname, int param);
	void DeleteTextures(uint32_t n, uint32_t* textures);
	/**
	 * 简化处理，该函数默认所有数据类型为 `float`。
	 */
	void VertexAttribPointer(
		uint32_t index,
		uint32_t count,
#if 0
		TAttributeType type,
#endif
		uint32_t stride,
		uint32_t offset);

	/* Debug */
	void PrintVAO(uint32_t vao);

	void UseProgram(TShader* shader);

	/**
	 * 简化处理，该函数默认所有数据类型为 `uint32`。
	 */
	void DrawElements(
		TDrawMode mode,
		uint32_t size,
#if 0
		TIndexDataType type,
#endif
		uint32_t offset);

private:
	TRenderState m_state;
	TRasterizer  m_rz;

	/* VBO */
	std::unordered_map<uint32_t, TBufferObject*> m_bufferMap;
	std::queue<uint32_t> m_freeBufferIds;
	uint32_t m_nextBufferId;

	/* VAO */
	std::unordered_map<uint32_t, TVertexArrayObject*> m_vaoMap;
	std::queue<uint32_t> m_freeVaoIds;
	uint32_t m_nextVaoId;

	/* Texture */
	std::unordered_map<uint32_t, TTexture*> m_textureMap;
	std::queue<uint32_t> m_freeTextureIds;
	uint32_t m_nextTextureId;

	/* Bounded */
	TVertexArrayObject* m_currentVertexArray;
	TBufferObject*      m_currentArrayBuffer;
	TBufferObject*      m_currentElementBuffer;
	TTexture*           m_currentTexture;

	/* Shader */
	TShader* m_currentShader;

	tmath::Mat4f m_screenMatrix;
private:
	uint32_t AllocateBufferId();
	uint32_t AllocateVaoId();
	uint32_t AllocateTextureId();

	int GetPrimitiveCount(TDrawMode mode);

	void SutherlandHodgmanClipTriangle(
		const TVertexShaderOutputPrivate vertexOutputs[3],
		std::vector<TVertexShaderOutputPrivate>& clipped);

	void ClipPolygonAgainstBoundary(
		const std::vector<TVertexShaderOutputPrivate>& vertices,
		std::vector<TVertexShaderOutputPrivate>& outVertices,
		const tmath::Vec4f& boundary);

	bool ShouldCullTriangle(
		const TVertexShaderOutputPrivate& v1,
		const TVertexShaderOutputPrivate& v2,
		const TVertexShaderOutputPrivate& v3
	);

	bool ShouldClipping(
		const TVertexShaderOutputPrivate vertexOutputs[3]);

public:
	TSoftRenderer(TSoftRenderer&& other) noexcept = default;
	TSoftRenderer& operator=(TSoftRenderer&& other) = default;

	TSoftRenderer(const TSoftRenderer&) = delete;
	TSoftRenderer& operator=(const TSoftRenderer&) = delete;

public:
	void SetPixel(int x, int y, TRGBA color);
	void DrawLine(int x1, int y1, TRGBA color1, int x2, int y2, TRGBA color2);
	void DrawTriangle(const tmath::Point2i& p1, const tmath::Point2i& p2, const tmath::Point2i& p3,
		TRGBA color1, TRGBA color2, TRGBA color3);
	void DrawTriangle(const tmath::Point2i& p1, const tmath::Point2i& p2, const tmath::Point2i& p3,
		const tmath::UV2f& uv1, const tmath::UV2f& uv2, const tmath::UV2f& uv3);
	void DrawImage(const TImage& image, int startX, int startY);
};