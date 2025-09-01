#include "tgaimage.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);
const TGAColor blue = TGAColor(0, 0, 255, 255);
const TGAColor green = TGAColor(0, 255, 0,255);
void line(int x0, int y0, int x1, int y1, TGAImage& image, TGAColor const& color) 
{
	//determine which axis is the steepest, then swap and transpose
	bool steep = false;
	if (std::abs(x0 - x1) < std::abs(y0 - y1)) 
	{
		std::swap(x0, y0);
		std::swap(x1, y1);
		steep = true;
	}
	if(x0 > x1)
	{
		std::swap(x0, x1);
		std::swap(y0, y1);
	}
	//difference between both points
	int dx = x1 - x0;
	int dy = y1 - y0;
	int derror2 = std::abs(dy) * 2; //derror2 because its equivalent to abs(dy) * 2
	int error2 = 0;
	int y = y0;
	
	//for every x pixel
	for (int x = x0; x <= x1; x++) 
	{
		if (steep) 
		{
			image.set(y, x, color);
		}
		else 
		{
			image.set(x, y, color);
		}

		//every loop add to error2, if its greater than 0.5f then start drawing on the next pixel of y 
		error2 += derror2;
		if (error2 > dx) 
		{
			y += (y1 > y0 ? 1 : -1); //if first point is above or below adjust accordingly
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