#pragma once

#include "TSoftRenderer.h"

class IRenderTask
{
public:
	virtual void Render(TSoftRenderer& sr) = 0;
};