#include "util.h"

int index_from_coord(int row, int col, int num_rows)
{
	return col * num_rows + row;
}

void coords_from_index(int index, int num_rows, int *row, int *col)
{
	*row = index % num_rows;
	*col = (int)(index / num_rows);
}
