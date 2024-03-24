#pragma once

class TImage
{
public:
	TImage(const char* filePath);
	~TImage();

	unsigned char* GetData() const;
	int GetWidth() const;
	int GetHeight() const;

	TImage() = delete;

private:
	unsigned char* m_data;
	int m_width;
	int m_height;
	int m_channels;

	TImage(const TImage&) = delete;
	TImage& operator=(const TImage&) = delete;
};