#include "Vect_M_SIMD.h"
#include "Matrix_M_SIMD.h"

Matrix_M_SIMD::Matrix_M_SIMD(const Vect_M_SIMD &tV0,
							 const Vect_M_SIMD &tV1,
							 const Vect_M_SIMD &tV2,
							 const Vect_M_SIMD &tV3)
	: v0(tV0), v1(tV1), v2(tV2), v3(tV3)
{
}

Matrix_M_SIMD Matrix_M_SIMD::operator * (const Matrix_M_SIMD &mb) const
{
	Matrix_M_SIMD rotated = mb;
	_MM_TRANSPOSE4_PS(rotated.v0._m, rotated.v1._m, rotated.v2._m, rotated.v3._m);

	Matrix_M_SIMD A;
	//Make first row of A
	A.v0._m = _mm_dp_ps(this->v0._m, rotated.v0._m, 0xF1);	
	A.v0._m = _mm_or_ps(_mm_dp_ps(this->v0._m, rotated.v1._m, 0xF2), A.v0._m);
	A.v0._m = _mm_or_ps(_mm_dp_ps(this->v0._m, rotated.v2._m, 0xF4), A.v0._m);
	A.v0._m = _mm_or_ps(_mm_dp_ps(this->v0._m, rotated.v3._m, 0xF8), A.v0._m);

	//Make second row of A
	A.v1._m = _mm_dp_ps(this->v1._m, rotated.v0._m, 0xF1);
	A.v1._m = _mm_or_ps(_mm_dp_ps(this->v1._m, rotated.v1._m, 0xF2), A.v1._m);
	A.v1._m = _mm_or_ps(_mm_dp_ps(this->v1._m, rotated.v2._m, 0xF4), A.v1._m);
	A.v1._m = _mm_or_ps(_mm_dp_ps(this->v1._m, rotated.v3._m, 0xF8), A.v1._m);

	//Make third row of A
	A.v2._m = _mm_dp_ps(this->v2._m, rotated.v0._m, 0xF1);
	A.v2._m = _mm_or_ps(_mm_dp_ps(this->v2._m, rotated.v1._m, 0xF2), A.v2._m);
	A.v2._m = _mm_or_ps(_mm_dp_ps(this->v2._m, rotated.v2._m, 0xF4), A.v2._m);
	A.v2._m = _mm_or_ps(_mm_dp_ps(this->v2._m, rotated.v3._m, 0xF8), A.v2._m);

	//Make fourth row of A
	A.v3._m = _mm_dp_ps(this->v3._m, rotated.v0._m, 0xF1);
	A.v3._m = _mm_or_ps(_mm_dp_ps(this->v3._m, rotated.v1._m, 0xF2), A.v3._m);
	A.v3._m = _mm_or_ps(_mm_dp_ps(this->v3._m, rotated.v2._m, 0xF4), A.v3._m);
	A.v3._m = _mm_or_ps(_mm_dp_ps(this->v3._m, rotated.v3._m, 0xF8), A.v3._m);
	return A;
}
