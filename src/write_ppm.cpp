#include "write_ppm.h"
#include <fstream>
#include <cassert>
#include <iostream>

bool write_ppm(
  const std::string & filename,
  const std::vector<unsigned char> & data,
  const int width,
  const int height,
  const int num_channels)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code from computer-graphics-raster-images
  std::ofstream file(filename);
  try {
	  
	  // return false if the file can not open
	  if (file.fail()) {
		  return false;
	  }

	  if (num_channels == 3) {
		  // P3 is RGB image in ppm file
		  file << "P3" << std::endl;
	  }
	  else {
		  // P2 is grayscale in ppm file
		  file << "P2" << std::endl;
	  }
	  file << width << " " << height << std::endl << "255" << std::endl;
	
	 
	  int index;
      for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            index = num_channels * (i * width + j);
            if (num_channels == 1)
                file << (double) data[index] << " ";
            else
                file << (double)data[index] << " " << (double)data[index + 1] << " " << (double)data[index + 2] << " ";
        }
        if (num_channels == 3) file << std::endl;
      }

	  file.close();
	  return true;
  }
  catch (int e) {
	  if (file.is_open()) {
		  file.close();
	  }
	  return false;
  }

  ////////////////////////////////////////////////////////////////////////////
}
