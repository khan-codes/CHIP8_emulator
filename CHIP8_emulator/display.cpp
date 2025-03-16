#include "display.h"

namespace display_constants
{
	extern int grid_width = 32;
	extern int grid_height = 16;
	extern int node_size = 5;
	extern int screen_width = grid_width * node_size;
	extern int screen_height = grid_height * node_size;
}

void initialize_grid(Node* grid)
{
	for (int x = 0; x < display_constants::grid_width; ++x)
	{
		for (int y = 0; y < display_constants::grid_height; ++y)
		{
			grid[y * display_constants::grid_width + x].x = x;
			grid[y * display_constants::grid_width + x].y = y;
		}
	}
}

int grid_projection(int x)
{
	return x * display_constants::node_size;
}

