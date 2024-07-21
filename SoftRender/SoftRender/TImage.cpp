#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "TImage.h"

TImage::TImage()
	: m_width(0),
	  m_height(0),
	  m_channels(0),
	  m_data(NULL),
	  m_ownsData(true)
{
}

TImage::TImage(const char* filePath, ColorFormat format)
{
	m_data = stbi_load(filePath, &m_width, &m_height, &m_channels, 4);
	assert(m_data);

	if (format == ColorFormat::BGRA)
	{
		unsigned char tmp;
		for (int i = 0; i < m_width * m_height * 4; i += 4)
		{
			tmp = m_data[i];
			m_data[i] = m_data[i + 2];
			m_data[i + 2] = tmp;
		}
	}

	m_ownsData = false;
}

TImage::TImage(const unsigned char* data, int width, int height)
{
	m_width = width;
	m_height = height;
	m_channels = 4;

	m_data = new unsigned char[width * height * 4];
	memcpy(m_data, data, width * height * 4);

	m_ownsData = true;
}

TImage::~TImage()
{
	if (m_data)
	{
		if (m_ownsData)
			delete[] m_data;
		else
			stbi_image_free(m_data);
	}
}

TImage::TImage(TImage&& other) noexcept
	: m_data(other.m_data),
	  m_width(other.m_width),
	  m_height(other.m_height),
	  m_channels(other.m_channels),
	  m_ownsData(other.m_ownsData)
{
	other.m_data = NULL;
	other.m_width = 0;
	other.m_height = 0;
	other.m_channels = 0;
	other.m_ownsData = true;
}

TImage& TImage::operator=(TImage&& other) noexcept
{
	if (this != &other)
	{
		this->~TImage();

		m_data = other.m_data;
		m_width = other.m_width;
		m_height = other.m_height;
		m_channels = other.m_channels;
		m_ownsData = other.m_ownsData;

		other.m_data = NULL;
		other.m_width = 0;
		other.m_height = 0;
		other.m_channels = 0;
		other.m_ownsData = true;
	}

	return *this;
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