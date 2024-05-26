#include "TVectorOpsRenderTask.h"
#include "TVector.h"

void TVectorOpsRenderTask::Render(TSoftRenderer& sr)
{
	tmath::Vec2f vec1(1.0f, 2.0f);
	tmath::Vec2f vec2(3.0f, 4.0f);

	auto vec3 = vec1 + vec2;
	printf("%s + %s = %s\n", vec1.toString().c_str(), vec2.toString().c_str(), vec3.toString().c_str());

	vec3 = vec1 * 2.0f;
	printf("%s * 2.0 = %s\n", vec1.toString().c_str(), vec3.toString().c_str());

	vec3 = 2.0f * vec2;
	printf("2.0 * %s = %s\n", vec2.toString().c_str(), vec3.toString().c_str());

	vec3 /= 2;
	printf("vec3 /= 2.0 = %s\n", vec3.toString().c_str());

	float res = tmath::cross(vec1, vec2);
	printf("%s cross %s = %f\n", vec1.toString().c_str(), vec2.toString().c_str(), res);
}