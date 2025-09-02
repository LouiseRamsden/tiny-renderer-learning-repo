#include "tgaimage.h"
#include "gfxlib.h"
#include "model.h"

constexpr int g_width = 128;
constexpr int g_height = 128;
Model* model = nullptr;

int main(int argc, char** argv) 
{

//	model = new Model("assets//diablo3_pose.obj");
	
	TGAImage framebuffer(g_width, g_height, TGAImage::RGB);

	triangle(7, 45, 35, 100, 45, 60, framebuffer, red);
	triangle(120, 35, 90, 5, 45, 110, framebuffer, white);
	triangle(115, 83, 80, 90, 85, 120, framebuffer, green);

	framebuffer.flip_vertically(); // set origin to bottom left
	framebuffer.write_tga_file("output//output.tga");
	return 0;
}