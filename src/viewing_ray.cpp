#include "viewing_ray.h"

void viewing_ray(
  const Camera & camera,
  const int i,
  const int j,
  const int width,
  const int height,
  Ray & ray)
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  double x_cor = (j+0.5)/width;
  double y_cor = (i+0.5)/height;
  double ratio = width/height;

  x_cor = (x_cor-0.5) * ratio * camera.width;
  y_cor = -(y_cor - 0.5) * camera.height;

  ray.origin = camera.e;
  ray.direction = x_cor * camera.u + y_cor * camera.v - camera.d * camera.w;


  ////////////////////////////////////////////////////////////////////////////
}

