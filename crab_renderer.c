
#include "crab_renderer.h"
#include <stdlib.h>
#include <stdio.h>

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
	vector3 v[3];
	unsigned int c[3];
	vector2 uv[3];

	v[0].x = 100, v[0].y = 100, v[0].z = 0;
	v[1].x = 230, v[1].y = 500, v[1].z = 0;
	v[2].x = 500, v[2].y = 230, v[2].z = 0;
	c[0] = 0xFFFF0000;
	c[1] = 0xFF00FF00;
	c[2] = 0xFF0000FF;
	uv[0].x = 0.0f, uv[0].y = 0.0f;
	uv[1].x = 2.0f, uv[1].y = 0.0f;
	uv[2].x = 0.0f, uv[2].y = 2.0f;

	draw_triangles(r, v, 3, c, 3, uv, 3);
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
void draw_triangles(renderer* r, const vector3* v, int vec_num, const unsigned int* c, int color_num, const vector2* uv, int uv_num)
{
	int x, y;
	vector2 vp, vp0, vp1, vp2, v_min, v_max;
	vector2 uv0;
	float area;

	// transform
	vp0.x = v[0].x, vp0.y = v[0].y;
	vp1.x = v[1].x, vp1.y = v[1].y;
	vp2.x = v[2].x, vp2.y = v[2].y;

	// rasterization
	area = crab_vector2_triangle_area(&vp0, &vp1, &vp2);

	v_min.x = min(vp0.x, min(vp1.x, vp2.x));
	v_min.y = min(vp0.y, min(vp1.y, vp2.y));
	v_max.x = max(vp0.x, max(vp1.x, vp2.x));
	v_max.y = max(vp0.y, max(vp1.y, vp2.y));
	for (y = (int)v_min.y; y <= v_max.y; ++y)
	{
		for (x = (int)v_min.x; x <= v_max.x; ++x)
		{
			vp.x = (float)x, vp.y = (float)y;
			if (crab_vector2_in_triangle(&vp, &vp0, &vp1, &vp2))
			{
				float area, area0, area1, area2;
				unsigned int c_vect, c_tex0, c_out;

				area  = crab_vector2_triangle_area(&vp0, &vp1, &vp2);
				area0 = crab_vector2_triangle_area(&vp, &vp1, &vp2);
				area1 = crab_vector2_triangle_area(&vp, &vp0, &vp2);
				area2 = crab_vector2_triangle_area(&vp, &vp0, &vp1);
				uv0.x = uv[0].x * (area0 / area) + uv[1].x * (area1 / area) + uv[2].x * (area2 / area);
				uv0.y = uv[0].y * (area0 / area) + uv[1].y * (area1 / area) + uv[2].y * (area2 / area);

				c_vect = (0xFF << 24) | 
						 ((unsigned int)((area0 / area) * 0xFF) << 16) | 
						 ((unsigned int)((area1 / area) * 0xFF) << 8 ) | 
						 ((unsigned int)((area2 / area) * 0xFF));
				c_vect = 0xFFFFFFFF;
				c_tex0 = texture_2d(r->texture_list[0], uv0.x, uv0.y);

				c_out =	((unsigned int)(((((c_vect >> 24) & 0xFF) / 255.f) * (((c_tex0 >> 24) & 0xFF) / 255.f)) * 255) << 24) |
						((unsigned int)(((((c_vect >> 16) & 0xFF) / 255.f) * (((c_tex0 >> 16) & 0xFF) / 255.f)) * 255) << 16) |
						((unsigned int)(((((c_vect >>  8) & 0xFF) / 255.f) * (((c_tex0 >>  8) & 0xFF) / 255.f)) * 255) <<  8) |
						((unsigned int)(((((c_vect >>  0) & 0xFF) / 255.f) * (((c_tex0 >>  0) & 0xFF) / 255.f)) * 255) <<  0);
				r->draw_point(x, y, c_out);

			}
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
texture* create_texture(const char* name)
{
	int x, y, width, height, off_bytes;
	unsigned short bit_count;
	texture* tex;
	FILE* fp = fopen(name, "rb");
	if (!fp)
		return 0;

	fseek(fp, 10, SEEK_SET);
	fread(&off_bytes,  sizeof(int), 1, fp);
	fseek(fp, 18, SEEK_SET);
	fread(&width,  sizeof(int), 1, fp);
	fread(&height, sizeof(int), 1, fp);
	fseek(fp, 28, SEEK_SET);
	fread(&bit_count, sizeof(unsigned short), 1, fp);
	if (bit_count != 24)
	{
		fclose(fp);
		return 0;
	}

	tex = (texture*)malloc(sizeof(texture) + sizeof(unsigned int) * (width * height - 1));
	tex->width = width, tex->height = height;

	fseek(fp, off_bytes, SEEK_SET);
	for (y = 0; y < height; ++y)
		for (x = 0; x < width; ++x)
		{
			unsigned char c[3];
			fread(c, sizeof(c), 1, fp);
			tex->data[(height - y - 1) * width + x] = (0xFF << 24) | (c[2] << 16) | (c[1] << 8) | (c[0]);
		}
	
	fclose(fp);
	return tex;
}

void destroy_texture(texture* t)
{
	if (t)
		free(t);
}


void set_texture(renderer* r, int index, texture* t)
{
	//assert(0 <= index && index < 4);
	r->texture_list[index] = t;
}

unsigned int texture_2d(texture* t, float u, float v)
{
	int x, y;
	unsigned int c;

	if (!t)
		return 0xFFFFFFFF;

	if (0)
	{

	}
	else
	{
		x = (int)(u * t->width)  % t->width;
		y = (int)(v * t->height) % t->height;
	
		c = t->data[y * t->width + x];
	}
	return c;
}
