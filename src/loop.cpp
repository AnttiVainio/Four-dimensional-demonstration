/** loop.cpp **/

#include "loop.hpp"

void loop(const unsigned char choise) {
	tesseract_c *tesseract = 0;
	three_sphere_c *three_sphere = 0;
	switch(choise) {
		case 0: return;
		case 1:
			tesseract = new tesseract_c;
			break;
		case 2:
			three_sphere = new three_sphere_c(12, 5, 21);
			break;
		case 3:
			three_sphere = new three_sphere_c(3, 10, 1001);
			break;
	}
	camera_c camera;
	SDL_Event event;
	bool exit = false;
	int starttime = SDL_GetTicks() - 10;
	int endtime = 0;

	//Here goes the loop
	while(!exit) {
		starttime+= 10;

		playerinputs = SDL_GetKeyState(NULL);

		camera.move();

		if(choise == 1) tesseract->move();
		else three_sphere->move();

		//DRAW
		for(int d=0;d<(DRAW_3D?2:1);d++) {
			if(DRAW_3D) draw_3d_1(d);
			else glClear(GL_COLOR_BUFFER_BIT);

			camera.draw(d);

			if(choise == 1) tesseract->draw();
			else three_sphere->draw();

			if(DRAW_3D) draw_3d_2(d);
			else SDL_GL_SwapBuffers();
		}

		//REST
		endtime = SDL_GetTicks() - starttime;
		if(10 - endtime > 0) SDL_Delay(10 - endtime);
		else starttime = SDL_GetTicks() - 10;

		while(SDL_PollEvent(&event)) {
			if(event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)) exit = true;
		}
	}
	delete tesseract;
	delete three_sphere;
}
