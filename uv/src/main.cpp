#include <memory>

#include "Wall.cpp"
#include "UVTube.cpp"

void main()
{
    std::unique_ptr<Wall> wall = std::make_unique<Wall>();
    UVTube tube = UVTube();

    
}