

#include "gfxlib.h"
#include "geometry.h"




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

std::tuple<Vec2i, Vec2i>const& findBoundingBox(int ax, int ay, int bx, int by, int cx, int cy) 
{
	Vec2i min, max;

	min = {
		std::min(ax,std::min(bx,cx)),
		std::min(ay, std::min(by,cy))
	};
	max = {
		std::max(ax,std::max(bx,cx)),
		std::max(ay, std::max(by,cy))
	};
	return { min, max };
}

constexpr double signedTriangleArea(int ax, int ay, int bx, int by, int cx, int cy) 
{
	return 0.5 * ((by - ay) * (bx + ax) + (cy - by) * (cx + bx) + (ay - cy) * (ax + cx));
}

void triangle(int ax, int ay, int az, int bx, int by, int bz, int cx, int cy, int cz, TGAImage& zbuffer, TGAImage& framebuffer, TGAColor const& color) 
{
	auto [bbMin, bbMax] = findBoundingBox(ax, ay, bx, by, cx, cy);

	double totalArea = signedTriangleArea(ax,ay,bx,by,cx,cy);
	if (totalArea < 1) return;

#pragma omp parallel for
	for (int x = bbMin.x; x <= bbMax.x; x++) 
	{
		for (int y = bbMin.y; y <= bbMax.y; y++) 
		{
			//find barycentric coordinates for each pixel in bounding box
			//discard if negative

			//barycentric coordinates are equivalent to: 
			// a = Area(point, B,C) / totalArea, b = Area(point, C, A) / totalArea, g = Area(point, A,B) / totalArea
			double a = signedTriangleArea(x,y,bx,by,cx,cy) / totalArea;
			double b = signedTriangleArea(x,y,cx,cy,ax,ay) / totalArea;
			double g = signedTriangleArea(x,y,ax,ay,bx,by) / totalArea;
			if (a < 0 || b < 0 || g < 0) continue;
			uint8_t z = (uint8_t)(a * az + b * bz + g * cz);
			if (z <= zbuffer.get(x, y).val) continue; //if the value is further than the current one on the zbuffer, dont draw it
			zbuffer.set(x, y, {z,z,z,255});
			framebuffer.set(x, y, color);
		}
	}
}