/** coordinate.cpp **/

#include "coordinate.hpp"
#include "math.hpp"
#include <cmath>

/*

	The w-component of a coordinate is simulated so that:
		when it is 0 the coordinate remains unchanged
		when it's > 1 the coordinate travels away from the origin
		when it's < 1 the coordinate travels towards the origin

	The x, y, z and w components remain same all the time.
	The coordinate is not transformed until it is drawn in draw_vertex();

*/

coordinate_c::coordinate_c(const float X, const float Y, const float Z, const float W) {
	x = X;
	y = Y;
	z = Z;
	w = W;
}

inline float transform_coord(const float a) {
	return linear_function(0, 1, -1, 1, a);
}

coordinate_c::coordinate_c(const unsigned char id) {
	x = transform_coord(id & 1);
	y = transform_coord(id >> 1 & 1);
	z = transform_coord(id >> 2 & 1);
	w = transform_coord(id >> 3 & 1);
}

bool coordinate_c::test_line_connection(const coordinate_c &other) const {
	int count = 0;
	if(x != other.x) count++;
	if(y != other.y) count++;
	if(z != other.z) count++;
	if(w != other.w) count++;
	return count == 1 ? true : false;
}

bool coordinate_c::test_face_connection(const coordinate_c &other1, const coordinate_c &other2, const coordinate_c &other3) const {
	int count = 0;
	if(x == other1.x && x == other2.x && x == other3.x) count++;
	if(y == other1.y && y == other2.y && y == other3.y) count++;
	if(z == other1.z && z == other2.z && z == other3.z) count++;
	if(w == other1.w && w == other2.w && w == other3.w) count++;
	return count == 2 ? true : false;
}

void coordinate_c::set_color(const float alpha) const {
	glColor4f(1.0 - x, 1.0 - y, 1.0 - z, alpha);
}

/*
	Used rotation matrix:
	  cA    zAsB  zAcBsC zAcBcC
	   0     cB    zBsC   zBcC
	   0      0     cC     zC
	  sA    cAsB  cAcBsC cAcBcC
	where:
	ABC = rotations
	c = cos
	s = sin
	z = -sin

	Coordinates:
	x = xcA - ysAsB - zsAcBsC - wsAcBcC
	y = ycB - zsBsC - wsBcC
	z = zcC - wsC
	w = xsA + ycAsB + zcAcBsC + wcAcBcC
*/

void coordinate_c::draw_vertex(const float A, const float B, const float C) const {
	//rotation: a * cos(rot) - b * sin(rot) and a * sin(rot) + b * cos(rot)
	const float sa = sin(A);
	const float ca = cos(A);
	const float sb = sin(B);
	const float cb = cos(B);
	const float sc = sin(C);
	const float cc = cos(C);
	const float dddd = pow(2, x * sa + y * ca * sb + z * ca * cb * sc + w * ca * cb * cc); //Projection to three dimensions
	glVertex3f(
		(x * ca - y * sa * sb - z * sa * cb * sc - w * sa * cb * cc) * dddd,
		(y * cb - z * sb * sc - w * sb * cc) * dddd,
		(z * cc - w * sc) * dddd);
}
