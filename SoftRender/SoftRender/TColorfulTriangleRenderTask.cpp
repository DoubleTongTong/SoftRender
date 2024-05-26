#include "TColorfulTriangleRenderTask.h"

void TColorfulTriangleRenderTask::Render(TSoftRenderer& sr)
{
	int centerX = sr.GetRenderWidth() / 2;
	int centerY = sr.GetRenderHeight() / 2;

	sr.Clear(TRGBA(0, 0, 0));

	sr.DrawTriangle({ centerX, 0 }, { 0, sr.GetRenderHeight() }, { sr.GetRenderWidth(), sr.GetRenderHeight() },
		TRGBA(255, 0, 0), TRGBA(0, 255, 0), TRGBA(0, 0, 255));
}