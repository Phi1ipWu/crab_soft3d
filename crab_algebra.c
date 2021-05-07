
#include "crab_algebra.h"
#include <math.h>


///////////////////////////////////////////////////////////////////////////////
const vector2* crab_vector2_add(vector2* out, const vector2* v1, const vector2* v2)
{
	out->x = v1->x + v2->x;
	out->y = v1->y + v2->y;
	return out;
}

const vector2* crab_vector2_sub(vector2* out, const vector2* v1, const vector2* v2)
{
	out->x = v1->x - v2->x;
	out->y = v1->y - v2->y;
	return out;
}

const vector2* crab_vector2_normalized(vector2* out, const vector2* v)
{
	float dist = crab_vector2_distance(v);
	out->x = dist > 0 ? v->x / dist : 0.0f;
	out->y = dist > 0 ? v->y / dist : 0.0f;
	return out;
}

float crab_vector2_dot(const vector2* v1, const vector2* v2)
{
	return v1->x * v2->x + v1->y * v2->y;
}

float crab_vector2_cross(const vector2* v1, const vector2* v2)
{
	return v1->x * v2->y - v1->y * v2->x;
}

float crab_vector2_distance(const vector2* a)
{
	return (float)sqrt(a->x * a->x + a->y * a->y);
}

float crab_vector2_triangle_area(const vector2* v1, const vector2* v2, const vector2* v3)
{
	float a, b, c, d, e, f;
	a = v1->x, b = v1->y;
	c = v2->x, d = v2->y;
	e = v3->x, f = v3->y;
	return 0.5f * (float)fabs(a*d + b*e + c*f - a*f - b*c - d*e);
}

int crab_vector2_in_triangle(const vector2* p, const vector2* v1, const vector2* v2, const vector2* v3)
{
	// https://stackoverflow.com/questions/2049582/how-to-determine-if-a-point-is-in-a-2d-triangle
	float d1, d2, d3;
	int has_neg, has_pos;

	d1 = (p->x - v2->x) * (v1->y - v2->y) - (v1->x - v2->x) * (p->y - v2->y);
	d2 = (p->x - v3->x) * (v2->y - v3->y) - (v2->x - v3->x) * (p->y - v3->y);
	d3 = (p->x - v1->x) * (v3->y - v1->y) - (v3->x - v1->x) * (p->y - v1->y);

	has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
	has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

	return !(has_neg && has_pos);
}

///////////////////////////////////////////////////////////////////////////////
const vector3* crab_vector3_add(vector3* out, const vector3* v1, const vector3* v2)
{
	out->x = v1->x + v2->x;
	out->y = v1->y + v2->y;
	out->z = v1->z + v2->z;

	return out;
}

const vector3* crab_vector3_normalized(vector3* out, const vector3* v)
{
	float dist = crab_vector3_distance(v);
	out->x = dist > 0 ? v->x / dist : 0.0f;
	out->y = dist > 0 ? v->y / dist : 0.0f;
	out->z = dist > 0 ? v->z / dist : 0.0f;
	return out;
}

float crab_vector3_distance(const vector3* v)
{
	return (float)sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
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
