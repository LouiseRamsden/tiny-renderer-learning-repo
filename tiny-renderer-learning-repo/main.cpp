#include <tuple>

#include "tgaimage.h"
#include "gfxlib.h"
#include "model.h"


constexpr int g_width = 2000;
constexpr int g_height = 2000;
Model* model = nullptr;


std::tuple<int, int, int> projectTriangleToScreen(Vec3f v, int width, int height)
{
	return { 
		(int)(((v.x + 1.0f) * width) / 2.0f),
		(int)(((v.y + 1.0f) * height) / 2.0f),
		(int)(((v.z + 1.0f) * 255) / 2.0f)
	};
}
int main(int argc, char** argv) 
{

	model = new Model("assets//diablo3_pose.obj");
	
	TGAImage framebuffer(g_width, g_height, TGAImage::RGB);
	TGAImage zbuffer(g_width, g_height, TGAImage::GRAYSCALE);

	for (int i = 0; i < model->nfaces(); i++)
	{
		std::vector<int> face = model->face(i);

		auto [ax, ay, az] = projectTriangleToScreen(model->vert(face[0]), g_width, g_height);
		auto [bx, by, bz] = projectTriangleToScreen(model->vert(face[1]), g_width, g_height);
		auto [cx, cy, cz] = projectTriangleToScreen(model->vert(face[2]), g_width, g_height);

		triangle(ax,ay,az,bx,by,bz,cx,cy,cz, 
			zbuffer,
			framebuffer, 
			genRandColor());
	}
	framebuffer.flip_vertically(); // set origin to bottom left
	framebuffer.write_tga_file("output//output.tga");
	zbuffer.flip_vertically();
	zbuffer.write_tga_file("output//zbuffer.tga");
	return 0;
}