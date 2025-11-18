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

t_color create_color(double r, double g, double b)
{
    return (t_color){r, g, b};
}

t_color color_scale(t_color c, double s)
{
    return (t_color){c.r * s, c.g * s, c.b * s};
}

t_color color_add(t_color a, t_color b)
{
    return (t_color){a.r + b.r, a.g + b.g, a.b + b.b};
}

double clamp(double x)
{
    if (x < 0) return 0;
    if (x > 1) return 1;
    return x;
}

int color_to_trgb(t_color c)
{
    int r = (int)(clamp(c.r) * 255);
    int g = (int)(clamp(c.g) * 255);
    int b = (int)(clamp(c.b) * 255);
    return create_trgb(0, r, g, b);
}

double    lighting(t_tuple ray, t_tuple p_light, t_tuple point, t_tuple p_eye, t_tuple normalv)
{
    (void)ray;
    double Intensity = 1.0;
    double k_ambient = 0.1;
    double k_diffuse = 0.9;
    double k_specular = 0.9;
    double shininess = 20000.0;

    double scalar_p1;
    double scalar_p2;
    t_tuple *L = malloc(sizeof(t_tuple));
    t_tuple *normal = malloc(sizeof(t_tuple));
    t_tuple *R = malloc(sizeof(t_tuple));
    t_tuple *V = malloc(sizeof(t_tuple));

    t_color base_color = create_color(1.0, 0.4, 1.0);
    vector_diff(L, p_light, point); 
    vector_norm(L, *L);
    vector_norm(normal, normalv);
    t_color ambient = color_scale(base_color, k_ambient * Intensity);
    t_color diffuse = create_color(0,0,0);
    scalar_p1 = scalar_product(*L, *normal);
    if (scalar_p1 > 0)
        diffuse = color_scale(base_color, k_diffuse * Intensity * scalar_p1);
    vector_diff(V, p_eye, point); 
    vector_norm(V, *V);
    t_color specular = create_color(0,0,0);
    if (scalar_p1 > 0)
    {
        vector_scale(L, *L, -1);
        vector_reflexion(R, *L, *normal);
        vector_norm(R, *R);
        scalar_p2 = scalar_product(*R, *V);
        if (scalar_p2 > 0)
        {
            double factor = pow(scalar_p2 , shininess);
            specular = color_scale(create_color(1,1,1), k_specular * Intensity * factor);
        }
    }
    free(L);
    free(normal);
    free(R);
    free(V);
    t_color result = color_add(ambient, color_add(diffuse, specular));
    return (color_to_trgb(result));
}