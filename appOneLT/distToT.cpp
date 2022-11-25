#include"mathUtil.h"
//‹——£‚©‚ç‚”‚ğ‹‚ß‚é
float distToT(
	float* LUT, //LUT Look Up Table
	int LUTlength, 
	float dist)
{
	float arcLength = LUT[LUTlength - 1];
	int n = LUTlength;
	if (0 <= dist && dist <= arcLength) {
		for (int i = 0; i < n; i++) {
			if (LUT[i] <= dist && dist <= LUT[i + 1]) {
				return Map(dist,
					LUT[i], LUT[i + 1],
					i/(n-1.0f), (i+1)/(n-1.0f));
			}
		}
	}
}