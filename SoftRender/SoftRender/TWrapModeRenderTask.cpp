#include "TWrapModeRenderTask.h"

TWrapModeRenderTask::TWrapModeRenderTask(TWrapMode mode)
	: m_wrapMode(mode)
{
	m_texture = TImage::LoadFromFile("image/ivysaur.png", TImage::ColorFormat::BGRA);
}

void TWrapModeRenderTask::Render(TSoftRenderer& sr)
{
	int width = m_texture.GetWidth();
	int height = m_texture.GetHeight();

	sr.SetTexture(&m_texture);
	sr.SetWrapMode(m_wrapMode);

	for (int row = 0; row < 3; row++)
	{
		tmath::Point2i p1 = tmath::Point2i(0, height * row);
		tmath::Point2i p2 = tmath::Point2i(width, height * row);
		tmath::Point2i p3 = tmath::Point2i(0, height * (row + 1));
		tmath::Point2i p4 = tmath::Point2i(width, height * (row + 1));

		tmath::UV2f uv1 = tmath::UV2f(0.0f, static_cast<float>(row));
		tmath::UV2f uv2 = tmath::UV2f(1.0f, static_cast<float>(row));
		tmath::UV2f uv3 = tmath::UV2f(0.0f, static_cast<float>(row + 1));
		tmath::UV2f uv4 = tmath::UV2f(1.0f, static_cast<float>(row + 1));

		for (int i = 0; i < 3; i++)
		{
			sr.DrawTriangle(p1, p2, p3, uv1, uv2, uv3);
			sr.DrawTriangle(p2, p3, p4, uv2, uv3, uv4);

			p1.x() += width;
			p2.x() += width;
			p3.x() += width;
			p4.x() += width;

			uv1.u() += 1.0f;
			uv2.u() += 1.0f;
			uv3.u() += 1.0f;
			uv4.u() += 1.0f;
		}
	}
}