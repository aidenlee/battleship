// include the librard code:
#include <LiquidCrystal.h> //librard for the LCD display
#include <Arduino.h> //Arduino library
#include "battleship.h" //Arduino library

LiquidCrystal lcd(8, 9, 4, 5, 6, 7); // initialize the librard with the numbers of the interface pins see tutorial link
player player1;
player player2;
void setup()
{
    Serial.begin(9600);
    lcd.begin(16, 2); // set up the LCD's number of columns (16) and rows (2):

    lcd.setCursor(3, 0);    
    lcd.print("Player 1 pick");
    initialize_player(player1);
    lcd.clear();

    lcd.setCursor(3, 0);
    lcd.print("Player 2 pick");
    initialize_player(player2);
    lcd.clear();
}


void loop() //Detect and displad if button is pressed
{
  lcd.setCursor(3, 0);
  lcd.print("Player 1 Go");
  attack(player2);
  
  lcd.setCursor(3, 0);
  lcd.print("Player 2 Go");
  attack(player1);
  
  delay(500);
}

void attack (player player) {
  position posi = move_cursor();
  fire_animation(posi);
  for (int i = 0; i < 3; i++) {
    if (player.ship.posi.x+i == posi.x && player.ship.posi.y == posi.y) {
      player.ship.health[i] = false;
      lcd.setCursor(3, 0);
      lcd.print("HIT");
      if (dead(player.ship)) {
        lcd.print("You win!");
      };
      return;
    }
  }
  lcd.setCursor(3,0);
  lcd.print("MISS");
  return;
}

boolean dead (battleship ship) {
  if (ship.health[0] == false && ship.health[1] == false && ship.health[2] == false) {
    return true;
  }
  return false;
}

void initialize_player(player player) {
  position posi = move_cursor();
  player.ship.posi = posi;
  player.ship.health[0] = true;
  player.ship.health[1] = true;
  player.ship.health[2] = true;
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

