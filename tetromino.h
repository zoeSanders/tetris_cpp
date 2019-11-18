#include "grid.h"

class tetromino {

 public:
  /* 7 different types */
  int type;
  /* 4 different rotations depicted by 5x5 matrices */
  int shape[4][5][5];
  /* current rotation
     0 - initial  <---
     1 - 90 degrees  |
     2 - 180         |
     3 - 270 ---------
  */
  int rotation;
  // x position for upper left corner of array.
  int pos_x;
  // y position for upper left corner of array.
  int pos_y;
  // color of tetromino
  int color;
  // Boolean for if tetromino can still be rotated.
  bool canRotate;
  // Boolean for is tetromino has been placed.
  bool placed;

  tetromino(int type)
    {
      canRotate = true;
      placed = false;
      this->type = type;
      rotation = 0;
      // Middle top of tetris container
      pos_x = WIDTH/2 + 2;
      pos_y = -2;
    }
  void delete_tetromino(tetromino *t)
    {
      delete(t);
    }
  
  void init_tetromino();
  void init_color();
  void render_tetromino();
  void render_shadow(grid *grd);
  void move_down(grid *grd);
  void rotate(grid *grd);
  void move(grid *grd, int dir);
  int collides_with_wall(int pos_x);
  int overlap(grid *grd);

};
 
