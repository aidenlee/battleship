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

struct custom_char {
  byte ship[8];
};

struct pixel {
  int a;
  int b;
  int c;
  int d;
};

