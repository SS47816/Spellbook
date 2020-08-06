#include "Wall.hpp"

Wall::Wall()
{
    length_ = 5;             // tube itself
    height_ = 3;             // from ground
    mesh_size_ = 0.1; 
    n_x_ = length_/mesh_size_;
    n_y_ = height_/mesh_size_;
    z_ = 2.0;
    
    for (int i = 0; i < n_x_; ++i)
    {
        distribution_.push_back(std::vector<double>(n_y_, 0.0));
    }
}

Wall::~Wall() {}

void Wall::recieveDose(const UVTube *tube, const double dt)
{
    for (auto tube_y : tube->y_)    // every section of the UV tube
    {
        for (int i = 0; i < n_x_; ++i)  // every mesh on the horizontal axis
        {
            for (int j = 0; j < n_y_; ++j) // every mesh on the vertical axis
            {
                std::cout << "Tube: " << tube_y << " i: " << i << " j: " << j << std::endl;
                const double dist = calcDist(tube->x_, tube_y, i, j, z_);
                const double I = tube->intensity_/(dist*dist);
                distribution_[i][j] += I*dt;
            }
        }
    }
}

double Wall::calcDist(const double tube_x, const double tube_y, const int i, const int j, const double z)
{
    const double x = i*mesh_size_ - tube_x;
    const double y = j*mesh_size_ - tube_y;
    
    return std::sqrt(x*x + y*y + z*z);
}