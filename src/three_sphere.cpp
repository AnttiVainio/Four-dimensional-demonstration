/** three_sphere.cpp **/

#include "three_sphere.hpp"
#include "math.hpp"
#include <cmath>

#define SPEED 0.01 //rotation speed

three_sphere_c::three_sphere_c(const unsigned char I, const unsigned char TI, const unsigned short TS):
	INTERVAL(I), //defines the accuracy of the 3-sphere
	TRAIL_INTERVAL(TI), //defines the accuracy of the trail
	TRAIL_SIZE(TS) { //should be 1 + a * TRAIL_INTERVAL (to prevent waste)
	rotationA = new float[TRAIL_SIZE];
	rotationB = new float[TRAIL_SIZE];
	rotationC = new float[TRAIL_SIZE];
	for(int i=0;i<TRAIL_SIZE;i++) {
		rotationA[i] = 0;
		rotationB[i] = 0;
		rotationC[i] = 0;
	}
	float *intervals = new float[INTERVAL * 2];
	for(int i=0;i<INTERVAL;i++)
		intervals[i] = 4.0 / 2.0 / (float)INTERVAL
		+ linear_function(0, INTERVAL - 1, -4.5 / 2.0 / (float)INTERVAL, 4.5 / 2.0 / (float)INTERVAL, i);
	for(int i=INTERVAL;i<INTERVAL*2-1;i++) intervals[i] = intervals[INTERVAL * 2 - i - 1];
	int a = 0;
	for(float i=-2;i<=2;i+=intervals[a]) {
		int b = 0;
		for(float j=-2;j<=2;j+=intervals[b]) {
			int c = 0;
			for(float k=-2;k<=2;k+=intervals[c]) {
				const float distance = 4 - i * i - j * j - k * k;
				if(distance >= 0) {
					coordinates.push_back(coordinate_c(i, j, k, sqrt(distance)));
					coordinates.push_back(coordinate_c(i, j, k, -sqrt(distance)));
				}
				c++;
			}
			b++;
		}
		a++;
	}
	delete [] intervals;
}

three_sphere_c::~three_sphere_c() {
	delete [] rotationA;
	delete [] rotationB;
	delete [] rotationC;
}

void three_sphere_c::move() {
	for(int i=TRAIL_SIZE-1;i>0;i--) {
		rotationA[i] = rotationA[i - 1];
		rotationB[i] = rotationB[i - 1];
		rotationC[i] = rotationC[i - 1];
	}
	if(playerinputs[SDLK_q]) rotationA[0]+= SPEED;
	if(playerinputs[SDLK_a]) rotationA[0]-= SPEED;
	if(playerinputs[SDLK_w]) rotationB[0]+= SPEED;
	if(playerinputs[SDLK_s]) rotationB[0]-= SPEED;
	if(playerinputs[SDLK_e]) rotationC[0]+= SPEED;
	if(playerinputs[SDLK_d]) rotationC[0]-= SPEED;
	if(playerinputs[SDLK_KP0]) {
		rotationA[0] = 0;
		rotationB[0] = 0;
		rotationC[0] = 0;
	}
}

void three_sphere_c::draw() const {
	for(unsigned int i=0;i<coordinates.size();i++) {
		glBegin(GL_POINTS);
			coordinates.at(i).set_color(1);
			coordinates.at(i).draw_vertex(rotationA[0], rotationB[0], rotationC[0]);
		glEnd();
		glBegin(GL_LINES);
			coordinates.at(i).draw_vertex(rotationA[0], rotationB[0], rotationC[0]);
			for(unsigned short j=TRAIL_INTERVAL;j<TRAIL_SIZE;j+=TRAIL_INTERVAL) {
				coordinates.at(i).set_color(1.0 - j / float(TRAIL_SIZE - 1));
				for(unsigned short a=0;a<2;a++) coordinates.at(i).draw_vertex(rotationA[j], rotationB[j], rotationC[j]);
			}
		glEnd();
	}
	glColor4f(1, 1, 1, 1);
}
