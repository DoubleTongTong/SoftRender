#include "TMatrixOpsTask.h"
#include "TMatrix.h"

TMatrixOpsTask::TMatrixOpsTask()
{
	tmath::Mat4f m = { 8, 7, 9, 5,
					   4, 3, 3, 1,
					   2, 1, 1, 0,
					   6, 7, 9, 8 };
	m.Print("m");

	tmath::Mat4f mi = m.Inverse();
	mi.Print("inverse of m");

#if 0
	tmath::Mat4f s = { 1, 2, 3, 4,
					   2, 4, 6, 8,
					   1, 1, 1, 1,
					   0, 1, 2, 3 };
	s.Print("singular");

	tmath::Mat4f si = s.Inverse();
#endif
}

void TMatrixOpsTask::Render(TSoftRenderer& sr)
{

}