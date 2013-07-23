struct ship {
  int x;
  int y;
  boolean health[3];
};

struct position {
  int x;
  int y;
};

struct player {
  ship ship;
};


void place_ship() {
  if (select pressed) {
    player1.ship = (.x = x, .y = y, .health = [true,true,true]);
  };
}

position move_cursor() {
  int button_pressed; //variable to store voltage value when a ked is pressed
  int c = 16;
  int d = 6;
  int a = 0;
  int b = 1;
  position position;
  position.x = 0;
  position.y = 0;


  byte ship[8] = { byte(0), byte(0), byte(0), byte(0), byte(0), byte(0), byte(0), byte(0) };

  while true {
    button_pressed = analogRead(0); //Read analog input pin 0 (section 2.2, figure 2.3)
    if (button_pressed < 100) { //RIGHT

      if (c > 1)
      {
        c = c/4;
        position.x ++;
      }
      else if (a < 15)
      {

        lcd.clear();

        a = a + 1;
        c = 16;
        position.x ++;
      }

      delay(500);
    }
    else if (button_pressed < 200) { //UP

      if (d > 1)
      {
        d = d-2;
        position.y ++;
      }
      else if (b > 0)
      {

        lcd.clear();

        b = b - 1;
        d = 7;
        position.y ++;
      }

      delay(500);
    }
    else if (button_pressed < 400) { //DOWN

      if (d < 6)
      {
        d = d + 2;
        position.y --;
      }
      else if (b < 1)
      {

        lcd.clear();

        b = b + 1;
        d = 0;
        position.y --;
      }

      delay(500);
    }
    else if (button_pressed < 600) { //LEFT

      if (c < 16)
      {
        c = c*4;
        position.x --;
      }
      else if (a > 0)
      {

        lcd.clear();

        a = a - 1;
        c = 1;
        position.x --;
      }

      delay(500);
    }
    else if(button_pressed < 800) { //SELECT

      return position;
    }

    ship[d] = byte(c);

    lcd.createChar(0, ship);
    lcd.setCursor(a, b);
    lcd.write(byte(0));

    lcd.setCursor(10, 0);
    lcd.print(x);
    lcd.print(",");
    lcd.print(y);
  }
}

