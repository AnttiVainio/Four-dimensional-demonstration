/** camera.hpp **/

#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "global.hpp"

class camera_c {
	private:
		float x, y, dist;

	public:
		camera_c();
		void move();
		void draw(const int d) const;
};

#endif
