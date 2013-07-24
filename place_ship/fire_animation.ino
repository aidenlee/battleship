
void fire_animation(position posi) {

  lcd.clear();
  
  byte ship_drawing0[8] = {
    B00000,
    B00000,
    B00000,
    B00000,
    B00110,
    B11111,
    B11111,
    B01111,
  };

  byte ship_drawing1[8] = {
    B00000,
    B00100,
    B00100,
    B00110,
    B01111,
    B11111,
    B11111,
    B11111,
  };

  byte ship_drawing2[8] = {
    B00000,
    B00000,
    B00000,
    B00001,
    B00111,
    B11111,
    B11111,
    B11111,
  };

  byte ship_drawing3[8] = {
    B00011,
    B00110,
    B11100,
    B11000,
    B11100,
    B11111,
    B11111,
    B11110,
  };

  byte ship_drawing4[8] = {
    B00001,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
  };
  
  lcd.createChar(0, ship_drawing0); 
  lcd.createChar(1, ship_drawing1);
  lcd.createChar(2, ship_drawing2);
  lcd.createChar(3, ship_drawing3);
  lcd.createChar(4, ship_drawing4);
  lcd.begin(16, 2);
  
  lcd.setCursor(0,0);
  lcd.print("FIRE");
  
  lcd.setCursor(0,1);
  lcd.write(byte(0));
  lcd.write(byte(1));
  lcd.write(byte(2));
  lcd.write(byte(3));
  lcd.write(byte(4));
  
  byte shot[8];
  lcd.setCursor(4,0);  
  int k = 7;
  int count = 14;
  
  for (int i = 4; i < 10; i++)
  {
    for (int j = 16; j > 0; j = j / 4)
    {
      byte shot[8] = { byte(0), byte(0), byte(0), byte(0), byte(0), byte(0), byte(0), byte(0) };
      lcd.createChar(5, shot);
      lcd.write(byte(5));
      
      shot[k] = byte(j);
      
      lcd.createChar(5, shot);
      lcd.setCursor(i, 0);
      lcd.write(byte(5));
      
      count--;
      if (count % 2 == 0)
      { k = count / 2; }
      
      delay(500);
    }
  }
  
  k = 1;
  int l = 0;
  count = 0;
  
  for (int i = 9; i < 12 + (posi.x / 3); i++)
  {
    for (int j = 16; j > 0; j = j / 4)
    {
      byte shot[8] = { byte(0), byte(0), byte(0), byte(0), byte(0), byte(0), byte(0), byte(0) };
      lcd.createChar(5, shot);
      lcd.write(byte(5));
      
      shot[k] = byte(j);
      
      lcd.createChar(5, shot);
      lcd.setCursor(i, l);
      lcd.write(byte(5));
      
      count++;
      if (count > (6 + posi.x + posi.y))
      { k = k + 2; }
      
      if (k > 7)
      {
        l = 1;
        k = 0;
      }
      
      if (15 - (9*l) - (k/2) == posi.y)
      {
        break;
      }
      
      delay(500);
    }
  }
  
  //write character where the shot was made
  

}

