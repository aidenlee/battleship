struct ship {
  int x;
  int y;
  boolean health[3];
};

struct player {
  ship ship;
};

boolean attack (player, x, y) {
  for (int i = 0, i < 3, i ++) {
    if (player.ship.x+i == x && player.ship.y == y) {}
      player.ship.health[i] = false;
      lcd.clear();
      lcd.print("HIT");
      if (dead(player.ship)) {
        lcd.print("You win!");
      };
      return true;
    }
  }
  lcd.print("MISS");
  return false;
}

boolean dead (ship) {
  if (ship.health = [false, false, false]) {
    return true;
  }
  return false;
}

void place_ship() {
  if (select pressed) {
    player1.ship = (.x = x, .y = y, .health = [true,true,true]);
  };
}