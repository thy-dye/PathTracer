#include <iostream>
#include <fstream>

int main ()
{
    std::ofstream PathTracerPPM("PathTracerPPM.ppm");

    if(!PathTracerPPM.is_open()){
        std::cerr << "Unable to open PathTracerPPM" << '\n';
        return 1;
    }

    int nx = 300;
    int ny = 150;
    PathTracerPPM << "P3\n" << nx << ' ' << ny << '\n' << 255 << '\n';
    for (int j = ny - 1;  j >= 0; j--)
    {
        for (int i = 0; i < nx; i++) 
        {
            float r = float(i) / float(nx);
            float g = float(j) / float(ny);
            float b = 0.0f;
            int ir = int(255.99*r);
            int ig = int(255.99*g);
            int ib = int(255.99*b);
            PathTracerPPM << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }
    PathTracerPPM.close();
    return 0;
}
