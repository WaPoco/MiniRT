#include "../Include/miniRT.h"

/*
Add the lighting(material, light, point, eyev, normalv) function

we need to create new types like object and material with ambient, diffuse, specular and shininess
We need to implement the Phong reflection model formular to create the 3d view.
L   position of light
N   normale of the surface
R   direction of the reflected light (use vector_ref())
V   position of viewer
I   Intensity of light
n   shininess

I = I*k_amb +I*k_diffuse L*N +I*k_specular * (R * V)^n

color_eff = color*I 
*/
double    lighting(t_tuple p_light, t_tuple point, t_tuple eyev, t_tuple normalv)
{
    double color = 250;
    double color_eff;
    double Intensity;
    double ambient = 0.1;
    double diffuse = 0.1;
    double specular = 0.1;
    double shininess = 10; 
    t_tuple *L = malloc(sizeof(t_tuple));
    t_tuple *normal = malloc(sizeof(t_tuple));
    t_tuple *R = malloc(sizeof(t_tuple));
    t_tuple *V = malloc(sizeof(t_tuple));


    vector_diff(L, p_light, point); 
    vector_norm(L, L);
    vector_norm(normal, normalv);
    vector_reflexion(R, L, normal);
    vector_norm(R, R);
    vector_diff(V, eyev, point); 
    vector_norm(V, V);
    diffuse = color * diffuse * scalar_product(*L, *N);
    specular = color * specular * pow(scalar_product(*R, *V), shininess);
    ambient = color * ambient;
    return (color);
}