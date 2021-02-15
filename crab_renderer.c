
#include "crab_renderer.h"
#include "crab_algebra.h"
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
	int x, y;
	vector2 vp, vp1, vp2, vp3, v_min, v_max;
	vector2 uv, uv1, uv2, uv3;
	int c, c_v, c_t, c1, c2, c3;
	float area;

	//v1.x = rand() % r->screen_sx, v1.y = rand() % r->screen_sy;
	//v2.x = rand() % r->screen_sx, v2.y = rand() % r->screen_sy;
	//v3.x = rand() % r->screen_sx, v3.y = rand() % r->screen_sy;
	vp1.x = 100, vp1.y = 100;
	vp2.x = 230, vp2.y = 500;
	vp3.x = 500, vp3.y = 230;
	c1 = 0xFFFF0000;
	c2 = 0xFF00FF00;
	c3 = 0xFF0000FF;
	uv1.x = 0.0f, uv1.y = 0.0f;
	uv2.x = 1.0f, uv2.y = 0.0f;
	uv3.x = 0.0f, uv3.y = 1.0f;

	area = crab_vector2_triangle_area(&vp1, &vp2, &vp3);

	v_min.x = min(vp1.x, min(vp2.x, vp3.x));
	v_min.y = min(vp1.y, min(vp2.y, vp3.y));
	v_max.x = max(vp1.x, max(vp2.x, vp3.x));
	v_max.y = max(vp1.y, max(vp2.y, vp3.y));
	for (y = v_min.y; y <= v_max.y; ++y)
	{
		for (x = v_min.x; x <= v_max.x; ++x)
		{
			vp.x = x, vp.y = y;
			if (crab_vector2_in_triangle(&vp, &vp1, &vp2, &vp3))
			{
				float area, area1, area2, area3, sum;
				area  = crab_vector2_triangle_area(&vp1, &vp2, &vp3);
				area1 = crab_vector2_triangle_area(&vp, &vp2, &vp3);
				area2 = crab_vector2_triangle_area(&vp, &vp1, &vp3);
				area3 = crab_vector2_triangle_area(&vp, &vp1, &vp2);
				sum = area1 + area2 + area3;

				uv.x = uv1.x * (area1 / sum) + uv2.x * (area2 / sum) + uv3.x * (area3 / sum);
				uv.y = uv1.y * (area1 / sum) + uv2.y * (area2 / sum) + uv3.y * (area3 / sum);

				c_v = (0xFF << 24) | ((int)((area1 / sum) * 0xFF) << 16) | ((int)((area2 / sum) * 0xFF) << 8 ) | ((int)((area3 / sum) * 0xFF));
				c_t = get_texture_color(r->texture_list[0], uv.x, uv.y);

				c = ((((c_v >> 24) & 0xFF) + ((c_t >> 24) & 0xFF)) / 2 << 24) |
					((((c_v >> 16) & 0xFF) + ((c_t >> 16) & 0xFF)) / 2 << 16) |
					((((c_v >>  8) & 0xFF) + ((c_t >>  8) & 0xFF)) / 2 <<  8) |
					((((c_v >>  0) & 0xFF) + ((c_t >>  0) & 0xFF)) / 2 <<  0);
				r->draw_point(x, y, c);
			}
		}
	}

	if (0 && r->texture_list[0])
	{
		int width, height;
		width  = r->texture_list[0]->width;
		height = r->texture_list[0]->height;
		for (y = 0; y < height; ++y)
		{
			for (x = 0; x < width; ++x)
			{
				r->draw_point(x, y, r->texture_list[0]->data[y * width + x]);
			}
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

unsigned int get_texture_color(texture* t, float u, float v)
{
	int x, y;
	unsigned int c;

	if (!t)
		return 0xFFFFFFFF;

	x = (int)(u * t->width)  % t->width;
	y = (int)(v * t->height) % t->height;
	
	c = t->data[y * t->width + x];
	return c;
}
