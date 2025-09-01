#include "tgaimage.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);
const TGAColor blue = TGAColor(0, 0, 255, 255);
const TGAColor green = TGAColor(0, 255, 0,255);

/*
* line()
* assuming line isnt steep
* 
* for every pixel of the x axis
*	add pixel
*	if y delta > 0.5 then
*		move y up a pixel
* 
* steepness switches axis and makes it mirrored
* 
* the optimization essentially just removes the floats by using dy * 2 and dx * 2 but it essentially works the same just with alot less floating point maths
* 
*/
void line(int ax, int ay, int bx, int by, TGAImage& framebuffer, TGAColor const& color) 
{
	//determine which axis is the steepest, then swap and transpose
	bool steep = std::abs(ax - bx) < std::abs(ay - by);
	if (steep) 
	{
		std::swap(ax, ay);
		std::swap(bx, by);
	}
	if(ax > bx)
	{
		std::swap(ax, bx);
		std::swap(ay, by);
	}
	//difference between both points
	int dx = bx - ax;
	int dy = by - ay;
	int derror2 = std::abs(dy) * 2; //derror2 because its equivalent to abs(dy) * 2
	int error2 = 0;
	int y = ay;
	
	//for every x pixel
	for (int x = ax; x <= bx; x++) 
	{
		if (steep) 
		{
			framebuffer.set(y, x, color);
		}
		else 
		{
			framebuffer.set(x, y, color);
		}

		error2 += derror2;
		if (error2 > dx) 
		{
			y += (by > ay ? 1 : -1); //if first point is above or below adjust accordingly
			error2 -= dx * 2;
		}
	}
}



int main(int argc, char** argv) 
{
	TGAImage image(100, 100, TGAImage::RGB);
	line(4, 4, 80, 20, image, green);
	line(1, 1, 70, 99, image, blue);
	image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	image.write_tga_file("output//output.tga");
	return 0;
}