#include "../Include/miniRT.h"

t_tuple *int_section(t_tuple ray, t_tuple o_ray, t_tuple c_sphere, double r_sphere)
{
    double result = 0;
    double d[2] = {0, 0};
    t_tuple  origin = {0,0,0,0};
    t_tuple *dis_origins = malloc(sizeof(t_tuple));
    t_tuple *neg_c_sphere = malloc(sizeof(t_tuple));
    t_tuple *P = malloc(sizeof(t_tuple) * 2);
    P[0].x = 0, P[0].y = 0, P[0].z = 0;
    P[1].x = 0, P[1].y = 0, P[1].z = 0;
    double result_scalar = 0;
    double sq_euclid_dis_ray = sq_euclidean_distance(ray, origin);
    double discriminant = 0;
    double tmp=0;

    vector_neg(neg_c_sphere, c_sphere);
    vector_add(dis_origins, o_ray, *neg_c_sphere);
    result_scalar = scalar_product(ray, *dis_origins);
    result = -4 * sq_euclid_dis_ray * (sq_euclidean_distance(*dis_origins, origin) - r_sphere * r_sphere);
    discriminant = 2 *result_scalar * 2 * result_scalar + result;
    if (discriminant < 0)
        return (free(dis_origins), free(neg_c_sphere), P);
    else if (discriminant >= 0)
    {
        d[0] = (-2 * result_scalar + sqrt(discriminant)) / (2 * sq_euclid_dis_ray);
        d[1] = (-2 * result_scalar - sqrt(discriminant)) / (2 * sq_euclid_dis_ray);
        tmp = d[0];
        if (d[0] >= d[1])
        {
            d[0] = d[1];
            d[1] = tmp; 
        }
        get_points(P, ray, o_ray, d);
    }
    return (free(dis_origins), free(neg_c_sphere), P);
}

void    get_points(t_tuple *P, t_tuple ray, t_tuple o_ray, double d[])
{
    t_tuple scale_vec;
    t_tuple result;
    int     i = 0;

    while (i < 2)
    {
        vector_scale(&scale_vec, ray, d[i]);
        vector_add(&result, o_ray, scale_vec);
        P[i].x = result.x;
        P[i].y = result.y;
        P[i].z = result.z;
        i++;
    }
}

