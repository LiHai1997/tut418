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
  double epslion = 1e-7;
    
  Eigen::Vector3d light_n;
  Eigen::Vector3d rgb = Eigen::Vector3d(0,0,0);
  Eigen::Vector3d ia = Eigen::Vector3d(0.1,0.1,0.1);

  Eigen::Vector3d ka, kd, ks;
  double phong_exp;

  rgb += (ka.array() * ia.array()).matrix();
  Ray light_ray;
  light_ray.origin = ray.origin + t * ray.direction;
  for (int i = 0; i < lights.size(); ++i)
  {
    lights[i]->direction(light_ray.origin, light_ray.direction, max_light_t);
    bool hit = first_hit(light_ray, epslion, objects, light_hit_id, light_t, light_n);
    if (!hit || light_t > max_light_t)
    {
      ka = objects[hit_id]->material->ka;
      kd = objects[hit_id]->material->kd;
      ks = objects[hit_id]->material->ks;
      phong_exp = objects[hit_id]->material->phong_exponent;

      Eigen::Vector3d I = lights[i]->I;

      Eigen::Vector3d h = (-ray.direction.normalized() + light_ray.direction.normalized()).normalized();
      double tmp1 = std::max(h.dot(n), 0.0);
      double tmp2 = std::max(n.dot(light_ray.direction), 0.0);
      rgb += ((kd.array() * I.array()).matrix() * tmp2) + ((ks.array() * I.array()).matrix() * pow(tmp1, phong_exp));
    }
  }

  ka = objects[hit_id]->material->ka;
  rgb += (ka.array() * ia.array()).matrix()
  return rgb;

  ////////////////////////////////////////////////////////////////////////////
}
