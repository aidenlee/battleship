void win_animation() {

  lcd.clear();
  custom_char picture[4] = {
    {
      B00000,
      B00000,
      B00000,
      B00000,
      B00110,
      B11111,
      B11111,
      B01111,
    },
    {
      B00000,
      B00100,
      B00100,
      B00110,
      B01111,
      B11111,
      B11111,
      B11111,
    },
    {
      B00000,
      B00000,
      B00000,
      B00001,
      B00111,
      B11111,
      B11111,
      B11111,
    },
    {
      B00011,
      B00110,
      B11100,
      B11000,
      B11100,
      B11111,
      B11111,
      B11110,
    }
  };

  lcd.createChar(0, picture[0].ship);
  lcd.createChar(1, picture[1].ship);
  lcd.createChar(2, picture[2].ship);
  lcd.createChar(3, picture[3].ship);
  lcd.begin(16, 2);

  lcd.setCursor(6,1);
  lcd.write(byte(0));
  lcd.write(byte(1));
  lcd.write(byte(2));
  lcd.write(byte(3));

  for (int x = 0; x < 8; x++) {
    for (int i = 0; i < 4; i++)
    {
      for (int j = 7; j >= 0; j --)
      {
        picture[i].ship[j] = picture[i].ship[j-1];
        if (j == 0) {
          picture[i].ship[j] = byte(0);
        }
      }
    }
    lcd.createChar(0, picture[0].ship);
    lcd.createChar(1, picture[1].ship);
    lcd.createChar(2, picture[2].ship);
    lcd.createChar(3, picture[3].ship);
    delay(400);
  }
  return;
}
  //write character where the shot was made




