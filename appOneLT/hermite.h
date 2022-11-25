#pragma once
namespace hermite
{
	VECTOR interpolation(
		VECTOR& p1, VECTOR& v1,
		VECTOR& p2, VECTOR& v2,
		float t
	);

	VECTOR derivative(
		VECTOR& p1, VECTOR& v1,
		VECTOR& p2, VECTOR& v2,
		float t
	);
}