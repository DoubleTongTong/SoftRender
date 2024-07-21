#include "TImageDisplayTask.h"

TImageDisplayTask::TImageDisplayTask()
	: m_img("image/dog.jpg", TImage::ColorFormat::BGRA),
	  m_image_png("image/ivysaur.png", TImage::ColorFormat::BGRA)
{
}

void TImageDisplayTask::Render(TSoftRenderer& sr)
{
	sr.SetBlend(false);
	sr.DrawImage(m_img, 0, 0);
	sr.DrawImage(m_image_png, 0, m_img.GetHeight());
	sr.DrawImage(m_img, 0, m_img.GetHeight() + m_image_png.GetWidth());
	sr.DrawImage(m_image_png, 0, m_img.GetHeight() + m_image_png.GetWidth());

	sr.SetBlend(true);
	sr.DrawImage(m_img, m_img.GetWidth(), 0);
	sr.DrawImage(m_image_png, m_image_png.GetWidth(), m_img.GetHeight());
	sr.DrawImage(m_img, m_img.GetWidth(), m_img.GetHeight() + m_image_png.GetWidth());
	sr.DrawImage(m_image_png, m_img.GetWidth(), m_img.GetHeight() + m_image_png.GetWidth());
}