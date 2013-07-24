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
    lcd.print("< Place Ship");
    lcd.setCursor(3, 1);    
    lcd.print("< Player 1");
    initialize_player(player1);
    
    Serial.println("Player 1 has been initialized"); //Serial checks
    Serial.print("Position of ship is: ");
    Serial.print(player1.ship.posi.x);
    Serial.print(" , ");
    Serial.println(player1.ship.posi.y);
    Serial.println("");
    
    lcd.clear();

    lcd.setCursor(3, 0);    
    lcd.print("< Place Ship");
    lcd.setCursor(3, 1);    
    lcd.print("< Player 2");
    initialize_player(player2);
    
    Serial.println("Player 2 has been initialized"); //Serial checks
    Serial.print("Position of ship is: ");
    Serial.print(player2.ship.posi.x);
    Serial.print(" , ");
    Serial.println(player2.ship.posi.y);
    Serial.println("");
    
    lcd.clear();
}


void loop()
{
  lcd.setCursor(3, 0);
  lcd.print("Player 1");
  lcd.setCursor(3, 1);
  lcd.print("Aim...");
  attack(player2);
  
  lcd.setCursor(3, 0);
  lcd.print("Player 2");
  lcd.setCursor(3, 1);
  lcd.print("Aim...");
  attack(player1);
  
  delay(500);
}

void attack (player player) {
  position posi = move_cursor(1, player);
  
  Serial.println("Player has fired at:"); //Serial checks
  Serial.print(posi.x);
  Serial.print(" , ");
  Serial.println(posi.y);
  Serial.println("");
    
  //fire_animation(posi);
  for (int i = 0; i < 3; i++) {
    if (player.ship.posi.x+i == posi.x && player.ship.posi.y == posi.y) {
      player.ship.health[i] = false;  
      lcd.clear();
      lcd.setCursor(3, 0);
      lcd.print("HIT");
      if (dead(player.ship)) {  
        lcd.clear();
        lcd.print("You win!");
        delay(8000);
      };
      return;
    }
  }
  lcd.clear();
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
  position posi = move_cursor(0, player);
  player.ship.posi = posi;
  player.ship.health[0] = true;
  player.ship.health[1] = true;
  player.ship.health[2] = true;
}

position move_cursor(int screen_num, player player) {
  int button_pressed; //variable to store voltage value when a key is pressed
  int c = 16;
  int d = 6;
  int a = screen_num*13;
  int b = 1;
  position posi;
  posi.x = 0;
  posi.y = 0;

  while (true) {
    byte ship[8] = { byte(0), byte(0), byte(0), byte(0), byte(0), byte(0), byte(0), byte(0) };
    button_pressed = analogRead(0); //Read analog input pin 0 (section 2.2, figure 2.3)

    if (button_pressed < 100) { //RIGHT
    
      delay(200);
      lcd.write(" ");
      posi.x ++;

      if (c > 1)
      {
        c = c/4;
      }
      else if (a < 2+(screen_num*13))
      {
        a = a + 1;
        c = 16;
      }
      else { posi.x --; }
    }

    else if (button_pressed < 200) { //UP
    
      delay(200);
      lcd.write(" ");
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
    
      delay(200);
      lcd.write(" ");
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
    
      delay(200);
      lcd.write(" ");
      posi.x --;

      if (c < 16)
      {
        c = c*4;
      }
      else if (a > (screen_num*13))
      {
        a = a - 1;
        c = 1;
      }
      else { posi.x ++; }
    }

    else if(button_pressed < 800) { //SELECT
      return posi;
    }

    ship[d] = byte(c);

    lcd.createChar(0, ship);
    lcd.setCursor(a, b);
    lcd.write(byte(0));

    //Print other stuff here....
  }
}

