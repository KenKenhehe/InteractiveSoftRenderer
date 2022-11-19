#include "triangle.h"

Vec3f barycentric(Vec3f A, Vec3f B, Vec3f C, Vec3f P) 
{
    Vec3f s[2];
    for (int i=2; i--; ) {
        s[i][0] = C[i]-A[i];
        s[i][1] = B[i]-A[i];
        s[i][2] = A[i]-P[i];
    }
    Vec3f u = cross(s[0], s[1]);
    if (std::abs(u[2])>1e-2) // dont forget that u[2] is integer. If it is zero then triangle ABC is degenerate
        return Vec3f(1.f-(u.x+u.y)/u.z, u.y/u.z, u.x/u.z);
    return Vec3f(-1,1,1); // in this case generate negative coordinates, it will be thrown away by the rasterizator
}

void triangle(Vec3f* pts, float* zbuffer, TGAImage &image, TGAColor color)
{
    Vec2f bboxmin(image.get_width() - 1, image.get_height() -1);
    Vec2f bboxmax(0, 0);
    Vec2f clamp(image.get_width() - 1, image.get_height() -1);

    for (int i=0; i<3; i++) {
        for (int j=0; j<2; j++) {
            bboxmin[j] = std::max(0.f,      std::min(bboxmin[j], pts[i][j]));
            bboxmax[j] = std::min(clamp[j], std::max(bboxmax[j], pts[i][j]));
        }
    }

    Vec3f P;
    for(P.x = bboxmin.x; P.x <= bboxmax.x; P.x++){
        for(P.y = bboxmin.y; P.y<=bboxmax.y; P.y++){
            Vec3f bc_screen = barycentric(pts[0], pts[1], pts[2], P);
            if(bc_screen.x < 0 || bc_screen.y < 0 || bc_screen.z < 0) continue;
            P.z = 0;
            for(int i = 0; i < 3; i++) P.z += pts[i][2] * bc_screen[i];
            if(zbuffer[int(P.x + P.y * image.get_width())] < P.z){
                zbuffer[int(P.x + P.y * image.get_width())] = P.z;
                image.set(P.x, P.y, color);
            }
        }
    }
}