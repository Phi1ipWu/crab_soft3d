
#include "crab_renderer.h"
#include "crab_algebra.h"
#include <stdlib.h>


///////////////////////////////////////////////////////////////////////////////
renderer* create_renderer(int screen_sx, int screen_sy, func_draw_point func)
{
	renderer* r = (renderer*)malloc(sizeof(renderer));
	r->screen_sx = screen_sx;
	r->screen_sy = screen_sy;
	r->draw_point = func;
	r->z_buffer  = (float*)malloc(sizeof(float) * screen_sx * screen_sy);
	return r;
}

void destroy_renderer(renderer* r)
{
	free(r->z_buffer);
	free(r);
}


void test_render1(renderer* r)
{
	int x, y;
	for (x = 1; x <= 200; ++x)
		for (y = 1; y <= 200; ++y)
		{
			vector2 v1, v2, v3;
			v1.x = 100, v1.y = 100;
			v2.x = x, v2.y = y;
			crab_vector2_sub(&v3, &v2, &v1);


		}
}


void begin_render(renderer* r)
{
	memset(r->z_buffer, 0, sizeof(float) * r->screen_sx * r->screen_sy);
}

void render(renderer* r)
{
/*
	//int x, y;
	int c1, c2, c3;
	vector2 v, v1, v2, v3, v_min, v_max;
	v1.x = 100, v1.y = 100;
	v2.x = 100, v2.y = 250;
	v3.x = 400, v3.y = 250;
	c1 = 0xFFFF0000;
	c2 = 0xFF00FF00;
	c3 = 0xFF0000FF;

	v_min.x = min(v1.x, min(v2.x, v3.x));
	v_min.y = min(v1.y, min(v2.y, v3.y));
	v_max.x = max(v1.x, max(v2.x, v3.x));
	v_max.y = max(v1.y, max(v2.y, v3.y));

	for (v.x = v_min.x; v.x <= v_max.x; ++v.x)
		for (v.y = v_min.y; v.y <= v_max.y; ++v.y)
		{
			vector2 temp;
			vector2 vn1, vn2, vn3;
			//vector2 vr1, vr2, vr3;
			float d1, d2, d3;

			crab_vector2_normalized(&vn1, crab_vector2_sub(&temp, &v1, &v));
			crab_vector2_normalized(&vn2, crab_vector2_sub(&temp, &v2, &v));
			crab_vector2_normalized(&vn3, crab_vector2_sub(&temp, &v3, &v));

			d1 = crab_vector2_dot(&vn1, &vn2);
			d2 = crab_vector2_dot(&vn2, &vn3);
			d3 = crab_vector2_dot(&vn3, &vn1);

			if (1)
				r->draw_point((int)v.x, (int)v.y, 0xFF000000 | (d1 > 0 ? 0xFF0000 : 0) | (d2 > 0 ? 0xFF00 : 0) | (d3 > 0 ? 0xFF : 0));
		}
*/
	test_render1(r);
}

void end_render(renderer* r)
{
}

///////////////////////////////////////////////////////////////////////////////
void draw_triangle(const vector3* vec_list, int* color_list)
{
	
}
