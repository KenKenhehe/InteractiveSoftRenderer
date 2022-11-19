#include "renderer.h"
#include "model.h"
#include "triangle.h"

void renderer::render_wireframe_obj(const char* file_name)
{
    Model model(file_name);
    const TGAColor white = TGAColor(255, 255, 255, 255);
    for(int i = 0; i < model.nfaces(); i++)
    {
        std::vector<int> face = model.face(i);
        for(int j = 0; j < 3; j++)
        {
            Vec3f v0 = model.vert(face[j]);
            Vec3f v1 = model.vert(face[(j + 1) % 3]);
            int x0 = (v0.x + 1.) * m_image.get_width()/2.;
            int y0 = (v0.y + 1.) * m_image.get_height()/2.;
            int x1 = (v1.x + 1.) * m_image.get_width()/2.;
            int y1 = (v1.y + 1.) * m_image.get_height()/2.;
            draw_line(x0, y0, x1, y1, m_image, white);
        }
    }

    m_image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	m_image.write_tga_file("output_test.tga");
}

void renderer::render_flat_shading(const char* file_name)
{
    Model model(file_name);
    for(int i = 0; i < model.nfaces(); i++)
    {
        std::vector<int> face = model.face(i);
        Vec2i screen_coords[3];
        for(int j = 0; j < 3; j++)
        {
            Vec3f world_coords = model.vert(face[j]);
            screen_coords[j] = Vec2i((world_coords.x+1.) * m_image.get_width() / 2., (world_coords.y+1.) * m_image.get_height() / 2.);
        }
        Vec3f pts[3];
        for (int i=0; i<3; i++) pts[i] = world_to_screen(model.vert(face[i]));
        triangle(pts, m_zbuffer, m_image, TGAColor(rand()%255, rand()%255, rand()%255, 255)); 
        //const TGAColor white = TGAColor(255, 255, 255, 255);
        //triangle(pts, m_image, white);
    }
}

void renderer::render_basic_lighting(const char* file_name)
{
    Vec3f light_dir(0, 0, -1);
    Model model(file_name);
    for(int i = 0; i < model.nfaces(); i++)
    {
        std::vector<int> face = model.face(i);
        Vec2i screen_coords[3];
        Vec3f world_coords[3];
        for(int j = 0; j < 3; j++)
        {
            Vec3f v = model.vert(face[j]);
            screen_coords[j] = Vec2i((v.x+1.) * m_image.get_width() / 2., (v.y+1.) * m_image.get_height() / 2.);
            world_coords[j] = v;
        }
        
        Vec3f n = cross((world_coords[2] - world_coords[0]), (world_coords[1] - world_coords[0]));
        n.normalize();
        float intensity = n * light_dir;

        Vec3f pts[3];
        for (int i=0; i<3; i++) pts[i] = world_to_screen(model.vert(face[i]));
        if(intensity > 0)
            triangle(pts, m_zbuffer, m_image, TGAColor(intensity * 255, intensity * 255, intensity * 255, 255)); 
        //const TGAColor white = TGAColor(255, 255, 255, 255);
        //triangle(pts, m_image, white);
    }
}

void renderer::render_test(){
    const TGAColor white = TGAColor(255, 255, 255, 255);

   // draw_line(0, 0, 300, 300, m_image, white);
    Vec2i pts[3] = {Vec2i(10,10), Vec2i(100, 30), Vec2i(190, 160)}; 
    //triangle(pts, m_image, white); 
    m_image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	m_image.write_tga_file("output_test.tga");
}

Vec3f renderer::world_to_screen(Vec3f v){
    return Vec3f(int((v.x+1.)*m_image.get_width()/2.+.5), int((v.y+1.)*m_image.get_height()/2.+.5), v.z);
}