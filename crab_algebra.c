
#include "crab_algebra.h"
#include <math.h>


///////////////////////////////////////////////////////////////////////////////
const vector2* crab_vector2_add(vector2* out, const vector2* a, const vector2* b)
{
	out->x = a->x + b->x;
	out->y = a->y + b->y;
	return out;
}

const vector2* crab_vector2_sub(vector2* out, const vector2* a, const vector2* b)
{
	out->x = a->x - b->x;
	out->y = a->y - b->y;
	return out;
}

const vector2* crab_vector2_normalized(vector2* out, const vector2* a)
{
	float dist = crab_vector2_distance(a);
	out->x = dist > 0 ? a->x / dist : 0.0f;
	out->y = dist > 0 ? a->y / dist : 0.0f;
	return out;
}

float crab_vector2_dot(const vector2* a, const vector2* b)
{
	return a->x * b->x + a->y * b->y;
}

float crab_vector2_distance(const vector2* a)
{
	return (float)sqrt(a->x * a->x + a->y * a->y);
}


///////////////////////////////////////////////////////////////////////////////
const vector3* crab_vector3_add(vector3* out, const vector3* a, const vector3* b)
{
	out->x = a->x + b->x;
	out->y = a->y + b->y;
	out->z = a->z + b->z;

	return out;
}

const vector3* crab_vector3_normalized(vector3* out, const vector3* a)
{
	float dist = crab_vector3_distance(a);
	out->x = dist > 0 ? a->x / dist : 0.0f;
	out->y = dist > 0 ? a->y / dist : 0.0f;
	out->z = dist > 0 ? a->z / dist : 0.0f;
	return out;
}

float crab_vector3_distance(const vector3* a)
{
	return (float)sqrt(a->x * a->x + a->y * a->y + a->z * a->z);
}

///////////////////////////////////////////////////////////////////////////////
const matrix* crab_matrix_zero(matrix* out)
{
	out->m11 = out->m12 = out->m13 = out->m14 = 0;
	out->m21 = out->m22 = out->m23 = out->m24 = 0;
	out->m31 = out->m32 = out->m33 = out->m34 = 0;
	out->m41 = out->m42 = out->m43 = out->m44 = 0;
	return out;
}

const matrix* crab_matrix_identity(matrix* out)
{
	crab_matrix_zero(out);
	out->m11 = out->m22 = out->m33 = out->m44 = 1.0f;
	return out;
}

const matrix* crab_matrix_mul(matrix* out, const matrix* a, const matrix* b)
{
	out->m11 = a->m11 * b->m11 + a->m12 * b->m21 + a->m13 * b->m31 + a->m14 * b->m41;
	out->m12 = a->m11 * b->m12 + a->m12 * b->m22 + a->m13 * b->m32 + a->m14 * b->m42;
	out->m13 = a->m11 * b->m13 + a->m12 * b->m23 + a->m13 * b->m33 + a->m14 * b->m43;
	out->m14 = a->m11 * b->m14 + a->m12 * b->m24 + a->m13 * b->m34 + a->m14 * b->m44;

	out->m21 = a->m21 * b->m11 + a->m22 * b->m21 + a->m23 * b->m31 + a->m24 * b->m41;
	out->m22 = a->m21 * b->m12 + a->m22 * b->m22 + a->m23 * b->m32 + a->m24 * b->m42;
	out->m23 = a->m21 * b->m13 + a->m22 * b->m23 + a->m23 * b->m33 + a->m24 * b->m43;
	out->m24 = a->m21 * b->m14 + a->m22 * b->m24 + a->m23 * b->m34 + a->m24 * b->m44;

	out->m31 = a->m31 * b->m11 + a->m32 * b->m21 + a->m33 * b->m31 + a->m34 * b->m41;
	out->m32 = a->m31 * b->m12 + a->m32 * b->m22 + a->m33 * b->m32 + a->m34 * b->m42;
	out->m33 = a->m31 * b->m13 + a->m32 * b->m23 + a->m33 * b->m33 + a->m34 * b->m43;
	out->m34 = a->m31 * b->m14 + a->m32 * b->m24 + a->m33 * b->m34 + a->m34 * b->m44;

	out->m41 = a->m31 * b->m11 + a->m42 * b->m21 + a->m43 * b->m31 + a->m44 * b->m41;
	out->m42 = a->m31 * b->m12 + a->m42 * b->m22 + a->m43 * b->m32 + a->m44 * b->m42;
	out->m43 = a->m31 * b->m13 + a->m42 * b->m23 + a->m43 * b->m33 + a->m44 * b->m43;
	out->m44 = a->m31 * b->m14 + a->m42 * b->m24 + a->m43 * b->m34 + a->m44 * b->m44;

	return out;
}

const vector3* crab_vector_cross(vector3* out, const vector3* a, const vector3* b)
{
	//VectorRegister Vec;
	//Vec.V[0] = Vec1.V[1] * Vec2.V[2] - Vec1.V[2] * Vec2.V[1];
	//Vec.V[1] = Vec1.V[2] * Vec2.V[0] - Vec1.V[0] * Vec2.V[2];
	//Vec.V[2] = Vec1.V[0] * Vec2.V[1] - Vec1.V[1] * Vec2.V[0];
	//Vec.V[3] = 0.0f;
	//return Vec;
	return out;
}

const matrix* crab_matrix_transform(matrix* out, const vector3* v)
{
	crab_matrix_identity(out);
	out->m41 = v->x;
	out->m42 = v->y;
	out->m43 = v->z;
	return out;
}

const matrix* crab_matrix_scale(matrix* out, const vector3* v)
{
	crab_matrix_identity(out);
	out->m11 = v->x;
	out->m22 = v->y;
	out->m33 = v->z;
	return out;
}
