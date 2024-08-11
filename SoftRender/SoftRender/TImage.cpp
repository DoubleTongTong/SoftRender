#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "TImage.h"

#include <utility>

TImage::TImage(unsigned char* data, int width, int height, int channels, bool useStbFree)
	: m_data(data), m_width(width), m_height(height), m_channels(channels), m_useStbFree(useStbFree)
{
}

TImage::TImage()
	: m_data(NULL), m_width(0), m_height(0), m_channels(0), m_useStbFree(false)
{
}

TImage::~TImage()
{
	if (m_data)
	{
		if (m_useStbFree)
			stbi_image_free(m_data);
		else
			delete[] m_data;
	}
}

TImage::TImage(TImage&& other) noexcept
	: TImage()
{
	swap(other);
}

TImage& TImage::operator=(TImage&& other) noexcept
{
	if (this != &other)
	{
		TImage tmp(std::move(other));
		swap(tmp);
	}

	return *this;
}

void TImage::swap(TImage& other) noexcept
{
	std::swap(m_data, other.m_data);
	std::swap(m_width, other.m_width);
	std::swap(m_height, other.m_height);
	std::swap(m_channels, other.m_channels);
	std::swap(m_useStbFree, other.m_useStbFree);
}

TImage TImage::LoadFromFile(const char* filePath, ColorFormat format)
{
	int width, height, channels;
	unsigned char* data = stbi_load(filePath, &width, &height, &channels, STBI_rgb_alpha);
	assert(data);
	if (format == ColorFormat::BGRA)
	{
		for (int i = 0; i < width * height * 4; i += 4)
			std::swap(data[i], data[i + 2]);
	}

	return TImage(data, width, height, channels, true);
}

TImage TImage::LoadFromRawData(const unsigned char* data, int width, int height)
{
	int channels = 4; // Assuming RGBA or BGRA format
	unsigned char* copiedData = new unsigned char[width * height * channels];
	memcpy(copiedData, data, width * height * channels);
	return TImage(copiedData, width, height, channels, false);
}

TImage TImage::LoadFromMemoryBuffer(const unsigned char* buffer, size_t bufferSize, ColorFormat format)
{
	int width, height, channels;
	unsigned char* data = stbi_load_from_memory(buffer, bufferSize, &width, &height, &channels, STBI_rgb_alpha);
	if (format == ColorFormat::BGRA)
	{
		for (int i = 0; i < width * height * 4; i += 4)
			std::swap(data[i], data[i + 2]);
	}

	return TImage(data, width, height, channels, true);
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