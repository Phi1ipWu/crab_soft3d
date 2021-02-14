
#ifndef __CRAB_ALGEBRA_H_
#define __CRAB_ALGEBRA_H_



///////////////////////////////////////////////////////////////////////////////
typedef struct tag_vector2
{
	float x, y;
}
vector2, *pvector2;

const vector2* crab_vector2_add(vector2* out, const vector2* v1, const vector2* v2);
const vector2* crab_vector2_sub(vector2* out, const vector2* v1, const vector2* v2);
const vector2* crab_vector2_normalized(vector2* out, const vector2* v);
float crab_vector2_dot(const vector2* v1, const vector2* v2);
float crab_vector2_cross(const vector2* v1, const vector2* v2);
float crab_vector2_distance(const vector2* v);
//float crab_vector2_triangle_area(const vector2* v1, const vector2* v2, const vector2* v3);
int crab_vector2_in_triangle(const vector2* p, const vector2* v1, const vector2* v2, const vector2* v3);

///////////////////////////////////////////////////////////////////////////////
typedef struct tag_vector3
{
	float x, y, z;
}
vector3, *pvector3;


const vector3* crab_vector3_add(vector3* out, const vector3* v1, const vector3* v2);
const vector3* crab_vector3_normalized(vector3* out, const vector3* v);
float crab_vector3_distance(const vector3* v);
const vector3* crab_vector_cross(vector3* out, const vector3* v1, const vector3* v2);

///////////////////////////////////////////////////////////////////////////////
typedef struct tag_matrix
{
	float	m11, m12, m13, m14,
			m21, m22, m23, m24,
			m31, m32, m33, m34,
			m41, m42, m43, m44;
}
matrix, *pmatrix;


const matrix* crab_matrix_zero(matrix* out);
const matrix* crab_matrix_identity(matrix* out);
const matrix* crab_matrix_mul(matrix* out, const matrix* a, const matrix* b);
const matrix* crab_matrix_transform(matrix* out, const vector3* v);
const matrix* crab_matrix_scale(matrix* out, const vector3* v);


#endif
