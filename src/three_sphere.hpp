/** three_sphere.hpp **/

#ifndef THREE_SPHERE_HPP
#define THREE_SPHERE_HPP

#include "global.hpp"
#include "coordinate.hpp"
#include <vector>

class three_sphere_c {
	private:
		const unsigned char INTERVAL;
		const unsigned char TRAIL_INTERVAL;
		const unsigned short TRAIL_SIZE;
		std::vector<coordinate_c> coordinates;
		float *rotationA, *rotationB, *rotationC;

	public:
		three_sphere_c(const unsigned char I, const unsigned char TI, const unsigned short TS);
		~three_sphere_c();
		void move();
		void draw() const;
};

#endif
