
#ifndef __CRAB_RENDERER_H_
#define __CRAB_RENDERER_H_

#include "crab_algebra.h"

///////////////////////////////////////////////////////////////////////////////
typedef struct tag_texture
{
	int width, height;
	unsigned int data[1];
}
texture;

typedef void (*func_draw_point)(int, int, unsigned int);
typedef struct tag_renderer
{
	int screen_sx, screen_sy;
	func_draw_point draw_point;
	float* z_buffer;
	texture* texture_list[4];
}
renderer;

renderer* create_renderer(int screen_sx, int screen_sy, func_draw_point func);
void destroy_renderer(renderer* r);
void begin_render(renderer* r);
void render(renderer* r);
void end_render(renderer* r);

///////////////////////////////////////////////////////////////////////////////
void draw_triangles(const vector3* v, int vec_num, const unsigned int* c, int color_num, const vector2* uv, int uv_num);

///////////////////////////////////////////////////////////////////////////////
texture* create_texture(const char* name);
void destroy_texture(texture* t);
void set_texture(renderer* r, int index, texture* t);
unsigned int texture_2d(texture* t, float u, float v);


#endif
