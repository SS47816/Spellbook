#pragma once

#include <iostream>
#include <vector>

class UVTube
{
  public: 
    UVTube()
    {
        for (int i = 0; i < sections_; ++i)
        {
            y_[i] = i/sections_*length_;
        }
    };
    ~UVTube() {};
    
    double length_ = 1.0;   // tube itself
    double height_ = 0.65;  // from ground
    int sections_ = 10;    // num if meshes

    double speed_ = 0.05;   // m/s
    double x_ = 0;          // horizontal position
    std::vector<double> y_;

    double intensity_ = 610*3/1000;
    
    void move(double dt)
    {
        x_ += speed_ * dt;
    }
};