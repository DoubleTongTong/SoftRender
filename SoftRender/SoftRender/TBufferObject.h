#pragma once

#include <stdint.h>

enum class TBufferType
{
	ArrayBuffer,
	ElementArrayBuffer
};

enum class TDrawMode
{
	Triangles,
	Lines
};

enum class TIndexDataType
{
	UnsignedByte,
	UnsignedShort,
	UnsignedInt
};


class TBufferObject
{
public:
	TBufferObject(uint32_t id);
	~TBufferObject();

	void SetBufferData(uint32_t size, void* data);
	uint8_t* GetBufferData();

	/* Debug */
	void Print() const;

private:
	uint32_t m_id;
	uint32_t m_size;
	uint8_t* m_pBuffer;
};