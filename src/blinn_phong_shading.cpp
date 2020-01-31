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

  Eigen::Vector3d ka = objects[hit_id]->material->ka;
  Eigen::Vector3d kd = objects[hit_id]->material->kd;
  Eigen::Vector3d ks = objects[hit_id]->material->ks;
  double phong_exp = objects[hit_id]->material->phong_exponent;
  rgb += (ka.array() * ia.array()).matrix();

  Ray out_ray;
  out_ray.origin = ray.origin + t * ray.direction;
  for (int i = 0; i < lights.size(); ++i)
  {
    lights[i]->direction(out_ray.origin, out_ray.direction, max_light_t);
    bool hit = first_hit(out_ray, epslion, objects, light_hit_id, light_t, light_n);
    if (!hit || light_t > max_light_t)
    {
      
      Eigen::Vector3d I = lights[i]->I;
      Eigen::Vector3d h = (-ray.direction.normalized() + out_ray.direction.normalized()).normalized();
     
      double spec = std::max(h.dot(n), 0.0);
      double diff = std::max(n.dot(out_ray.direction), 0.0);
      rgb += ((kd.array() * I.array()).matrix() * diff) + ((ks.array() * I.array()).matrix() * pow(spec, phong_exp));
    }
  }

  return rgb;

  ////////////////////////////////////////////////////////////////////////////
}
