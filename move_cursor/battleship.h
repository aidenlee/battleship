struct position {
  int x;
  int y;
};

struct battleship {
  position posi;
  boolean health[3];
};

struct player {
  battleship ship;
  
};

struct pixel {
  int a;
  int b;
  int c;
  int d;
};

struct custom_char {
  byte ship[8];
};

struct char_list {
  custom_char player_ship[2];
  int ship_char[2][2];
  custom_char screen[3][2];
};
