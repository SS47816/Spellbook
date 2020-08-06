#pragma once

#include <iostream>
#include <vector>
#include <cmath>

#include "UVTube.cpp"

class Wall
{
  public: 
    Wall()
    {
        for (int i = 0; i < n_x_; ++i)
        {
            distribution_.push_back(std::vector<double>(n_y_, 0.0));
        }
    };
    ~Wall() {};
    
    double length_ = 8;     // tube itself
    double height_ = 3;     // from ground
    double mesh_size_ = 0.1; 
    int n_x_ = length_/mesh_size_;
    int n_y_ = height_/mesh_size_;
    double z_ = 2.0;

    std::vector<std::vector<double>> distribution_;

    void recieveDose(UVTube &tube, double distance, double dt)
    {
        for (auto tube_y : tube.y_)
        {
            for (int i = 0; i < n_x_; ++i)
            {
                for (int j = 0; j < n_y_; ++j)
                {
                    const double dist = calcDist(tube.x_, tube_y, i, j, z_);
                    const double I = tube.intensity_/(dist*dist);
                    distribution_[i][j] += I*dt;
                }
            }
        }
    };

    double calcDist(double tube_x, double tube_y, int i, int j, double z)
    {
        const double x = i*mesh_size_ - tube_x;
        const double y = j*mesh_size_ - tube_y;
        
        return std::sqrt(x*x + y*y + z*z);
    }
};