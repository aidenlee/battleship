struct ship {
  int x;
  int y;
  boolean health[3];
};

struct player {
  ship ship;
};

boolean attack (x, y) {
  for (int i = 0, i < 3, i ++) {
    if (ship.x+i == x && ship.y == y) {}
      ship.health[i] = false;
      lcd.clear();
      lcd.print("HIT");
      return true;
    }
  }
  lcd.print("MISS");
  return false;
}

