/** draw_3d.cpp **/

#include "global.hpp"

/*

	This here handles the magical cross-eyed/parallel 3D thing.

*/

void draw_3d_1(const unsigned char ddd_state) {
	if(ddd_state == 0) {
		glClear(GL_COLOR_BUFFER_BIT);
		glViewport(CROSS_EYED ? WIDTH : 0, 0, WIDTH, HEIGHT);
	}
	else glViewport(CROSS_EYED ? 0 : WIDTH, 0, WIDTH, HEIGHT);
}

void draw_3d_2(const unsigned char ddd_state) {
	if(ddd_state) {
		//Draw the vertical middle line
		glViewport(WIDTH - 1, 0, 2, HEIGHT);
		glLoadIdentity();
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		glBegin(GL_TRIANGLE_STRIP);
			glVertex2f(-1, -1); glVertex2f(1, -1); glVertex2f(-1, 1); glVertex2f(1, 1);
		glEnd();
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		SDL_GL_SwapBuffers();
	}
}
