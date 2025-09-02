#include "gfxlib.h"



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
	if (ax > bx)
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

void triangle(int ax, int ay, int bx, int by, int cx, int cy, TGAImage& framebuffer, TGAColor const& color) 
{
	line(ax, ay, bx, by, framebuffer, color);
	line(bx, by, cx, cy, framebuffer, color);
	line(cx, cy, ax, ay, framebuffer, color);
}