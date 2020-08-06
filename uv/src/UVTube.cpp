#include "UVTube.hpp"

UVTube::UVTube()
{
    length_ = 1.0;   // tube itself
    height_ = 0.65;  // from ground
    sections_ = 10;     // num if meshes
    intensity_ = 610*3/1000;

    speed_ = 0.05;   // m/s
    x_ = 0;          // horizontal position

    for (int i = 0; i < sections_; ++i)
    {
        y_[i] = i/this->sections_*this->length_ + this->height_;
    }
}

UVTube::~UVTube() {}

void UVTube::move(const double dt)
{
    this->x_ += this->speed_ * dt;
}