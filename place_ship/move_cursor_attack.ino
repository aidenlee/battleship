position move_cursor_attack(player player) {
  int button_pressed; //variable to store voltage value when a key is pressed
  int c = 16;
  int d = 6;
  int a = 0;
  int b = 1;
  position posi;
  posi.x = 0;
  posi.y = 0;
  
  custom_char grid[6] = { { byte(0), byte(4), byte(0), byte(0), byte(8), byte(0), byte(0), byte(1) }, { byte(0), byte(0), byte(3), byte(0), byte(0), byte(0), byte(1), byte(0) }, { byte(0), byte(0), byte(0), byte(0), byte(0), byte(0), byte(0), byte(0) }, { byte(0), byte(0), byte(0), byte(0), byte(0), byte(0), byte(0), byte(0) }, { byte(0), byte(0), byte(0), byte(0), byte(0), byte(0), byte(0), byte(0) } };
  
  for (int i = 0; i < 6; i ++)
  {
    lcd.createChar(i, grid[i].ship);
  }
  
  
  lcd.setCursor(13,0);
  lcd.write(byte(0));
  lcd.write(byte(1));
  lcd.write(byte(2));
  lcd.setCursor(13,1);
  lcd.write(byte(3));
  lcd.write(byte(4));
  lcd.write(byte(5));
    
  

  while (true) {
    //byte ship[8] = { byte(0), byte(0), byte(0), byte(0), byte(0), byte(0), byte(0), byte(0) };
    button_pressed = analogRead(0); //Read analog input pin 0 (section 2.2, figure 2.3)

    if (button_pressed < 800) { //button is pressed
      delay(200);    
      grid[a+(3*b)].ship[d] -=  byte(c);
      lcd.createChar(a+(3*b), grid[a+(3*b)].ship);
    }

    if (button_pressed < 100) { //RIGHT
      posi.x ++;

      if (c > 1)
      {
        c = c/4;
      }
      else if (a < 2)
      {
        a = a + 1;
        c = 16;
      }
      else { posi.x --; }
    }

    else if (button_pressed < 200) { //UP
      posi.y ++;

      if (d > 1)
      {
        d = d-2;
      }
      else if (b > 0)
      {
        b = b - 1;
        d = 7;
      }
      else { posi.y --; }
    }

    else if (button_pressed < 400) { //DOWN
      posi.y --;

      if (d < 6)
      {
        d = d + 2;
      }
      else if (b < 1)
      {
        b = b + 1;
        d = 0;
      }
      else { posi.y ++; }
    }

    else if (button_pressed < 600) { //LEFT
      posi.x --;

      if (c < 16)
      {
        c = c*4;
      }
      else if (a > 0)
      {
        a = a - 1;
        c = 1;
      }
      else { posi.x ++; }
    }

    else if(button_pressed < 800) { //SELECT
      return posi;
    }

    grid[a+(3*b)].ship[d] += byte(c);
    lcd.createChar(a+(3*b), grid[a+(3*b)].ship);

    //Print other stuff here....

 }
}