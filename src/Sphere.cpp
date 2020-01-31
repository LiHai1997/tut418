#include "Sphere.h"
#include "Ray.h"
#include <cmath>
#include <iostream>

bool Sphere::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  // double r = radius;
  // Eigen::Vector3d e = ray.origin;
  // Eigen::Vector3d d = ray.direction;
  // Eigen::Vector3d o = center;

  // double a = d.dot(d);
  // double b = d.dot(e-o);
  // double c = (e-o).dot(e-o) - pow(r,2);

  // double discriminant = pow(b,2) - a * c;

  // if (discriminant < 0)
  // {
  // 	return false;
  // }
  // else 
  // {
  //   Eigen::Vector3d p;
  //   double r1 = (-b + sqrt(discriminant))/a;
  //   double r2 = (-b + sqrt(discriminant))/a;
  //   if (r2 >= min_t)
  //   {
  //     t = r2;
  //     p = e + t * d;
  //     n = (p-o)/r;
  //     return true;
  //   }
  //   else
  //   {
  //     if (r1 >= min_t)
  //     {
  //       t = r1;
  //       p = e + t * d;
  //       n = (p-o)/r;
  //       return true;
  //     }
  //     else
  //     {
  //       return false;
  //     }

  //   }
  // }
  double t1, t2, radius = this->radius;
    auto e = ray.origin, d = ray.direction, o = this->center;
    auto a = d.dot(d);
    auto b = 2.0 * (e.transpose().dot(d) - o.transpose().dot(d));
    auto c = e.transpose().dot(e) - (2.0 * e.transpose().dot(o)) + o.transpose().dot(o) - pow(radius, 2.0);
    auto ret = quadratic_solution(a, b, c, t1, t2);
    if (ret && (t1 >= min_t || t2 >= min_t)){
        t = (t1 < t2 && t >= min_t) ? t1 : t2;
        auto intersection = e + t * d;
        n = (intersection - o).normalized();
        return true;
    }
    return false;

  ////////////////////////////////////////////////////////////////////////////
}

