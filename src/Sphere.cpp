#include "Sphere.h"
#include "Ray.h"
#include <cmath>
#include <iostream>

bool quadratic_solution(
        const double a,
        const double b,
        const double c,
        double & x1,
        double & x2)
{
    // if b^2 - 4ac...
    //    = 0 -> t1 = t2 = -b/2a
    //    > 0 -> t1 / t2 = (-b +/- sqrt(b^2 - 4ac)) / 2a - pick closer point
    //    < 0 -> no solution
    double determinant = pow(b, 2.0) - 4.0 * a * c;
    // in c++ we can assume number 0 <= x < 1e-6 are just zero
    if (0 <= determinant && determinant <= 1e-6){
        x1 = (-b / (2.0 * a));
        x2 = x1;
        return true;
    }
    else if (determinant < 0)
        return false;
    else{
        x1 = (-b + sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);
        x2 = (-b - sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);
        return true;
    }
}

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
  // double t1, t2, radius = this->radius;
  //   auto e = ray.origin, d = ray.direction, o = this->center;
  //   auto a = d.dot(d);
  //   auto b = 2.0 * (e.transpose().dot(d) - o.transpose().dot(d));
  //   auto c = e.transpose().dot(e) - (2.0 * e.transpose().dot(o)) + o.transpose().dot(o) - pow(radius, 2.0);
  //   auto ret = quadratic_solution(a, b, c, t1, t2);
  //   if (ret && (t1 >= min_t || t2 >= min_t)){
  //       t = (t1 < t2 && t >= min_t) ? t1 : t2;
  //       auto intersection = e + t * d;
  //       n = (intersection - o).normalized();
  //       return true;
  //   }
  //   return false;
    Eigen::Vector3d d = ray.direction;
  Eigen::Vector3d e_minus_c = ray.origin-center;

  double A = d.dot(d);
  double B = (d).dot(e_minus_c);
  double C = (e_minus_c).dot(e_minus_c) - pow(radius, 2.0);

  double discriminant = pow(B, 2.0) - A*C;

  if (discriminant == 0.0) {
    t = (-d).dot(e_minus_c) / d.dot(d);
    // check if the ray is not intersecting with something else 
    // in between ray origin and image plane (if min_t =1).
    if (t <= min_t) return false;
    // unit normal
    n = (ray.origin + t*d - center) / radius;
    return true;
  }
  else if (discriminant > 0.0) {
    double t1 = ((-d).dot(e_minus_c) + sqrt(discriminant)) / d.dot(d);
    double t2 = ((-d).dot(e_minus_c) - sqrt(discriminant)) / d.dot(d);
    if (std::min(t1, t2) < min_t && std::max(t1, t2) >min_t) {
      t = std::max(t1, t2);
    }
    else if (std::min(t1, t2) > min_t) {
      t = std::min(t1, t2);
    }
    else {
      return false;
    }
    n = (ray.origin + t*d - center) / radius;
    return true;
  }
  else {
    return false;
  }
  ////////////////////////////////////////////////////////////////////////////
}

