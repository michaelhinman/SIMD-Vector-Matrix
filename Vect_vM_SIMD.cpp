#include "Vect_vM_SIMD.h"
#include "Matrix_vM_SIMD.h"

Vect_vM_SIMD::Vect_vM_SIMD(const float tx, const float ty, const float tz, const float tw)
	: x(tx), y(ty), z(tz), w(tw)
{
}

Vect_vM_SIMD Vect_vM_SIMD::operator * (const Matrix_vM_SIMD &ma) const
{
	Matrix_vM_SIMD rotated = ma;
	_MM_TRANSPOSE4_PS(rotated.v0._m, rotated.v1._m, rotated.v2._m, rotated.v3._m);

	Vect_vM_SIMD A;
	A._m = _mm_dp_ps(this->_m, rotated.v0._m, 0xF1);
	A._m = _mm_or_ps(_mm_dp_ps(this->_m, rotated.v1._m, 0xF2), A._m);
	A._m = _mm_or_ps(_mm_dp_ps(this->_m, rotated.v2._m, 0xF4), A._m);
	A._m = _mm_or_ps(_mm_dp_ps(this->_m, rotated.v3._m, 0xF8), A._m);
	return  A; 
};
