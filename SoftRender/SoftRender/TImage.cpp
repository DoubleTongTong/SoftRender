#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "TImage.h"

TImage::TImage(const char* filePath)
{
	m_data = stbi_load(filePath, &m_width, &m_height, &m_channels, 4);
	assert(m_data);

	unsigned char tmp;
	for (int i = 0; i < m_width * m_height * 4; i += 4)
	{
		tmp = m_data[i];
		m_data[i] = m_data[i + 2];
		m_data[i + 2] = tmp;
	}
}

TImage::~TImage()
{
	if (m_data)
		stbi_image_free(m_data);
}

unsigned char* TImage::GetData() const
{
	return m_data;
}

int TImage::GetWidth() const
{
	return m_width;
}

int TImage::GetHeight() const
{
	return m_height;
}