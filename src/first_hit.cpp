#include "first_hit.h"
#include <iostream>
#include <limits>

bool first_hit(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  int & hit_id, 
  double & t,
  Eigen::Vector3d & n)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  
  double t_temp = std::numeric_limits<double>::infinity();
  double distance;
  Eigen::Vector3d n_temp;
  hit_id = -1;
  for (int i = 0; i < objects.size(); ++i)
  {
    if (objects[i]->intersect(ray, min_t, distance, n_temp))
    {
      if (distance < t_temp)
      {
        t_temp = distance;
        t = distance;
        n = n_temp;
        hit_id = i;
      }
    }
  }
  return (hit_id>=0);
  ////////////////////////////////////////////////////////////////////////////
}

