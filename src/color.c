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
return color_eff
*/
double    lighting(t_tuple ray, t_tuple p_light, t_tuple point, t_tuple p_eye, t_tuple normalv)
{
    (void)ray;
    double color = 250.0;
    double color_eff;
    double Intensity = 1;
    double ambient = 0.1;
    double diffuse = 0.9;
    double specular = 0.9;
    double shininess = 200.0; 
    double scalar_p1;
    t_tuple *L = malloc(sizeof(t_tuple));
    t_tuple *normal = malloc(sizeof(t_tuple));
    t_tuple *R = malloc(sizeof(t_tuple));
    t_tuple *V = malloc(sizeof(t_tuple));

    vector_diff(L, p_light, point); 
    vector_norm(L, *L);
    vector_norm(normal, normalv);
    ambient = Intensity * color * ambient;
    scalar_p1 = scalar_product(*L, *normal);
    diffuse = Intensity * color * diffuse * scalar_p1;
    if (scalar_p1 < 0)
    {
        diffuse = 0;
        specular = 0;
    }
    else
    {
        //vector_scale(L, *L, -1);
        vector_reflexion(R, *L, *normal);
        vector_norm(R, *R);
        //vector_scale(R, *R, -1);
        vector_diff(V, p_eye, point); 
        vector_norm(V, *V);
        //vector_scale(V, *V, -1);
        specular = Intensity * color * specular * pow(scalar_product(*R, *V), shininess);
    }
    free(L);
    free(normal);
    free(R);
    free(V);
    color_eff = ambient + diffuse + specular;
    if (color_eff > 255)
        color_eff = 255;
    return (color_eff);
}