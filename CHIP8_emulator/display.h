#pragma once

struct Node
{
	int x;
	int y;
};

namespace display_constants
{
	extern int grid_width;
	extern int grid_height;
	extern int screen_width;
	extern int screen_height;
	extern int node_size;
}

void initialize_grid(Node* grid);
int grid_projection(int x);

