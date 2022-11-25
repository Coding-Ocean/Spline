#include"VECTOR.h"
#include"bspline.h"
namespace bspline
{
	VECTOR interpolation(
		VECTOR& p0, VECTOR& p1,
		VECTOR& p2, VECTOR& p3,
		float t)
	{
		float omt = 1.0f - t;
		float t3 = t * t * t;
		float t2 = t * t;
		float oos = 1.0f / 6;//one over six
		return
			oos * omt * omt * omt * p0 +
			(0.5f * t3 - t2 + 2.0f / 3) * p1 +
			(-0.5f * t3 + 0.5f * t2 + 0.5f * t + oos) * p2 +
			oos * t3 * p3;
	}

	VECTOR derivative(
		VECTOR& p0, VECTOR& p1,
		VECTOR& p2, VECTOR& p3,
		float t)
	{
		float t2 = t * t;
		return
			(-0.5f * t2 + t - 0.5f) * p0 +
			(1.5f * t2 - 2 * t) * p1 +
			(-1.5f * t2 + t + 0.5f) * p2 +
			0.5f * t2 * p3;
	}
}