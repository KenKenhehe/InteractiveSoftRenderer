#include "line.h"
#include "renderer.h"
#include "triangle.h"
const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);


int main(int argc, char** argv) {
	TGAImage image(1000, 1000, TGAImage::RGB);

    renderer ren(image);
    ren.render_basic_lighting("african_head.obj");
    //ren.render_test();
    image.flip_vertically(); // to place the origin in the bottom left corner of the image 
    image.write_tga_file("framebuffer.tga");
    return 0; 	
}
