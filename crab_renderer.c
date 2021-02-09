
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
	vector2 vp, vp1, vp2, vp3, v_min, v_max;
	int c1, c2, c3;

	//v1.x = rand() % r->screen_sx, v1.y = rand() % r->screen_sy;
	//v2.x = rand() % r->screen_sx, v2.y = rand() % r->screen_sy;
	//v3.x = rand() % r->screen_sx, v3.y = rand() % r->screen_sy;
	vp1.x = 100, vp1.y = 100;
	vp2.x = 260, vp2.y = 600;
	vp3.x = 600, vp3.y = 260;
	c1 = 0xFFFF0000;
	c2 = 0xFF00FF00;
	c3 = 0xFF0000FF;

	v_min.x = min(vp1.x, min(vp2.x, vp3.x));
	v_min.y = min(vp1.y, min(vp2.y, vp3.y));
	v_max.x = max(vp1.x, max(vp2.x, vp3.x));
	v_max.y = max(vp1.y, max(vp2.y, vp3.y));
	for (x = v_min.x; x <= v_max.x; ++x)
		for (y = v_min.y; y <= v_max.y; ++y)
		{
			vp.x = x, vp.y = y;
			if (crab_vector2_in_triangle(&vp, &vp1, &vp2, &vp3))
			{
				int x1, x2, x3, y1, y2, y3;
				float u1, u2, u3, v1, v2, v3;
				x1 = abs(x - (int)vp1.x);
				x2 = abs(x - (int)vp2.x);
				x3 = abs(x - (int)vp3.x);
				y1 = abs(y - (int)vp1.y);
				y2 = abs(y - (int)vp2.y);
				y3 = abs(y - (int)vp3.y);

				u1 = 1.f - (x1 * 1.f / (x1 + x2 + x3));
				u2 = 1.f - (x2 * 1.f / (x1 + x2 + x3));
				u3 = 1.f - (x3 * 1.f / (x1 + x2 + x3));
				v1 = 1.f - (y1 * 1.f / (y1 + y2 + y3));
				v2 = 1.f - (y2 * 1.f / (y1 + y2 + y3));
				v3 = 1.f - (y3 * 1.f / (y1 + y2 + y3));

				//r->draw_point(x, y, 0xFF00FF00);
				//continue;

				r->draw_point(x, y, 0xFF |
					(int)(((c1 & 0xFF0000) * (u1 + v1) / 0.5f) + ((c2 & 0xFF0000) * (u2 + v2) / 0.5f) + ((c3 & 0xFF0000) * (u3 + v3) / 0.5f)) |
					(int)(((c1 & 0x00FF00) * (u1 + v1) / 0.5f) + ((c2 & 0x00FF00) * (u2 + v2) / 0.5f) + ((c3 & 0x00FF00) * (u3 + v3) / 0.5f)) |
					(int)(((c1 & 0x0000FF) * (u1 + v1) / 0.5f) + ((c2 & 0x0000FF) * (u2 + v2) / 0.5f) + ((c3 & 0x0000FF) * (u3 + v3) / 0.5f)));
			}
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
