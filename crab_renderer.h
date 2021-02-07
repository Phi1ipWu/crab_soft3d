
#ifndef __CRAB_RENDERER_H_
#define __CRAB_RENDERER_H_

typedef void (*func_draw_point)(int, int, int);

typedef struct tag_renderer
{
	int screen_sx, screen_sy;
	func_draw_point draw_point;
	float* z_buffer;
}
renderer;


renderer* create_renderer(int screen_sx, int screen_sy, func_draw_point func);
void destroy_renderer(renderer* r);
void begin_render(renderer* r);
void render(renderer* r);
void end_render(renderer* r);


#endif
