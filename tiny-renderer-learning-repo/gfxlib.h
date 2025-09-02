#pragma once
#include "tgaimage.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);
const TGAColor blue = TGAColor(0, 0, 255, 255);
const TGAColor green = TGAColor(0, 255, 0, 255);
const TGAColor cyan = TGAColor(0, 255, 255, 255);
const TGAColor yellow = TGAColor(255, 255, 0, 255);
const TGAColor magenta = TGAColor(255, 0, 255, 255);

//draw line from point a to point b on framebuffer of color
void line(int ax, int ay, int bx, int by, TGAImage& framebuffer, TGAColor const& color);
void triangle(int ax, int ay, int bx, int by, int cx, int xy, TGAImage& framebuffer, TGAColor const& color);