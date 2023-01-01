#include "Vect_Mv_SIMD.h"
#include "Matrix_Mv_SIMD.h"

Matrix_Mv_SIMD::Matrix_Mv_SIMD(const Vect_Mv_SIMD &tV0,
							   const Vect_Mv_SIMD &tV1,
							   const Vect_Mv_SIMD &tV2,
							   const Vect_Mv_SIMD &tV3)
	: v0(tV0), v1(tV1), v2(tV2), v3(tV3)
{
}

Vect_Mv_SIMD Matrix_Mv_SIMD::operator * (const Vect_Mv_SIMD &v) const
{
	Vect_Mv_SIMD vOut;
	vOut._m = _mm_dp_ps(this->v0._m, v._m, 0xF1);
	vOut._m = _mm_or_ps(_mm_dp_ps(this->v1._m, v._m, 0xF2), vOut._m);
	vOut._m = _mm_or_ps(_mm_dp_ps(this->v2._m, v._m, 0xF4), vOut._m);
	vOut._m = _mm_or_ps(_mm_dp_ps(this->v3._m, v._m, 0xF8), vOut._m);

	return  vOut;
}