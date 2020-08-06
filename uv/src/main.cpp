#include <memory>

#include "Wall.hpp"
#include "UVTube.hpp"

int main()
{
    std::cout << "Step 0" << std::endl;
    std::unique_ptr<Wall> wall = std::make_unique<Wall>();
    std::cout << "Step 1" << std::endl;
    std::unique_ptr<UVTube> tube = std::make_unique<UVTube>();

    
    const double t_max = 5.0;
    const double dt = 0.1;

    const size_t t_steps = t_max/dt;

    std::cout << "Step 1" << std::endl;
    for (size_t t = 0; t < t_steps; t++)
    {
        wall->recieveDose(tube.get(), dt);
        tube->move(dt);
    }

    std::cout << "Step 1" << std::endl;
    
    return 0;
}