/** camera.cpp **/

#include "camera.hpp"
#include <cmath>

camera_c::camera_c() {
	x = 0;
	y = 0;
	dist = 8;
}

void camera_c::move() {
	if(playerinputs[SDLK_RIGHT]) x+= 0.02;
	if(playerinputs[SDLK_LEFT]) x-= 0.02;
	if(playerinputs[SDLK_UP]) y+= 0.1;
	if(playerinputs[SDLK_DOWN]) y-= 0.1;
	if(playerinputs[SDLK_KP_PLUS]) dist+= 0.1;
	if(playerinputs[SDLK_KP_MINUS]) dist-= 0.1;
	if(playerinputs[SDLK_KP0]) {
		x = 0;
		y = 0;
		dist = 8;
	}
}

void camera_c::draw(const int d) const {
	glLoadIdentity();
	const float temp_x = x + (DRAW_3D ? ((float)d / 10.0 - 0.05) : 0);
	gluLookAt(sin(temp_x) * dist, y, cos(temp_x) * dist, 0, 0, 0, 0, 1, 0);
	glFogf(GL_FOG_START, sqrt(dist * dist + y * y) - 2);
	glFogf(GL_FOG_END, sqrt(dist * dist + y * y) + 3);
}
