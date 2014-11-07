/** tesseract.cpp **/

#include "tesseract.hpp"
#include "math.hpp"

tesseract_c::tesseract_c() {
	rotationA = 0;
	rotationB = 0;
	rotationC = 0;
	for(unsigned char i=0;i<16;i++) coordinates.push_back(coordinate_c(i));
	for(unsigned char i=0;i<16;i++) {
		for(unsigned char j=i+1;j<16;j++) {
			if(coordinates.at(i).test_line_connection(coordinates.at(j)))
				lines.push_back(indexpair(i,j));
		}
	}
	for(unsigned char i=0;i<16;i++) {
		for(unsigned char j=i+1;j<16;j++) {
			for(unsigned char k=j+1;k<16;k++) {
				for(unsigned char l=k+1;l<16;l++) {
					if(coordinates.at(i).test_face_connection(coordinates.at(j), coordinates.at(k), coordinates.at(l)))
						faces.push_back(std::pair<indexpair,indexpair>(indexpair(i,j),indexpair(k,l)));
				}
			}
		}
	}
}

void tesseract_c::move() {
	if(playerinputs[SDLK_q]) rotationA+= 0.01;
	if(playerinputs[SDLK_a]) rotationA-= 0.01;
	if(playerinputs[SDLK_w]) rotationB+= 0.01;
	if(playerinputs[SDLK_s]) rotationB-= 0.01;
	if(playerinputs[SDLK_e]) rotationC+= 0.01;
	if(playerinputs[SDLK_d]) rotationC-= 0.01;
	if(playerinputs[SDLK_KP0]) {
		rotationA = 0;
		rotationB = 0;
		rotationC = 0;
	}
}

void tesseract_c::draw() const {
	for(unsigned int i=0;i<lines.size();i++) {
		glBegin(GL_LINES);
			coordinates.at(lines.at(i).first).draw_vertex(rotationA, rotationB, rotationC);
			coordinates.at(lines.at(i).second).draw_vertex(rotationA, rotationB, rotationC);
		glEnd();
	}
	for(unsigned int i=0;i<faces.size();i++) {
		glColor4f(linear_function(0, faces.size() - 1, 0, 2, i), linear_function(0, faces.size() - 1, 2, 0, i), 0, 0.1);
		glBegin(GL_TRIANGLE_STRIP);
			coordinates.at(faces.at(i).first.first).draw_vertex(rotationA, rotationB, rotationC);
			coordinates.at(faces.at(i).first.second).draw_vertex(rotationA, rotationB, rotationC);
			coordinates.at(faces.at(i).second.first).draw_vertex(rotationA, rotationB, rotationC);
			coordinates.at(faces.at(i).second.second).draw_vertex(rotationA, rotationB, rotationC);
		glEnd();
	}
	glColor4f(1, 1, 1, 1);
}
