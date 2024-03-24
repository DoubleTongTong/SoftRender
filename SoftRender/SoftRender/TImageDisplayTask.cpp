#include "TImageDisplayTask.h"

TImageDisplayTask::TImageDisplayTask()
	: m_img("image/dog.jpg"),
	  m_image_png("image/ivysaur.png")
{
}

void TImageDisplayTask::Render(TRasterizer& rz)
{
	rz.SetBlend(false);
	rz.DrawImage(m_img, 0, 0);
	rz.DrawImage(m_image_png, 0, m_img.GetHeight());
	rz.DrawImage(m_img, 0, m_img.GetHeight() + m_image_png.GetWidth());
	rz.DrawImage(m_image_png, 0, m_img.GetHeight() + m_image_png.GetWidth());

	rz.SetBlend(true);
	rz.DrawImage(m_img, m_img.GetWidth(), 0);
	rz.DrawImage(m_image_png, m_image_png.GetWidth(), m_img.GetHeight());
	rz.DrawImage(m_img, m_img.GetWidth(), m_img.GetHeight() + m_image_png.GetWidth());
	rz.DrawImage(m_image_png, m_img.GetWidth(), m_img.GetHeight() + m_image_png.GetWidth());
}