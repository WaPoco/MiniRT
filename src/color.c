#include "../Include/miniRT.h"

/*
Add the lighting(material, light, point, eyev, normalv) function

we need to create new types like object and material with ambient, diffuse, specular and shininess
We need to implement the Phong reflection model formular to create the 3d view.
L   position of light
N   normale of the surface
R   direction of the reflected light (use vector_ref())
V   position of viewer
I   Intensity if light
n   shininess

I = I*k_amb +I*k_diffuse L*N +I*k_specular * (R * V)^n

color_eff = color*I 
*/