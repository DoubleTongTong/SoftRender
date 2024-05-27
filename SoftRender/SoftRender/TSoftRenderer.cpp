#include "TSoftRenderer.h"

TSoftRenderer::TSoftRenderer()
	: m_nextBufferId(0),
	  m_nextVaoId(0),
	  m_currentArrayBuffer(NULL),
	  m_currentElementBuffer(NULL),
	  m_currentVertexArray(NULL)
{
}

void TSoftRenderer::SetRasterizer(uint32_t* pBits, int width, int height)
{
	m_rz = TRasterizer(pBits, width, height, &m_state);
	m_screenMatrix = tmath::ScreenMatrix<float>(width, height);
}

int TSoftRenderer::GetRenderWidth()
{
	return m_rz.GetWidth();
}

int TSoftRenderer::GetRenderHeight()
{
	return m_rz.GetHeight();
}

void TSoftRenderer::Clear(TRGBA color)
{
	m_rz.Clear(color);
}

void TSoftRenderer::SetPixel(int x, int y, TRGBA color)
{
	m_rz.SetPixel(x, y, color);
}

void TSoftRenderer::DrawLine(int x1, int y1, TRGBA color1, int x2, int y2, TRGBA color2)
{
	m_rz.DrawLine(x1, y1, color1, x2, y2, color2);
}

void TSoftRenderer::DrawTriangle(const tmath::Point2i& p1, const tmath::Point2i& p2, const tmath::Point2i& p3,
	TRGBA color1, TRGBA color2, TRGBA color3)
{
	m_rz.DrawTriangle(p1, p2, p3, color1, color2, color3);
}

void TSoftRenderer::DrawTriangle(const tmath::Point2i& p1, const tmath::Point2i& p2, const tmath::Point2i& p3,
	const tmath::UV2f& uv1, const tmath::UV2f& uv2, const tmath::UV2f& uv3)
{
	m_rz.DrawTriangle(p1, p2, p3, uv1, uv2, uv3);
}

void TSoftRenderer::DrawImage(const TImage& image, int startX, int startY)
{
	m_rz.DrawImage(image, startX, startY);
}

void TSoftRenderer::SetBlend(bool enable)
{
	m_state.SetBlend(enable);
}

void TSoftRenderer::SetTexture(const TImage* texture)
{
	m_state.SetTexture(texture);
}

void TSoftRenderer::SetSampleMode(TSampleMode mode)
{
	m_state.SetSampleMode(mode);
}

void TSoftRenderer::SetWrapMode(TWrapMode mode)
{
	m_state.SetWrapMode(mode);
}

uint32_t TSoftRenderer::AllocateBufferId()
{
	if (m_freeBufferIds.empty())
	{
		return ++m_nextBufferId;
	}
	else
	{
		uint32_t id = m_freeBufferIds.front();
		m_freeBufferIds.pop();
		return id;
	}
}

uint32_t TSoftRenderer::AllocateVaoId()
{
	if (m_freeVaoIds.empty())
		return ++m_nextVaoId;
	else
	{
		uint32_t id = m_freeVaoIds.front();
		m_freeVaoIds.pop();
		return id;
	}
}

void TSoftRenderer::GenBuffers(uint32_t n, uint32_t* buffers)
{
	for (uint32_t i = 0; i < n; i++)
	{
		uint32_t id = AllocateBufferId();
		m_bufferMap[id] = new TBufferObject(id);
		buffers[i] = id;
	}
}

void TSoftRenderer::DeleteBuffers(uint32_t n, uint32_t* buffers)
{
	for (uint32_t i = 0; i < n; i++)
	{
		uint32_t id = buffers[i];
		auto it = m_bufferMap.find(id);
		if (it != m_bufferMap.end())
		{
			delete it->second;
			m_bufferMap.erase(it);
			m_freeBufferIds.push(id);
		}
	}
}

void TSoftRenderer::GenVertexArrays(uint32_t n, uint32_t* arrays)
{
	for (uint32_t i = 0; i < n; i++)
	{
		uint32_t id = AllocateVaoId();
		m_vaoMap[id] = new TVertexArrayObject(id);
		arrays[i] = id;
	}
}

void TSoftRenderer::DeleteVertexArrays(uint32_t n, uint32_t* arrays)
{
	for (uint32_t i = 0; i < n; i++)
	{
		uint32_t id = arrays[i];
		auto it = m_vaoMap.find(id);
		if (it != m_vaoMap.end())
		{
			delete it->second;
			m_vaoMap.erase(it);
			m_freeVaoIds.push(id);
		}
	}
}

void TSoftRenderer::BindBuffer(TBufferType target, uint32_t buffer)
{
	TBufferObject* bufferPtr = NULL;
	if (buffer != 0)
	{
		auto it = m_bufferMap.find(buffer);
		assert(it != m_bufferMap.end());

		bufferPtr = it->second;
	}

	switch (target)
	{
	case TBufferType::ArrayBuffer:
		m_currentArrayBuffer = bufferPtr;
		break;
	case TBufferType::ElementArrayBuffer:
		m_currentElementBuffer = bufferPtr;
		break;
	default:
		assert(0);
		break;
	}
}

void TSoftRenderer::BufferData(TBufferType target, uint32_t size, void* data)
{
	TBufferObject* buffer = NULL;

	switch (target)
	{
	case TBufferType::ArrayBuffer:
		buffer = m_currentArrayBuffer;
		break;
	case TBufferType::ElementArrayBuffer:
		buffer = m_currentElementBuffer;
		break;
	default:
		break;
	}

	assert(buffer != NULL);
	buffer->SetBufferData(size, data);
}

void TSoftRenderer::BindVertexArray(uint32_t array)
{
	if (array == 0)
		m_currentVertexArray = NULL;
	else
	{
		auto it = m_vaoMap.find(array);
		assert(it != m_vaoMap.end());
		m_currentVertexArray = it->second;
	}
}

void TSoftRenderer::VertexAttribPointer(
	uint32_t index,
	uint32_t count,
#if 0
	TAttributeType type,
#endif
	uint32_t stride,
	uint32_t offset)
{
	assert(m_currentVertexArray != NULL);
	assert(m_currentArrayBuffer != NULL);

	TVertexAttribute attr(TAttributeType::Float, count, stride, offset);
	m_currentVertexArray->AddVertexAttribBinding(index, m_currentArrayBuffer, attr);
}

void TSoftRenderer::PrintVAO(uint32_t vao)
{
	auto it = m_vaoMap.find(vao);
	assert(it != m_vaoMap.end());
	it->second->Print();
}

void TSoftRenderer::UseProgram(TShader* shader)
{
	m_currentShader = shader;
}

int TSoftRenderer::GetPrimitiveCount(TDrawMode mode)
{
	switch (mode)
	{
	case TDrawMode::Triangles:
		return 3;
	case TDrawMode::Lines:
		return 2;
	default:
		assert(0);
		return 0;
	}
}

void TSoftRenderer::DrawElements(
	TDrawMode mode,
	uint32_t size,
#if 0
	TIndexDataType type,
#endif
	uint32_t offset)
{
	uint32_t* indexData = (uint32_t*)(m_currentElementBuffer->GetBufferData() + offset);

	FragmentShaderFunction fragFunc = std::bind(&TShader::FragmentShader, m_currentShader, std::placeholders::_1, std::placeholders::_2);
	TShaderContext context(m_currentVertexArray);
	TVertexShaderOutput vertexOutputs[3];
	int primitive = GetPrimitiveCount(mode);

	for (uint32_t i = 0; i < size; i += primitive)
	{
		for (uint32_t j = 0; j < primitive; j++)
		{
			context.SetVertexIndex(indexData[i + j]);

			// VertexShader
			m_currentShader->VertexShader(context, vertexOutputs[j]);

			// 透视除法
			vertexOutputs[j].position /= vertexOutputs[j].position.w();

			// NDC - 屏幕
			vertexOutputs[j].position = m_screenMatrix * vertexOutputs[j].position;
		}

		switch (mode)
		{
		case TDrawMode::Triangles:
			m_rz.RasterizeTriangle(vertexOutputs[0], vertexOutputs[1], vertexOutputs[2], fragFunc);
			break;
		case TDrawMode::Lines:
		default:
			assert(0);
			break;
		}
	}
}