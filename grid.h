

#define WIDTH 32
#define HEIGHT 37

class grid
{
 public:
  int score;
  int game[HEIGHT][WIDTH];
  /* returns 1 if game is over, 0 if it isnt */
  int game_ended();
  /* removes row and returns index of that row */
  int remove_row(int row);
  /* Checks if a row is empty. */
  int is_empty(int row);
  /* Checks if row is a straight */
  int is_straight(int row);
  void clear_straights();
  /* Find first non_empty row moving upwards. */
  int find_nonempty_row(int start_row);
  /* Used to shift all blocks down until they reach a row that is nonempty */
  void shift_blocks_down();
  /* used by shift_blocks_down. Shifts row down till it hits a nonempty row. */
  void shift_row(int row);
};

void init_grid(grid *grd);
void render_grid(grid *grd);
