#include "Plane.h"
#include "Ray.h"

bool Plane::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  

  // ray is parallel to plane 
  // if (ray.direction.dot(normal) == 0)
  // {
  //   return false;
  // }

  // double tmp = (point - ray.origin).dot(normal)/(ray.direction.dot(normal));
  // if (tmp >= min_t)
  // {
  //   t = tmp;
  // 	n = normal;
  // 	return true;
  // }
  // return false;
  auto e = ray.origin, d = ray.direction, p = this->point, plane_normal = this->normal;

    double numerator = (p - e).dot(plane_normal);
    double denumerator = d.dot(plane_normal);
    if (0 <= denumerator && denumerator<= 1e-6){
        if (0 <= numerator && numerator <= 1e-6){
            // ray lines in the plane
            // not sure if this is the right way to handle this or not
            t = min_t;
            n = plane_normal;
            return true;
        }else // they never intersect
            return false;
    }
    // They intersect, check if >= min_t
    t = numerator / denumerator;
    if (t >= min_t){
        n = plane_normal;
        return true;
    }
    return false;
  ////////////////////////////////////////////////////////////////////////////
}

