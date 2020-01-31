#include "Sphere.h"
#include "Ray.h"
#include <cmath>
#include <iostream>


bool Sphere::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  
  Eigen::Vector3d d = ray.direction;
  Eigen::Vector3d o = ray.origin-center;

  double a = d.dot(d);
  double b = (d).dot(o);
  double c = (o).dot(o) - pow(radius, 2.0);

  double discriminant = pow(b, 2.0) - a*c;

  if (discriminant > 0.0) 
  {
    double t1 = ((-d).dot(o) + sqrt(discriminant)) / d.dot(d);
    double t2 = ((-d).dot(o) - sqrt(discriminant)) / d.dot(d);
    if (std::max(t1, t2) >min_t && std::min(t1, t2) < min_t) 
    {
      t = std::max(t1, t2);
    }
    else if (std::min(t1, t2) > min_t) 
    {
      t = std::min(t1, t2);
    }
    else 
    {
      return false;
    }
    n = (ray.origin + t*d - center) / radius;
    return true;
  }
  else if (discriminant == 0.0) 
  {
    t = (-d).dot(o) / d.dot(d);
    
    if (t <= min_t) 
      {
        return false;
      }
    n = (ray.origin + t*d - center) / radius;
    return true;
  }
  else 
  {
    return false;
  }
  ////////////////////////////////////////////////////////////////////////////
}

