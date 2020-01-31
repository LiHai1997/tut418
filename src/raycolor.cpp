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
  if (num_recursive_calls > 22)
  {
    return false;
  }
  int hit_id;
  double t, min_new_t = 1e-8;
  rgb = Eigen::Vector3d(0,0,0);
  Eigen::Vector3d n, new_color;

  bool result = first_hit(ray, min_t, objects, hit_id, t, n);
  if (result)
  {
    rgb += blinn_phong_shading(ray, hit_id, t, n, objects, lights);
    Ray new_ray;
    new_ray.direction = reflect(ray.direction, n);
    if (raycolor(new_ray, min_new_t, objects, lights, num_recursive_calls + 1, new_color))
    {
      rgb += (objects[hit_id]->material->km.array() * new_color.array()).matrix();
    }
  }
  return result;
  ////////////////////////////////////////////////////////////////////////////
}
