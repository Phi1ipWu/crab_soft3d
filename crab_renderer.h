
#ifndef __CRAB_RENDERER_H_
#define __CRAB_RENDERER_H_

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
texture* create_texture(const char* name);
void destroy_texture(texture* t);
void set_texture(renderer* r, int index, texture* t);
unsigned int get_texture_color(texture* t, float u, float v);


#endif
