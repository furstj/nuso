#pragma once

#include "Grid.hpp"

enum {
  BND_LEFT   = -1,
  BND_RIGHT  = -2,
  BND_TOP    = -3,
  BND_BOTTOM = -4,
};


Grid CartesianGrid(std::size_t Nx, std::size_t Ny); 

