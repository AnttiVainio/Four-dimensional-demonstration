/** menu.cpp **/

#include "menu.hpp"
#include "bmp.hpp"

unsigned char menu() {
	SDL_Event event;
	bool exit = false;
	int starttime = SDL_GetTicks() - 10;
	int endtime = 0;

	//Load info textures
	unsigned int width, height;
	unsigned char *pixels = load_bmp("img/info1.bmp", width, height);
	GLuint info_tex1;
	glGenTextures(1, &info_tex1);
	glBindTexture(GL_TEXTURE_2D, info_tex1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	if(pixels != NULL) {
		glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
		delete [] pixels;
	}
	pixels = load_bmp("img/info2.bmp", width, height);
	GLuint info_tex2;
	glGenTextures(1, &info_tex2);
	glBindTexture(GL_TEXTURE_2D, info_tex2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	if(pixels != NULL) {
		glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
		delete [] pixels;
	}

	//Here goes the loop
	while(!exit) {
		starttime+= 10;

		playerinputs = SDL_GetKeyState(NULL);

		if(playerinputs[SDLK_1]) {
			glDeleteTextures(1, &info_tex1);
			glDeleteTextures(1, &info_tex2);
			return 1;
		}
		if(playerinputs[SDLK_2]) {
			glDeleteTextures(1, &info_tex1);
			glDeleteTextures(1, &info_tex2);
			return 2;
		}
		if(playerinputs[SDLK_3]) {
			glDeleteTextures(1, &info_tex1);
			glDeleteTextures(1, &info_tex2);
			return 3;
		}

		//DRAW
		glClear(GL_COLOR_BUFFER_BIT);

		glPushMatrix();
		glLoadIdentity();
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		glEnable(GL_TEXTURE_2D);
		glDisable(GL_FOG);
		glBindTexture(GL_TEXTURE_2D, info_tex1);
		glBegin(GL_TRIANGLE_STRIP);
			glTexCoord2f(0.0, 1.0); glVertex3f(-1, 0.5, -1);
			glTexCoord2f(1.0, 1.0); glVertex3f(1, 0.5, -1);
			glTexCoord2f(0.0, 0.0); glVertex3f(-1, 1, -1);
			glTexCoord2f(1.0, 0.0); glVertex3f(1, 1, -1);
		glEnd();
		glBindTexture(GL_TEXTURE_2D, info_tex2);
		glBegin(GL_TRIANGLE_STRIP);
			glTexCoord2f(0.0, 1.0); glVertex3f(-1, 0, -1);
			glTexCoord2f(1.0, 1.0); glVertex3f(1, 0, -1);
			glTexCoord2f(0.0, 0.0); glVertex3f(-1, 0.5, -1);
			glTexCoord2f(1.0, 0.0); glVertex3f(1, 0.5, -1);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glEnable(GL_FOG);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();

		SDL_GL_SwapBuffers();

		//REST
		endtime = SDL_GetTicks() - starttime;
		if(10 - endtime > 0) SDL_Delay(10 - endtime);
		else starttime = SDL_GetTicks() - 10;

		while(SDL_PollEvent(&event)) {
			if(event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)) exit = true;
		}
	}
	return 0;
}
