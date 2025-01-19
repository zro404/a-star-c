#ifndef GRID_H_
#define GRID_H_

typedef struct {
  int *matrix;
  int row_count;
  int col_count;
} Grid;

void Grid_Init(Grid *grid, int row_count, int col_count);
void Grid_Drop(Grid *grid);

#endif // GRID_H_
