#ifndef TRIANGLE_H
#define TRIANGLE_H
#include <vector>
#include <iostream>
#include "geometry.h"
#include "tgaimage.h"


Vec3f barycentric(Vec3f A, Vec3f B, Vec3f C, Vec3f P);
void triangle(Vec3f* pts, float* zbuffer, TGAImage &image, TGAColor color);

#endif