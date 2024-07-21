#pragma once

class TImage
{
public:
	enum class ColorFormat
	{
		RGBA,
		BGRA,
	};

	TImage();
	TImage(const char* filePath, ColorFormat format);
	TImage(const unsigned char* data, int width, int height);
	~TImage();

	unsigned char* GetData() const;
	int GetWidth() const;
	int GetHeight() const;

	TImage(TImage&& other) noexcept;
	TImage& operator=(TImage&& other) noexcept;
private:
	unsigned char* m_data;
	int m_width;
	int m_height;
	int m_channels;

	bool m_ownsData;

	TImage(const TImage&) = delete;
	TImage& operator=(const TImage&) = delete;
};