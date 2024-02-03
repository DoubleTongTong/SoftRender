#include "TColorfulTriangleRenderTask.h"

void TColorfulTriangleRenderTask::Render(TRasterizer& rz)
{
	int centerX = rz.GetWidth() / 2;
	int centerY = rz.GetHeight() / 2;

	rz.Clear(TRGB888(0, 0, 0));

	rz.DrawTriangle({ centerX, 0 }, { 0, rz.GetHeight() }, { rz.GetWidth(), rz.GetHeight() },
		TRGB888(255, 0, 0), TRGB888(0, 255, 0), TRGB888(0, 0, 255));
}