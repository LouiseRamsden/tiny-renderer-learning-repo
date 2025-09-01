#include "tgaimage.h"
#include "gfxlib.h"


int main(int argc, char** argv) 
{
	TGAImage image(500, 500, TGAImage::RGB);
	line(4, 4, 80, 20, image, green);
	line(1, 1, 70, 99, image, red);
	line(50, 50, 0, 0, image, blue);
	image.flip_vertically(); // set origin to bottom left
	image.write_tga_file("output//output.tga");
	return 0;
}