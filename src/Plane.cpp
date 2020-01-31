#include "Plane.h"
#include "Ray.h"

bool Plane::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  

  // ray is parallel to plane 
  if (ray.direction.dot(normal) == 0)
  {
    return false;
  }

  double temp = (point - ray.origin).dot(normal)/(ray.direction.dot(normal));
  if (temp >= min_t)
  {
    t = temp;
  	n = normal;
  	return true;
  }
  return false;

  ////////////////////////////////////////////////////////////////////////////
}

