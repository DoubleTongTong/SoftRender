#include "TColorfulTriangleRenderTask.h"

void TColorfulTriangleRenderTask::Render(TRasterizer& rz)
{
	int centerX = rz.GetWidth() / 2;
	int centerY = rz.GetHeight() / 2;

	rz.Clear(TRGBA(0, 0, 0));

	rz.DrawTriangle({ centerX, 0 }, { 0, rz.GetHeight() }, { rz.GetWidth(), rz.GetHeight() },
		TRGBA(255, 0, 0), TRGBA(0, 255, 0), TRGBA(0, 0, 255));
}