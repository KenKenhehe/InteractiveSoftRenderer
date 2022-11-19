#ifndef RENDERER_H
#define RENDERER_H

#include "tgaimage.h"
#include "line.h"
#include "geometry.h"
#include <vector>

class renderer
{
private:
    /* data */
    TGAImage& m_image;
    float* m_zbuffer;
public:
    renderer(TGAImage& image_to_render) : m_image(image_to_render){
        m_zbuffer = new float[m_image.get_width() * m_image.get_height()];
        for (int i=m_image.get_width()*m_image.get_height(); i--; m_zbuffer[i] = -std::numeric_limits<float>::max());
    }
    ~renderer(){
        delete[] m_zbuffer;
    }
public:
    void render_wireframe_obj(const char* file_name);
    void render_flat_shading(const char* file_name);
    void render_basic_lighting(const char* file_name);
    void render_test();
private:
    Vec3f world_to_screen(Vec3f v);
    
};

#endif
