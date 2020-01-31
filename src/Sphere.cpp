#include "Sphere.h"
#include "Ray.h"
#include <cmath>
#include <iostream>

bool Sphere::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  double r = radius;
  Eigen::Vector3d e = ray.origin;
  Eigen::Vector3d d = ray.direction;
  Eigen::Vector3d o = center;

  double a = d.dot(d);
  double b = d.dot(e-o);
  double c = (e-o).dot(e-o) - pow(r,2);

  double discriminant = pow(b,2) - a * c;

  if (discriminant < 0)
  {
  	return false;
  }
  else 
  {
    Eigen::Vector3d p;
    double r1 = (-b + sqrt(discriminant))/a;
    double r2 = (-b + sqrt(discriminant))/a;
    if (r2 >= min_t)
    {
      t = r2;
      p = e + t * d;
      n = (p-o)/r;
      return true;
    }
    else
    {
      if (r1 >= min_t)
      {
        t = r1;
        p = e + t * d;
        n = (p-o)/r;
        return true;
      }
      else
      {
        return false;
      }

    }
  }
  ////////////////////////////////////////////////////////////////////////////
}

