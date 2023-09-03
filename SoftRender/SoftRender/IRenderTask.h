#pragma once

#include "TRasterizer.h"

class IRenderTask
{
public:
	virtual void Render(TRasterizer& rz) = 0;
};