#include "tgaimage.h"
#include "gfxlib.h"
#include "model.h"

constexpr int g_width = 2000;
constexpr int g_height = 2000;
Model* model = nullptr;

int main(int argc, char** argv) 
{

	model = new Model("assets//diablo3_pose.obj");
	
	TGAImage framebuffer(g_width, g_height, TGAImage::RGB);
	TGAImage zbuffer(g_width, g_height, TGAImage::GRAYSCALE);

	for (int i = 0; i < model->nfaces(); i++)
	{
		std::vector<int> face = model->face(i);
		Vec3f a, b, c;
		a = model->vert(face[0]);
		b = model->vert(face[1]);
		c = model->vert(face[2]);
		triangle(
			(a.x + 1.0f) * g_width/2.0f, (a.y + 1.0f) * g_height / 2.0f, (a.z + 1) * 255 / 2.0f,
			(b.x + 1.0f) * g_width / 2.0f, (b.y + 1.0f) * g_height / 2.0f, (b.z + 1) * 255 / 2.0f, 
			(c.x + 1.0f) * g_width / 2.0f, (c.y + 1.0f) * g_height / 2.0f, (c.z + 1) * 255 / 2.0f, 
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