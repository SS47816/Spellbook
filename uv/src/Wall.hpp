#pragma once

#include <iostream>
#include <vector>
#include <cmath>

#include "UVTube.hpp"

class Wall
{
  public: 
    Wall();
    ~Wall();
    
    double length_;             // tube itself
    double height_;             // from ground
    double mesh_size_; 
    int n_x_ = length_/mesh_size_;
    int n_y_ = height_/mesh_size_;
    double z_;

    std::vector<std::vector<double>> distribution_;

    void recieveDose(const UVTube *tube, const double dt);

    double calcDist(const double tube_x, const double tube_y, const int i, const int j, const double z);
};