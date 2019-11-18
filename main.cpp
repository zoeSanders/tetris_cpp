#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <ncurses.h>
#include <time.h>
#include <unistd.h>
#include "tetromino.h"
#include <string.h>


#define MOVE_CLOCK_INITIAL 100000
using namespace std;
void menu();
void display_instructions()
{
  clear();
  char input = ' ';
  while(input != 27)
    {
      refresh();
      mvprintw(22, 0, "Press escape to return to menu");
      mvprintw( 0, 20, "TETRIS INSTRUCTIONS" );
      mvprintw( 2, 1, "Hi, welcome to my (Zoe Sanders) version of Tetris. \nDue to time constraint and laziness I did not implement music.\nIf you want to play this game without just the sound of \nyour own breathing,or whatever music you listen to while grading, \nI recommend youtubing the tetris theme song for a full immersive experience.");
      mvprintw( 8, 0, "-----------------------------------------------------------------");
      mvprintw( 10, 1, "Rotate Tetromino (Counter-clockwise) .....  [ s-key ]");
      mvprintw( 12, 1, "Move tetromino to the left ...............  [ a-key ]");
      mvprintw( 14, 1, "Move tetromino to the right ..............  [ d-key ]");
      mvprintw( 16, 1, "Speed tetromino fall .....................  [ w-key ]");
      mvprintw( 18, 1, "Quit game ................................  [ q-key ]");
      mvprintw( 20, 0, "-----------------------------------------------------------------");
      input = getch();


    }
  menu();
  return;
  
  
}
/* Handles ncurses initializations */
void menu()
{    
  initscr();
  curs_set(0);           // set the cursor to invisible
   noecho();  
  clear();
  int cursor = 0;
  string tetris[] = {"######## ######## ######## ########  ####  ######",  
		     "   ##    ##          ##    ##     ##  ##  ##    ##", 
		     "   ##    ##          ##    ##     ##  ##  ##" ,      
		     "   ##    ######      ##    ########   ##   ######",  
		     "   ##    ##          ##    ##   ##    ##        ##", 
		     "   ##    ##          ##    ##    ##   ##  ##    ##", 
		      "   ##    ########    ##    ##     ## ####  ######"};
  int tetris_x = 20;
  int tetris_y = 5;
  int cursor_x;
  char input = ' ';
  string options[] = { "Start", "Instructions"};
  int i;
  while(1)
    {
      mvprintw(0, 1, "Press a to move cursor to left, d to move cursor to the right and w to select.");
      for( i = 0; i < 7; i++)
	{
	  const char *c_tetris = tetris[i].c_str();
	  mvprintw(tetris_y, tetris_x, c_tetris);
	  tetris_y++;
	}
      mvprintw(tetris_y + 5, tetris_x + 5, options[0].c_str());
      mvprintw(tetris_y +5, tetris_x + 30, options[1].c_str());
      cursor_x = tetris_x + 11;
      
      if(cursor == 1)
	{
	  cursor_x += 33;
	}
      mvaddch(tetris_y + 5, cursor_x, '*');
      input = getch();
      if(input== 'd' && cursor < 1)
	{
	  cursor++;
	}
      if(input == 'a' && cursor > 0 )
	{
	  cursor--;
	}
      if(input == 'w')
	{
	  if(cursor == 0) { clear();  break; }
	  if(cursor == 1) { display_instructions(); clear(); break; }
	}
      tetris_y = 5;
      clear();
      refresh();
    }
  
  
}
void ncurses_init()
{
  cbreak();              // pass key presses to program, but not signals
  noecho();              // don't echo key presses to screen
  keypad(stdscr, TRUE);  // allow arrow keys
  timeout(0);            // no blocking on getch()
  start_color();
  init_pair(COLOR_RED, COLOR_WHITE, COLOR_RED);
  init_pair(COLOR_GREEN, COLOR_WHITE, COLOR_GREEN);
  init_pair(COLOR_YELLOW, COLOR_WHITE, COLOR_YELLOW);
  init_pair(COLOR_BLUE, COLOR_WHITE, COLOR_BLUE);
  init_pair(COLOR_MAGENTA, COLOR_WHITE, COLOR_MAGENTA);
  init_pair(COLOR_CYAN, COLOR_WHITE, COLOR_CYAN);
  init_pair(COLOR_WHITE, COLOR_WHITE, COLOR_WHITE);
  init_pair(COLOR_BLACK, COLOR_WHITE, COLOR_BLACK);
  init_pair(8, COLOR_WHITE, COLOR_WHITE);
}
int main(int argc, char *argv[])
{
  menu();
  //Game grid.
  grid grid;

  srand(time(0));
  
  //Used to determine when to speed up game.
  clock_t game_start, game_current;

  game_start = clock();
  game_current = clock();

  ncurses_init();
  
  //Clocks for determining when to move block down.
  clock_t t0, t1;

  int move_time = MOVE_CLOCK_INITIAL;
  int move_time_hold = move_time;

  t0 = clock();
  t1 = clock();
  init_grid(&grid);
  //Create new tetromino
  tetromino *t = new tetromino(rand()%7);
  t->init_tetromino();
  t->init_color();
  //current command
  char c;
  //last command
  char last_c;

  bool over = false;
  bool lost = false;

  while(!over)
    {
      // New current game time.
      game_current = clock();
      if(game_start - game_current >= 120)
	{
	  move_time -= move_time/3;
	  move_time_hold = move_time;
	  game_start = game_current;
	}
      mvprintw(5, WIDTH + 10, "Current Score:");
      mvprintw(6, WIDTH + 15, "%d", grid.score);
      t1 = clock();
      if(t->placed && t1 - t0 > move_time)
      	{
      	  t = new tetromino(rand()%7);
      	    t->init_tetromino();
	    move_time = move_time_hold;
	    refresh();
	    last_c = ' ';
	    t0 = clock();
      	}
      render_grid(&grid);
      t->render_tetromino();
      t->render_shadow(&grid);
      if(t1 - t0 > move_time)
	{
	  t->move_down(&grid);
	  t0 = clock();
	}
      c = getch();
      if(c == 's' && !t->placed)
	{
	  t->rotate(&grid);
	  last_c = c;
	}
      if(c == 'd')
	{
	  t->move(&grid, 1);
	  last_c = c;
	}
      if(c == 'a')
	{
	  t->move(&grid, -1);
	  last_c = c;
	}
      if(c == 'q')
	{
	  over = true;
	  last_c = c;
	}
      if(c == 'w' && last_c != 'w')
	{
	  move_time_hold = move_time;
	  move_time = 1000;
	  last_c = c;
	}
      if(grid.game_ended())
	{
	  over = true;
	  lost = true;
	}
      t1 = clock();
      grid.clear_straights();
      refresh();
    }
  if(lost)
    {
      //TODO, add more details.
      clear();
      mvprintw(WIDTH/2, HEIGHT/2, "YOU LOST\n");
      refresh();
      usleep(3000000);
    }
  t->delete_tetromino(t);
  clear();
  refresh();
  endwin();

}
