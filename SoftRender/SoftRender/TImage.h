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

	TImage(const TImage& other) = delete;
	TImage& operator=(const TImage& other) = delete;
	TImage(TImage&& other) noexcept;
	TImage& operator=(TImage&& other) noexcept;
	~TImage();

	static TImage LoadFromFile(const char* filePath, ColorFormat format = ColorFormat::RGBA);
	static TImage LoadFromRawData(const unsigned char* data, int width, int height);
	static TImage LoadFromMemoryBuffer(const unsigned char* buffer, size_t bufferSize, ColorFormat format = ColorFormat::RGBA);

	unsigned char* GetData() const;
	int GetWidth() const;
	int GetHeight() const;

private:
	TImage(unsigned char* data, int width, int height, int channels, bool useStbFree);
	void swap(TImage& other) noexcept;

	unsigned char* m_data;
	int m_width;
	int m_height;
	int m_channels;

	bool m_useStbFree;
};