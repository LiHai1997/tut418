#include "blinn_phong_shading.h"
// Hint:
#include "first_hit.h"
#include <iostream>

Eigen::Vector3d mat_mult(
    const Eigen::Vector3d & a,
    const Eigen::Vector3d & b){
  return (a.array() * b.array()).matrix();
}
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
  // int light_hit_id;
  // double max_light_t, light_t;
  // double epslion = 1e-7;
    
  // Eigen::Vector3d light_n;
  // Eigen::Vector3d rgb = Eigen::Vector3d(0,0,0);
  // Eigen::Vector3d ia = Eigen::Vector3d(0.1,0.1,0.1);

  // Eigen::Vector3d ka, kd, ks;
  // double phong_exp;

  // Ray light_ray;
  // light_ray.origin = ray.origin + t * ray.direction;
  // for (int i = 0; i < lights.size(); ++i)
  // {
  //   lights[i]->direction(light_ray.origin, light_ray.direction, max_light_t);
  //   bool hit = first_hit(light_ray, epslion, objects, light_hit_id, light_t, light_n);
  //   if (!hit || light_t > max_light_t)
  //   {
  //     ka = objects[hit_id]->material->ka;
  //     kd = objects[hit_id]->material->kd;
  //     ks = objects[hit_id]->material->ks;
  //     phong_exp = objects[hit_id]->material->phong_exponent;

  //     Eigen::Vector3d I = lights[i]->I;

  //     Eigen::Vector3d h = (-ray.direction.normalized() + light_ray.direction.normalized()).normalized();
  //     double tmp1 = std::max(h.dot(n), 0.0);
  //     double tmp2 = std::max(n.dot(light_ray.direction), 0.0);
  //     rgb += ((kd.array() * I.array()).matrix() * tmp2) + ((ks.array() * I.array()).matrix() * pow(tmp1, phong_exp));
  //   }
  // }

  // ka = objects[hit_id]->material->ka;
  // rgb += (ka.array() * ia.array()).matrix();
  // return rgb;
  int light_hit_id;
  double max_light_t, light_t;
  double min_t = 1e-7, phong_exp;
  double max_spec, max_diff;
  bool ret;
  Eigen::Vector3d light_n, bp_shading(0, 0, 0), ka, IA(0.1, 0.1, 0.1), kd, ks, I, h, v;

  int num_lights = lights.size();
  Ray light_ray;
  light_ray.origin = ray.origin + t * ray.direction;
  for (int i = 0; i < num_lights; i++){
    lights[i]->direction(light_ray.origin, light_ray.direction, max_light_t);

    ret = first_hit(light_ray, min_t, objects, light_hit_id, light_t, light_n);
    // if !ret means we didn't hit an object on the way to the light source
    if (!ret || light_t > max_light_t){
      ka = objects[hit_id]->material->ka;
      kd = objects[hit_id]->material->kd;
      ks = objects[hit_id]->material->ks;
      phong_exp = objects[hit_id]->material->phong_exponent;
      I = lights[i]->I;
      // instead of mat_mult(ka, I);
      h = (-ray.direction.normalized() + light_ray.direction.normalized()).normalized();
      max_spec = std::max(h.dot(n), 0.0);
      max_diff = std::max(n.dot(light_ray.direction), 0.0);
      bp_shading += (mat_mult(kd, I) * max_diff) + \
                    (mat_mult(ks, I) * pow(max_spec, phong_exp));
    }

  }
  ka = objects[hit_id]->material->ka;
  bp_shading += mat_mult(ka, IA);
  return bp_shading;

  ////////////////////////////////////////////////////////////////////////////
}
