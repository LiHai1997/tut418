#include "raycolor.h"
#include "first_hit.h"
#include "blinn_phong_shading.h"
#include "reflect.h"

bool raycolor(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector< std::shared_ptr<Light> > & lights,
  const int num_recursive_calls,
  Eigen::Vector3d & rgb)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  if (num_recursive_calls > 20)
  {
    return false;
  }
  int hit_id;
  double epslion = 1e-7;
  double t;
  rgb = Eigen::Vector3d(0,0,0);
  Eigen::Vector3d n, new_color;

  bool hit = first_hit(ray, min_t, objects, hit_id, t, n);
  if (hit)
  {
    rgb += blinn_phong_shading(ray, hit_id, t, n, objects, lights);
    Ray out_ray;
    out_ray.direction = reflect(ray.direction, n);
    out_ray.origin = ray.origin + t * ray.direction; 
    Eigen::Vector3d km = objects[hit_id]->material->km;
    if (raycolor(out_ray, epslion, objects, lights, num_recursive_calls + 1, new_color))
    {
      rgb += (km.array() * new_color.array()).matrix();
    }
  }
  return hit;
  
  ////////////////////////////////////////////////////////////////////////////
}
