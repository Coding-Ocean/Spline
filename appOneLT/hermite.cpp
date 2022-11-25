#include"VECTOR.h"
#include"hermite.h"
namespace hermite
{
	VECTOR interpolation(
		VECTOR& p1, VECTOR& v1,
		VECTOR& p2, VECTOR& v2,
		float t)
	{
		return
			(-2 * (p2 - p1) + v2 + v1) * t * t * t +
			(3 * (p2 - p1) - v2 - 2 * v1) * t * t +
			v1 * t +
			p1;
	}
	VECTOR derivative(
		VECTOR& p1, VECTOR& v1,
		VECTOR& p2, VECTOR& v2,
		float t)
	{
		return
			(-2 * (p2 - p1) + v2 + v1) * 3 * t * t +
			(3 * (p2 - p1) - v2 - 2 * v1) * 2 * t +
			v1;
	}
}