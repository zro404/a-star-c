#include "grid.h"
#include "main.h"

void Grid_Init(Grid *grid, int row_count, int col_count) {
  grid->matrix = malloc(sizeof(int) * row_count * col_count);
}

void Grid_Drop(Grid *grid) { free(grid->matrix); }
