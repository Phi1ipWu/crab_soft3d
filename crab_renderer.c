
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


void test_triangle(renderer* r)
{
	int x, y;
	vector2 v, v1, v2, v3, v_min, v_max;
	int c1, c2, c3;

	v1.x = rand() % r->screen_sx, v1.y = rand() % r->screen_sy;
	v2.x = rand() % r->screen_sx, v2.y = rand() % r->screen_sy;
	v3.x = rand() % r->screen_sx, v3.y = rand() % r->screen_sy;
	c1 = 0xFFFF0000;
	c2 = 0xFF00FF00;
	c3 = 0xFF0000FF;

	v_min.x = min(v1.x, min(v2.x, v3.x));
	v_min.y = min(v1.y, min(v2.y, v3.y));
	v_max.x = max(v1.x, max(v2.x, v3.x));
	v_max.y = max(v1.y, max(v2.y, v3.y));
	for (x = v_min.x; x <= v_max.x; ++x)
		for (y = v_min.y; y <= v_max.y; ++y)
		{
			v.x = x, v.y = y;
			if (crab_vector2_in_triangle(&v, &v1, &v2, &v3))
				r->draw_point(x, y, 0xFFFFFF00);
		}
}


void begin_render(renderer* r)
{
	memset(r->z_buffer, 0, sizeof(float) * r->screen_sx * r->screen_sy);
}

void render(renderer* r)
{
	test_triangle(r);
}

void end_render(renderer* r)
{
}

///////////////////////////////////////////////////////////////////////////////
void draw_triangle(const vector3* vec_list, int* color_list)
{
	
}
