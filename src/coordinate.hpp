/** coordinate.hpp **/

#ifndef COORDINATE_HPP
#define COORDINATE_HPP

#include "global.hpp"

class coordinate_c {
	public:
		float x, y, z, w;
		coordinate_c(const float X, const float Y, const float Z, const float W); //Common
		coordinate_c(const unsigned char id); //This is for tesseract
		bool test_line_connection(const coordinate_c &other) const;
		bool test_face_connection(const coordinate_c &other1, const coordinate_c &other2, const coordinate_c &other3) const;
		void set_color(const float alpha) const;
		void draw_vertex(const float A, const float B, const float C) const;
};

#endif
