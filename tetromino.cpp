#include "tetromino.h"
#include <time.h>
#include <ncurses.h>

#define RED 1
#define GREEN 2
#define YELLOW 3
#define BLUE 4
#define MAGENTA 5
#define CYAN 6
#define WHITE 7
/*
  Keeps track of all the blocks and their rotations.
 */
 int rotations[7][4][5][5] = 
  {
    /* I */
    {
      /* Initial */
      {
	{ 0, 0, 0, 0, 0 },
	{ 0, 0, 1, 0, 0 },
	{ 0, 0, 1, 0, 0 },
	{ 0, 0, 1, 0, 0 },
	{ 0, 0, 1, 0, 0 }
      },

      { /* 90 degrees */
	{ 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0 },
	{ 1, 1, 1, 1, 0 },
	{ 0, 0, 0, 0, 0 }
      },

      { /* 180 degrees */
	{ 0, 0, 0, 0, 0 },
	{ 0, 0, 1, 0, 0 },
	{ 0, 0, 1, 0, 0 },
	{ 0, 0, 1, 0, 0 },
	{ 0, 0, 1, 0, 0 }
      },

      { /* 270 degrees */
	{ 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0 },
	{ 0, 1, 1, 1, 1 },
	{ 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0 }
      }
    },
    /* J */ 
    {
      { /* initial */
	{ 0, 0, 0, 0, 0 },
	{ 0, 0, 1, 0, 0 },
	{ 0, 0, 1, 0, 0 },
	{ 0, 1, 1, 0, 0 },
	{ 0, 0, 0, 0, 0 }
      },
      { /* 90 */
	{ 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0 },
	{ 0, 1, 1, 1, 0 },
	{ 0, 0, 0, 1, 0 },
	{ 0, 0, 0, 0, 0 }
      },
      { /* 180 */
	{ 0, 0, 0, 0, 0 },
	{ 0, 0, 1, 1, 0 },
	{ 0, 0, 1, 0, 0 },
	{ 0, 0, 1, 0, 0 },
	{ 0, 0, 0, 0, 0 }
      },
      { /* 270 */
	{ 0, 0, 0, 0, 0 },
	{ 0, 1, 0, 0, 0 },
	{ 0, 1, 1, 1, 0 },
	{ 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0 }
      }

    },
    /* L */
    {
      { /* initial */
	{ 0, 0, 0, 0, 0 },
	{ 0, 0, 1, 0, 0 },
	{ 0, 0, 1, 0, 0 },
	{ 0, 0, 1, 1, 0 },
	{ 0, 0, 0, 0, 0 }
      },

      { /* 90 */
	{ 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 1, 0 },
	{ 0, 1, 1, 1, 0 },
	{ 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0 }
      },
      { /* 180 */
	{ 0, 0, 0, 0, 0 },
	{ 0, 1, 1, 0, 0 },
	{ 0, 0, 1, 0, 0 },
	{ 0, 0, 1, 0, 0 },
	{ 0, 0, 0, 0, 0 }
      },
      { /* 270 */
	{ 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0 },
	{ 0, 1, 1, 1, 0 },
	{ 0, 1, 0, 0, 0 },
	{ 0, 0, 0, 0, 0 },
      }
    },
    /* O */
    {
      { /* initial */
	{ 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0 },
	{ 0, 0, 1, 1, 0 },
	{ 0, 0, 1, 1, 0 },
	{ 0, 0, 0, 0, 0 }
      },
      { /* 90  */
	{ 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0 },
	{ 0, 0, 1, 1, 0 },
	{ 0, 0, 1, 1, 0 },
	{ 0, 0, 0, 0, 0 }
      },
      { /* 180  */
	{ 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0 },
	{ 0, 0, 1, 1, 0 },
	{ 0, 0, 1, 1, 0 },
	{ 0, 0, 0, 0, 0 }
      },
      { /* 270  */
	{ 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0 },
	{ 0, 0, 1, 1, 0 },
	{ 0, 0, 1, 1, 0 },
	{ 0, 0, 0, 0, 0 }
      }
    },
    /* S */
    {
      { /* initial */
	{ 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0 },
	{ 0, 0, 1, 1, 0 },
	{ 0, 1, 1, 0, 0 },
	{ 0, 0, 0, 0, 0 }
      },
      { /* 90 */
	{ 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0 },
	{ 0, 1, 0, 0, 0 },
	{ 0, 1, 1, 0, 0 },
	{ 0, 0, 1, 0, 0 }
      },
      { /* 180 */
	{ 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0 },
	{ 0, 0, 1, 1, 0 },
	{ 0, 1, 1, 0, 0 }
      },
      /* 270 */
      {
	{ 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 1, 0 },
	{ 0, 0, 1, 1, 0 },
	{ 0, 0, 1, 0, 0 }
      }
    },
    /* T */
    {
      {
	/* initial */
	{ 0, 0, 0, 0, 0 },
	{ 0, 0, 1, 0, 0 },
	{ 0, 1, 1, 1, 0 },
	{ 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0 }
      },
      {
	/*90*/
	{ 0, 0, 0, 0, 0 },
	{ 0, 0, 1, 0, 0 },
	{ 0, 1, 1, 0, 0 },
	{ 0, 0, 1, 0, 0 },
	{ 0, 0, 0, 0, 0 }
      },
	
      { /* 180 */
	{ 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0 },
	{ 0, 1, 1, 1, 0 },
	{ 0, 0, 1, 0, 0 },
	{ 0, 0, 0, 0, 0 }
      },
      { /* 270 */
	{ 0, 0, 0, 0, 0 },
	{ 0, 0, 1, 0, 0 },
	{ 0, 0, 1, 1, 0 },
	{ 0, 0, 1, 0, 0 },
	{ 0, 0, 0, 0, 0 }
      }
    },
    /* Z */
    {
      { /* initial */
	{ 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0 },
	{ 0, 1, 1, 0, 0 },
	{ 0, 0, 1, 1, 0 },
	{ 0, 0, 0, 0, 0 } 
      },
	
      { /* 90 */
	{ 0, 0, 0, 0, 0 },
	{ 0, 0, 1, 0, 0 },
	{ 0, 1, 1, 0, 0 },
	{ 0, 1, 0, 0, 0 },
	{ 0, 0, 0, 0, 0 }
      },
	
      { /* 180 */
	{ 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0 },
	{ 0, 1, 1, 0, 0 },
	{ 0, 0, 1, 1, 0 },
	{ 0, 0, 0, 0, 0 }
      },
	
      { /* 270 */
	{ 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 1, 0 },
	{ 0, 0, 1, 1, 0 },
	{ 0, 0, 1, 0, 0 },
	{ 0, 0, 0, 0, 0 }
      }  
    }
  };
int x_offsets[7][4][2] = {
  { // I initial
    { /* left offset */ 3, /* right offset */ 3 },
    // I 90
    { 1, 2 },
    // I 180
    { 3, 3 },
    // I 270
    { 2, 1 }
  },
  { // J initial
    { 2, 3 },
    // J 90
    { 2, 2 },
    // J 180
    { 3, 2 },
    // J 270
    { 2, 2 }
  },
  {
    // L initial
    { 3, 2 },
    // L 90
    { 2, 2 },
    // L 180
    { 2, 3 },
    // L 270
    { 2, 2 }
  },
  {
    // O
    { 3, 2 },
    { 3, 2 },
    { 3, 2 },
    { 3, 2 }
  },
  {
    // S initial
    { 2, 2 },
    // S 90
    { 2, 3 },
    // S 180
    { 2, 2 },
    // S 270
    { 3, 2 }
  },
  { 
    // T initial
    { 2, 2 },
    // T 90
    { 2, 3 },
    // T 180
    { 2, 2 },
    // T 270
    { 3, 2 }
  },
  {
    // Z initial
    { 2, 2 },
    // Z 90
    { 2, 3 },
    // Z 180
    { 2, 2 },
    // Z 270
    { 3, 2 }
  }
};
   /* 7 shapes, each corresponds to y offsets for initial position */
int y_offsets[7][4][2] = {
    { // I initial
      { /* upper offset*/ 1, /*lower offset*/ 0 },
      //I 90
      { 3, 1 },
      //I 180
      { 1, 0 },
      // I 270
      { 2, 2 }
    },
    { // J initial
      { 1, 1 },
      //J 90
      { 2, 1 },
      //J 180
      { 1, 1 },
      // J 270
      { 1, 2 }
    },
    { // L initial
      { 1, 1 },
      // L 90
      { 1, 2 },
      // L 180
      { 1, 1 },
      // L 270
      { 2, 1 }
    },
    { // O
      { 2, 1 },
      { 2, 1 },
      { 2, 2 },
      { 2, 1 },
    },
    { // S initial
      { 2, 1 },
      // S 90
      { 2, 0 },
      // S 180
      { 3, 0 },
      // S 270
      { 2, 0 }
    },
    { // T initial
      { 1, 2 },
      // T 90
      { 1, 1 },
      // T 180
      { 2, 1 },
      // T 270
      { 1, 1 }
    },
    { // Z initial
      { 2, 1 },
      // Z 90
      { 1, 1 },
      // Z 180
      { 2, 1 },
      // Z 270
      { 1, 1 }
    }
  };

void tetromino::init_color()
{
  switch(type)
    {
    case 0:
      color = CYAN;
      break;
    case 1:
      color = BLUE;
      break;
    case 2:
      color = WHITE;
      break;
    case 3:
      color = YELLOW;
      break;
    case 4:
      color = GREEN;
      break;
    case 5:
      color = MAGENTA;
      break;
    case 6:
      color = RED;
      break;
    default:
      break;
    }

}
void tetromino::init_tetromino()
{
  pos_y = pos_y + y_offsets[type][rotation][0];
  int i, j, k;
  for( k = 0; k < 4; k++)
    {
      for( i = 0; i < 5; i++)
	{
	  for( j = 0; j < 5; j++)
	    {
	      shape[k][i][j] = rotations[type][k][i][j];
	    }
	}
    }
  init_color();
}

void tetromino::render_tetromino()
{
  int i, j;
  for( i = 0; i < 5; i++)
    {
      for( j = 0; j < 5; j++)
	{
	  if( shape[rotation][i][j] != 0 )
	    {
	      attron(COLOR_PAIR(color));
	      mvaddch(i + pos_y, j + pos_x, ' ');
	      attroff(COLOR_PAIR(color));
	    }
	}
    }
  

}
/*PSYCH 101
  STORY FOR TEST:
  Doctor meant Right Ear, but did Rear. <--- Example of type of Shortcut (AUTHORITY FIGURE)

  3 MORE SHORTCUTS
  - Identification Principle
  - Contrast Principle
  - Humor
 */
void place(grid *grd, tetromino *t)
{
  t->placed = true;
  t->canRotate = false;
  int i, j;
  for( i = 0; i < 5; i++)
    {
      for( j = 0; j < 5; j++)
      	{
	  if(grd->game[i + t->pos_y][j + t->pos_x] == 0 &&
	     t->shape[t->rotation][i][j] != 0 )
	    {
	      grd->game[i + t->pos_y][j + t->pos_x] =
		t->color;
	    }
	}
    }
}
void tetromino::move_down(grid *grd)
{
  pos_y++;
  if(pos_y + 5 - y_offsets[type][rotation][1] <= HEIGHT  && overlap(grd) == 0 )
    {
    }
  else
    {
      pos_y--;
      place(grd, this);
    }

}
int tetromino::overlap(grid *grd)
{
  int i, j;
  for( i = 0; i < 5; i++)
    {
      for( j = 0; j < 5; j++)
	{
	  if(shape[rotation][i][j] > 0 &&
	     grd->game[ i + pos_y][ j + pos_x] > 0) 
	    
	    { return 1; }
	}
    }
  return 0;
}
int tetromino::collides_with_wall(int x)
{
  if( x + 5 - x_offsets[type][rotation][1] >= WIDTH )
    {
      return 1;
    }
  else if( x + x_offsets[type][rotation][0] <= 1 )
    {
      return 1;
    }
  return 0;

}

void tetromino::rotate(grid *grd)
{
  if(canRotate)
    {
      rotation = (rotation + 1)%4;
    }
  if(collides_with_wall(pos_x) || overlap(grd) )
    {
      if(rotation == 0) { rotation = 3; }
      else { rotation--; }
    }

}
void tetromino::move(grid *grd, int dir)
{
  pos_x += dir;
  if(collides_with_wall(pos_x) == 0  && overlap(grd) == 0)
    {
    }
  else
    {
      pos_x-=dir;
    }

}
void tetromino::render_shadow(grid *grd)
{
  int index;
  int hold_y = pos_y;
  int hold_x = pos_x;

  for(index = pos_y; index + 5 - y_offsets[type][rotation][1] < HEIGHT; index++)
    {
      if(overlap(grd))
	{
	  pos_y--;
	  break;
	}
      pos_y++;
    }
  if(overlap(grd))
    {
      pos_y--;
    }
  if(pos_y + 1 == hold_y) { return; }
  int i, j;
  for( i = 0; i < 5; i++)
    {
      for( j = 0; j < 5; j++)
	{
	  if(shape[rotation][i][j] != 0)
	    {
	      mvaddch(i + pos_y, j + pos_x, '#');
	    }
	}
    }
  pos_y = hold_y;
  pos_x = hold_x;
}
