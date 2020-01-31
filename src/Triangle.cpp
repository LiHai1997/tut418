#include "Triangle.h"
#include "Ray.h"
#include "Plane.h"
#include <Eigen/Geometry>


bool Triangle::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  Eigen::Vector3d a = std::get<0>(corners);
  Eigen::Vector3d b = std::get<1>(corners);
  Eigen::Vector3d c = std::get<2>(corners);

  Eigen::Vector3d d = b-a;
  Eigen::Vector3d e = c-a;
  Eigen::Vector3d triangle_n = (d).cross(e).normalized();

  auto plane = new Plane();
  plane->point = a;
  plane->normal = triangle_n;

  if (plane->intersect(ray, min_t,t,n))
  {
  	Eigen::Vector3d point = ray.origin + t * ray.direction;
  	Eigen::Vector3d e0 = b-a;
  	Eigen::Vector3d e1 = c-b;
  	Eigen::Vector3d e2 = a-c;

  	Eigen::Vector3d x0 = point-a;
  	Eigen::Vector3d x1 = point-b;
  	Eigen::Vector3d x2 = point-c;

  	if (n.dot(e0.cross(x0)) > 0 && n.dot(e1.cross(x1)) > 0 && n.dot(e2.cross(x2)) > 0)
  	{
  		return true;
  	}
  }
  delete plane;
  return false;

  ////////////////////////////////////////////////////////////////////////////
}


