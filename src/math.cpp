/** math.cpp **/

float linear_function(const float x1, const float x2, const float y1, const float y2, const float x) {
	return (y1 - y2) / (x1 - x2) * (x - x1) + y1;
}
