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
