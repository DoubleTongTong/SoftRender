#include "TBufferObject.h"
#include <string.h>
#include <iostream>

TBufferObject::TBufferObject(uint32_t id)
	: m_id(id),
	  m_size(0),
	  m_pBuffer(NULL)
{
}

TBufferObject::~TBufferObject()
{
	delete[] m_pBuffer;
}

void TBufferObject::SetBufferData(uint32_t size, void* data)
{
	if (size > m_size)
	{
		delete[] m_pBuffer;
		m_pBuffer = new uint8_t[size];
	}

	m_size = size;

	if (data != NULL && size > 0)
	{
		memcpy(m_pBuffer, data, size);
	}
}

uint8_t* TBufferObject::GetBufferData()
{
	return m_pBuffer;
}

void TBufferObject::Print() const
{
	std::cout << "Buffer ID: " << m_id << ", Size: " << m_size << " bytes.\n";
}