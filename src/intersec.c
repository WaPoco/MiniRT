#include "../Include/miniRT.h"

int  int_section(t_tuple ray, t_tuple o_ray, t_tuple c_sphere, double r_sphere)
{
    double result;
    t_tuple *dis_origins = malloc(sizeof(t_tuple));
    t_tuple *neg_c_sphere = malloc(sizeof(t_tuple));
    t_tuple  origin = {0,0,0,0};
    double result_scalar;

    vector_neg(neg_c_sphere, c_sphere);
    vector_add(dis_origins, o_ray, *neg_c_sphere);
    result_scalar = 2 * scalar_product(ray, *dis_origins);
    result_scalar *= result_scalar;
    result = -4 * sq_euclidean_distance(ray, origin) * (sq_euclidean_distance(*dis_origins, origin) - r_sphere * r_sphere);
    if (sqrt(result_scalar + result) <= 0)
        return (free(dis_origins), free(neg_c_sphere), 0);
    else if (sqrt(result_scalar + result) > 0)
        return (free(dis_origins), free(neg_c_sphere), 2);
    return(0);
}

t_tuple *int_point_section(t_tuple ray, t_tuple o_ray, t_tuple c_sphere, double r_sphere)
{
    double result;
    t_tuple *dis_origins = malloc(sizeof(t_tuple));
    t_tuple *neg_c_sphere = malloc(sizeof(t_tuple));
    t_tuple *P = malloc(sizeof(t_tuple));
    t_tuple  origin = {0,0,0,0};
    double result_scalar;

    vector_neg(neg_c_sphere, c_sphere);
    vector_add(dis_origins, o_ray, *neg_c_sphere);
    result_scalar = 2 * scalar_product(ray, *dis_origins);
    result_scalar *= result_scalar;
    result = -4 * sq_euclidean_distance(ray, origin) * (sq_euclidean_distance(*dis_origins, origin) - r_sphere * r_sphere);
    /*
    Add the quadaratic equation and solve for the scaling factor. Pick the smallest and calc the intersection point p
    */
}