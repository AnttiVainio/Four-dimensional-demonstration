/** main.cpp **/

#include "main.hpp"

/*

	This program lets you rotate a tesseract and a 3-sphere in four dimensions.

	A tesseract is a four dimensional cube like object. Basically, a tesseract is formed from a cube in a same way as a cube is formed from a square or a square is formed from a line.

	A 3-sphere is a four dimensional sphere like object. Its form is much more complex than the one of a tesseract and is much more difficult to understand (even I don't really understand it).
	The rendering of the 3-sphere is executed so that the program draws dots that are on the surface of the 3-sphere and as the dots move they leave a trail behind.

	The program uses cross-eyed 3D rendering. Basically if you can cross your eyes so that the two images next to each other combine so that the resulting image is sharp you will see the image in real 3D.

	NOTES:
	The interesting four dimensional transformation and projection stuff can be found in coordinate.cpp
	There is also an option for parallel 3D instead of cross-eyed 3D
	  This option can be enabled in global.hpp
	  If you use parallel 3D you should probably lower the resolution below

*/

const short WIDTH = 512; //doubled for the 3D rendering
const short HEIGHT = 576;
Uint8 *playerinputs;

void log(const char *text) { printf("%s\n", text); }

int main(int argc, char **argv) {
	//Starting SDL
	if(SDL_Init(SDL_INIT_VIDEO) != 0) {
		printf("SDL_Init error: %s\n", SDL_GetError());
		throw 0;
	}

	SDL_WM_SetCaption("4D", "4D");
	SDL_ShowCursor(1);

	//OpenGL settings
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 16);

	//Starting OpenGL
	if(SDL_SetVideoMode(WIDTH * (DRAW_3D ? 2 : 1), HEIGHT, 0, SDL_OPENGL) == NULL) {
		printf("SDL_SetVideoMode error: %s\n", SDL_GetError());
		printf("Couldn't initialize OpenGL with the default settings! Trying other settings...\n");
		bool success = false;
		for(int i=0;i<2;i++) {
			if(i == 1) {
				printf("Trying with 16 bit colors...\n");
				SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 4);
				SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 4);
				SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 4);
				SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 4);
				SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 16);
				SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
				SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 16);
				printf("Trying with 16 x multisampling.\n");
				if(SDL_SetVideoMode(WIDTH * (DRAW_3D ? 2 : 1), HEIGHT, 0, SDL_OPENGL) == NULL)
					printf("SDL_SetVideoMode error: %s\n", SDL_GetError());
				else success = true;
			}
			if(success) break;
			for(int j=8;j>=2;j/=2) {
				SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, j);
				printf("Trying with %i x multisampling.\n", j);
				if(SDL_SetVideoMode(WIDTH * (DRAW_3D ? 2 : 1), HEIGHT, 0, SDL_OPENGL) == NULL)
					printf("SDL_SetVideoMode error: %s\n", SDL_GetError());
				else { j = 0; success = true; }
			}
			if(success) break;
			SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 0);
			SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 0);
			printf("Trying without multisampling.\n");
			if(SDL_SetVideoMode(WIDTH * (DRAW_3D ? 2 : 1), HEIGHT, 0, SDL_OPENGL) == NULL)
				printf("SDL_SetVideoMode error: %s\n", SDL_GetError());
			else break;
			if(i == 1) throw 1;
		}
	}

	//Check the got values
	int value;
	char text[30];
	SDL_GL_GetAttribute(SDL_GL_BUFFER_SIZE, &value);
	sprintf(text, "Frame buffer size: %i / %i", value, 32);
	log(text);
	SDL_GL_GetAttribute(SDL_GL_DEPTH_SIZE, &value);
	sprintf(text, "Depth buffer size: %i / %i", value, 24);
	log(text);
	SDL_GL_GetAttribute(SDL_GL_DOUBLEBUFFER, &value);
	if(value) log("Got doublebuffering");
	else log("Couldn't get doublebuffering");
	SDL_GL_GetAttribute(SDL_GL_MULTISAMPLEBUFFERS, &value);
	if(value) {
		SDL_GL_GetAttribute(SDL_GL_MULTISAMPLESAMPLES, &value);
		sprintf(text, "Got %i x multisampling", value);
		log(text);
	}
	else log("Didn't get multisampling");

	//OpenGL setting
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_FOG);
	const float fog_color[3] = {0, 0, 0};
	glFogfv(GL_FOG_COLOR, fog_color);
	glFogi(GL_FOG_MODE, GL_LINEAR);

	glViewport(0, 0, WIDTH, HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65, (float)WIDTH / (float)HEIGHT, 0.1, 100);
	glMatrixMode(GL_MODELVIEW);
	glColor4f(1, 1, 1, 1);
	glClearColor(0, 0, 0, 1);

	loop(menu());

	SDL_Quit();
	return 0;
}
