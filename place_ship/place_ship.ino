// include the librard code:
#include <LiquidCrystal.h> //librard for the LCD display
#include <Arduino.h> //Arduino library
#include <battleship.h> //Arduino library

LiquidCrystal lcd(8, 9, 4, 5, 6, 7); // initialize the librard with the numbers of the interface pins see tutorial link

void setup()
{
    Serial.begin(9600);
    lcd.begin(16, 2); // set up the LCD's number of columns (16) and rows (2):
    lcd.setCursor(0, 0);
}


void loop() //Detect and displad if button is pressed
{
  position position = move_cursor();
  Serial.println(position.x);
  Serial.println(position.y);
  delay(500);
}

position move_cursor() {
  lcd.clear();
  int button_pressed; //variable to store voltage value when a ked is pressed
  int c = 16;
  int d = 6;
  int a = 0;
  int b = 1;
  position position;
  position.x = 0;
  position.y = 0;

  while (true) {
    byte ship[8] = { byte(0), byte(0), byte(0), byte(0), byte(0), byte(0), byte(0), byte(0) };
    button_pressed = analogRead(0); //Read analog input pin 0 (section 2.2, figure 2.3)
    if (button_pressed < 100) { //RIGHT

      if (c > 1)
      {
        c = c/4;
        position.x ++;
      }
      else if (a < 15)
      {

         lcd.setCursor(a, b);
         lcd.write(" ");

        a = a + 1;
        c = 16;
        position.x ++;
      }

      delay(200);
    }
    else if (button_pressed < 200) { //UP

      if (d > 1)
      {
        d = d-2;
        position.y ++;
      }
      else if (b > 0)
      {

        lcd.setCursor(a, b);
        lcd.write(" ");

        b = b - 1;
        d = 7;
        position.y ++;
      }

      delay(200);
    }
    else if (button_pressed < 400) { //DOWN

      if (d < 6)
      {
        d = d + 2;
        position.y --;
      }
      else if (b < 1)
      {

        lcd.setCursor(a, b);
        lcd.write(" ");

        b = b + 1;
        d = 0;
        position.y --;
      }

      delay(200);
    }
    else if (button_pressed < 600) { //LEFT

      if (c < 16)
      {
        c = c*4;
        position.x --;
      }
      else if (a > 0)
      {

        lcd.setCursor(a, b);
        lcd.write(" ");

        a = a - 1;
        c = 1;
        position.x --;
      }

      delay(200);
    }
    else if(button_pressed < 800) { //SELECT
      return position;
    }

    ship[d] = byte(c);

    lcd.createChar(0, ship);
    lcd.setCursor(a, b);
    lcd.write(byte(0));

    lcd.setCursor(10, 0);
    lcd.print(position.x);
    lcd.print(",");
    lcd.print(position.y);
  }
}

