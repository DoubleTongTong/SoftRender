#include "TRadialLinesRenderTask.h"
#include <algorithm>

void TRadialLinesRenderTask::Render(TRasterizer& rz)
{
	int centerX = rz.GetWidth() / 2;
	int centerY = rz.GetHeight() / 2;

	const int angleInterval = 5;
	int r = std::min(rz.GetWidth(), rz.GetHeight()) / 2;

	rz.Clear(TRGBA(0, 0, 0));
	for (int angle = 0; angle < 360; angle += angleInterval)
	{
		double radian = angle * 3.14159265358979323846 / 180.0;

		int endX = (int)(centerX + cos(radian) * r);
		int endY = (int)(centerY + sin(radian) * r);

		rz.DrawLine(centerX, centerY, TRGBA(rand() % 255, rand() % 255, rand() % 255),
			endX, endY, TRGBA(rand() % 255, rand() % 255, rand() % 255));
	}
}