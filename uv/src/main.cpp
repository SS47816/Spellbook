#include <memory>
#include <fstream>

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

    std::ofstream csv;
    csv.open("heatmap.csv");
    for (size_t i = 0; i < wall->distribution_.size(); i++)
    {
        std::string line;
        for (size_t j = 0; j < wall->distribution_[0].size(); j++)
        {
            line += std::to_string(wall->distribution_[i][j]);
            line += ",";
        }
        line += "\n";
        csv << line;
    }
    
    csv.close();
    std::cout << "Done!" << std::endl;

    return 0;
}