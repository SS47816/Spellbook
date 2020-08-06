#include <memory>
#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;

#include "Wall.hpp"
#include "UVTube.hpp"

int main()
{
    std::unique_ptr<Wall> wall = std::make_unique<Wall>();
    std::unique_ptr<UVTube> tube = std::make_unique<UVTube>();
    
    const double t_max = 5.0;
    const double dt = 0.1;

    const size_t t_steps = t_max/dt;

    for (size_t t = 0; t < t_steps; t++)
    {
        wall->recieveDose(tube.get(), dt);
        tube->move(dt);
    }
    
    plt::plot({1,3,2,4});
    plt::show();
    return 0;
}