#include "blinn_phong_shading.h"
// Hint:
#include "first_hit.h"
#include <iostream>

Eigen::Vector3d blinn_phong_shading(
  const Ray & ray,
  const int & hit_id, 
  const double & t,
  const Eigen::Vector3d & n,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector<std::shared_ptr<Light> > & lights)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  int light_hit_id;
  double max_light_t, light_t;
  double min_t = 1e-8;
  double phong_exp;
  double max_spec, max_diff;
  bool result;
  Eigen::Vector3d light_n, bp_shading(0,0,0), ka, IA(0.1,0.1,0.1),kd,ks,I,h,v;

  Ray light_ray;
  light_ray.origin = ray.origin + t * ray.direction;
  for (int i = 0; i < lights.size(); ++i)
  {
    lights[i]->direction(light_ray.origin, light_ray.direction, max_light_t);
    result = first_hit(light_ray, min_t, objects, light_hit_id, light_t, light_n);
    if (!result || light_t > max_light_t)
    {
      ka = objects[hit_id]->material->ka;
      kd = objects[hit_id]->material->kd;
      ks = objects[hit_id]->material->ks;
      phong_exp = objects[hit_id]->material->phong_exponent;
      I = lights[i]->I;

      h = (-ray.direction.normalized() + light_ray.direction.normalized()).normalized();
      max_spec = std::max(h.dot(n), 0.0);
      max_diff = std::max(n.dot(light_ray.direction), 0.0);
      bp_shading += ((kd.array() * I.array()).matrix() * max_diff) + ((ks.array() * I.array()).matrix() * pow(max_spec, phong_exp));
    }
  }

  ka = objects[hit_id]->material->ka;
  bp_shading += (ka.array() * IA.array()).matrix();
  return bp_shading;

  ////////////////////////////////////////////////////////////////////////////
}
