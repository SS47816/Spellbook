#pragma once

#include <iostream>
#include <vector>

class UVTube
{
  public: 
    UVTube();
    ~UVTube();

    void move(const double dt);

    double length_;   // tube itself
    double height_;  // from ground
    int sections_;     // num if meshes
    double intensity_;

    double speed_;   // m/s
    double x_;          // horizontal position
    std::vector<double> y_;
};