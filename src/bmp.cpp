/** bmp.cpp **/

#include <cstdio>

//Returns data in RGB format starting from top left corner of the image
//Supports 24 and 32 bit bmp:s without alpha
unsigned char *load_bmp(const char *path, unsigned int &width, unsigned int &height) {
	width = 0;
	height = 0;
	FILE *file = fopen(path, "rb");
	if(file == NULL) {
		printf("Couldn't open file %s!\n", path);
		return NULL;
	}
	for(unsigned char i=0;i<18;i++) getc(file);
	for(unsigned char i=0;i<4;i++) width+= getc(file) << (i * 8);
	for(unsigned char i=0;i<4;i++) height+= getc(file) << (i * 8);
	getc(file); getc(file);
	unsigned char bpp = getc(file); //Bits per pixel
	if(bpp != 24 && bpp != 32) {
		printf("Bitmap format %i bits per pixel not supported!\n", bpp);
		return NULL;
	}
	for(unsigned char i=0;i<25;i++) getc(file);
	unsigned char *pixels = new unsigned char[width * height * 3];
	for(unsigned int i=0;i<height;i++) {
		for(unsigned int j=0;j<width;j++) {
			pixels[((height - i - 1) * width + j) * 3 + 2] = getc(file);
			pixels[((height - i - 1) * width + j) * 3 + 1] = getc(file);
			pixels[((height - i - 1) * width + j) * 3] = getc(file);
			if(bpp == 32) getc(file);
		}
		if(bpp == 24 && width % 4 != 0) {
			 for(unsigned char i=0;i<4-width*3%4;i++) getc(file);
		}
	}
	fclose(file);
	printf("Loaded %i bit bmp.\n", bpp);
	return pixels;
}
