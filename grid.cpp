#include "grid.h"
#include <ncurses.h>
#include <unistd.h>

void init_grid(grid *grd)
{
  grd->score = 0;
  int i, j;

  for(i = 0; i < HEIGHT; i++)
    {
      for( j = 0; j < WIDTH; j++)
	{
	  grd->game[i][j] = 0;
	}
    }
}
void render_grid(grid *grd)
{
  int i, j;

  for( i = 0; i <= HEIGHT; i++)
    {
      for( j = 0; j <= WIDTH; j++)
	{
	  if( i == 0 || i >= HEIGHT )
	    {
	      mvaddch(i, j, '-');
	    }
	  else if( j == 0 || j == WIDTH )
	    {
	      mvaddch(i, j, '|');
	    }
	  else{
	    if(grd->game[i][j] != 0)
	      {
		
		attron(COLOR_PAIR(grd->game[i][j]));
		mvaddch(i, j, ' ');
		attroff(COLOR_PAIR(grd->game[i][j]));
	      }
	    else{ 
	      mvaddch(i, j, ' ');
	    }
	  }
	}
    }
}

int grid::game_ended()
{
  int i;
  for( i = 0; i < WIDTH; i++ )
    {
      if( game[2][i] != 0 ) { return 1; }
    }
  return 0;
}

/* returns the removed row */
int grid::remove_row(int row)
{
  int x;
  for( x = 1; x < WIDTH; x++)
    {
      game[row][x] = 0;
    }
  return row;
}
/* Checks if there is a row of blocks to clear */
int grid::is_straight(int row)
{
  int x;
  for( x = 1; x < WIDTH; x++)
    {
      if( game[row][x] == 0 ) { return 0; }
    }
  return 1;
}
void grid::clear_straights()
{
  int num_straights = 0;
  int i, j;
  for ( i = 1; i < HEIGHT; i++ )
    {
      if(is_straight(i)) { 
	remove_row(i);
	num_straights++;
      }
    }
  if(num_straights > 0 )
    {
      render_grid(this);
      refresh();
      usleep(300000);
      shift_blocks_down();
    }
  if( num_straights == 4 )
    {
      clear();
      mvprintw(8, WIDTH/2, "TETRIS!");
      score += 100;
      usleep(300000);
      refresh();
      return;
    }
  score += 10*num_straights;
}

int grid::is_empty(int row)
{
  if( row == HEIGHT) { return 0; }
  int x;
  for( x = 1; x < WIDTH; x++ )
    {
      if( game[row][x] > 0 ) { return 0; }
    }
  return 1;
}
void grid::shift_row(int row)
{
  int x;
  int temp;
  int temp_row = row;
  while(is_empty(temp_row + 1))
    {
      for( x = 1; x < WIDTH; x++ )
	{
	  temp =  game[temp_row][x];
	  game[temp_row][x] = 0;
	  game[temp_row + 1][x] = temp;
	}
      temp_row++;
    }

}
void grid::shift_blocks_down()
{
  //Index of first nonempty row to be encounter going up.
  int y;
  for( y = HEIGHT - 1; y >= 1; y--)
    {
      shift_row(y);
    }

}
