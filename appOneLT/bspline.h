#pragma once
namespace bspline
{
	VECTOR interpolation(
		VECTOR& p0, VECTOR& p1,
		VECTOR& p2, VECTOR& p3,
		float t
	);
	VECTOR derivative(
		VECTOR& p0, VECTOR& p1,
		VECTOR& p2, VECTOR& p3,
		float t
	);
}