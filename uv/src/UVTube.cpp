#include "UVTube.hpp"

UVTube::UVTube()
{
    double length_ = 1.0;   // tube itself
    double height_ = 0.65;  // from ground
    int sections_ = 10;     // num if meshes
    double intensity_ = 610*3/1000;

    double speed_ = 0.05;   // m/s
    double x_ = 0;          // horizontal position

    for (int i = 0; i < sections_; ++i)
    {
        y_[i] = i/sections_*length_;
    }
}

UVTube::~UVTube() {};

void UVTube::move(double dt)
{
    x_ += speed_ * dt;
}