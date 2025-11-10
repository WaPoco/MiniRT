#include "../Include/miniRT.h"

double scalar_product(t_tuple a, t_tuple b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

double euclidean_distance(t_tuple a, t_tuple b)
{
    return sqrt(
        (a.x - b.x) * (a.x - b.x) +
        (a.y - b.y) * (a.y - b.y) +
        (a.z - b.z) * (a.z - b.z)
    );
}

double sq_euclidean_distance(t_tuple a, t_tuple b)
{
    return ((a.x - b.x) * (a.x - b.x) +
        (a.y - b.y) * (a.y - b.y) +
        (a.z - b.z) * (a.z - b.z));
}

// Vector addition: result = a + b
void vector_add(t_tuple *result, t_tuple a, t_tuple b)
{
    (*result).x = a.x + b.x;
    (*result).y = a.y + b.y;
    (*result).z = a.z + b.z;
}
void vector_scale(t_tuple *result, t_tuple a, double factor)
{
    (*result).x = factor * a.x;
    (*result).y = factor * a.y;
    (*result).z = factor * a.z;    
}

void vector_norm(t_tuple *result, t_tuple a)
{
    double factor;
    t_tuple origin = {0,0,0,0};

    factor = euclidean_distance(a, origin);
    (*result).x = (1.0 / factor) * a.x;
    (*result).y = (1.0 / factor) * a.y;
    (*result).z = (1.0 / factor) * a.z;    
}

void vector_diff(t_tuple *result, t_tuple a, t_tuple b)
{
    (*result).x = a.x - b.x;
    (*result).y = a.y - b.y;
    (*result).z = a.z - b.z;
}

// Vector negation: result = -a
void vector_neg(t_tuple *result, t_tuple a)
{
    (*result).x = -a.x;
    (*result).y = -a.y;
    (*result).z = -a.z;
}

void vector_reflexion(t_tuple *result, t_tuple ray, t_tuple normal)
{
    double distance_mirror_plane;
    t_tuple *scale_result = malloc(sizeof(t_tuple));

    distance_mirror_plane = 2 * scalar_product(normal, ray);
    vector_scale(scale_result, normal, distance_mirror_plane);
    vector_diff(result, ray, *scale_result);
}
