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

    void recieveDose(UVTube *tube, double dt);

    double calcDist(double tube_x, double tube_y, int i, int j, double z);
};