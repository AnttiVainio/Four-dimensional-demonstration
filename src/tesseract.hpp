/** tesseract.hpp **/

#ifndef TESSERACT_HPP
#define TESSERACT_HPP

#include "global.hpp"
#include "coordinate.hpp"
#include <vector>
#include <utility>

typedef std::pair<unsigned char, unsigned char> indexpair;

class tesseract_c {
	private:
		std::vector<coordinate_c> coordinates;
		std::vector<indexpair> lines;
		std::vector<std::pair<indexpair, indexpair> > faces;
		float rotationA, rotationB, rotationC;

	public:
		tesseract_c();
		void move();
		void draw() const;
};

#endif
