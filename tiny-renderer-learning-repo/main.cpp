#include "tgaimage.h"
#include "gfxlib.h"
#include "model.h"

constexpr int g_width = 64;
constexpr int g_height = 64;
Model* model = nullptr;

int main(int argc, char** argv) 
{

//	model = new Model("assets//diablo3_pose.obj");
	
	TGAImage framebuffer(g_width, g_height, TGAImage::RGB);

	triangle(10, 10, 32, 64, 50, 10, framebuffer, green);


	framebuffer.flip_vertically(); // set origin to bottom left
	framebuffer.write_tga_file("output//output.tga");
	return 0;
}