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
    player1 = initialize_player("Juliet");

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
    player2 = initialize_player("Aiden");

    Serial.println("Player 2 has been initialized"); //Serial checks
    Serial.print("Position of ship is: ");
    Serial.print(player2.ship.posi.x);
    Serial.print(" , ");
    Serial.println(player2.ship.posi.y);
    Serial.println("");

    lcd.clear();
    lcd.print("Press Any Key To ");
    lcd.setCursor(0,1);
    lcd.print("      Begin      ");
    int button_pressed; //variable to store voltage value when a key is pressed
    while (true) {
      button_pressed = analogRead(0); //Read analog input pin 0 (section 2.2, figure 2.3)
      if (button_pressed < 800) { //button is pressed
        delay(500);
        return;
      }
    }
    
}


void loop()
{

  delay(250);

  draw_my_ship(player1.ship.posi);
  lcd.setCursor(3, 0);
  lcd.print(player1.name);
  lcd.setCursor(3, 1);
  lcd.print("Fire in ");
  attack(player2, player1);

  delay(250);
  draw_my_ship(player2.ship.posi);
  lcd.setCursor(3, 0);
  lcd.print(player2.name);
  lcd.setCursor(3, 1);
  lcd.print("Fire in ");
  attack(player1, player2);

}

void draw_my_ship(position position) {
  pixel pixel = posi_to_pixel(position, 0);

  byte ship1[8] = { byte(0), byte(0), byte(0), byte(0), byte(0), byte(0), byte(0), byte(0) };
  byte ship2[8] = { byte(0), byte(0), byte(0), byte(0), byte(0), byte(0), byte(0), byte(0) };
  switch (pixel.c) {
  case 16 :
    ship1[pixel.d] = byte(21);
    break;
  case 4 :
    ship1[pixel.d] = byte(5);
    ship2[pixel.d] = byte(16);
    break;
  case 1 :
    ship1[pixel.d] = byte(1);
    ship2[pixel.d] = byte(20);
    break;
  default :
    Serial.println("Error");
  }

  lcd.createChar(6, ship1);
  lcd.createChar(7, ship2);
  lcd.begin(16, 2);
  lcd.setCursor(pixel.a, pixel.b);
  lcd.write(byte(6));
  lcd.write(byte(7));

}

void attack (player &player, player &attacker) {
  double time = millis();
  Serial.print("Double Time: ");
  Serial.println(time);

  position posi = move_cursor_attack(player, time);

  Serial.println("Player has fired at:"); //Serial checks
  Serial.print(posi.x);
  Serial.print(" , ");
  Serial.println(posi.y);
  Serial.println("");

  fire_animation(posi);

  lcd.clear();

  byte shot[8] = { byte(0), byte(0), byte(0), byte(0), byte(0), byte(0), byte(0), byte(0) };
  lcd.createChar(5, shot);
  pixel shot_pixel = posi_to_pixel(posi, 1);

  lcd.setCursor(shot_pixel.a, shot_pixel.b);
  lcd.write(byte(5));

  shot[shot_pixel.d] = byte(shot_pixel.c);
  lcd.createChar(5, shot);
  lcd.setCursor(0,0);

  lcd.print(attacker.name);
  lcd.print(" has");

  lcd.setCursor(0,1);


  for (int i = 0; i < 3; i++) {
    if (player.ship.posi.x+i == posi.x && player.ship.posi.y == posi.y) {
      player.ship.health[i] = false;

      lcd.print("HIT!");
      Serial.print(player.ship.health[0]);
      Serial.print(player.ship.health[1]);
      Serial.print(player.ship.health[2]);

      if (dead(player.ship)) {
        lcd.clear();
        lcd.setCursor (0,0);
        lcd.print(attacker.name);
        win_animation();
        lcd.print(" wins!!");
        delay(9000);
        lcd.clear();
        lcd.setCursor (0,0);
        lcd.print(" Press reset to ");
        lcd.setCursor (0,1);
        lcd.print("    continue    ");
        while (true)
        {}
      }

      int button_pressed; //variable to store voltage value when a key is pressed
      while (true) {
        button_pressed = analogRead(0); //Read analog input pin 0 (section 2.2, figure 2.3)
        if (button_pressed < 800) { //button is pressed
          delay(250);
          return;
        }
      }
    }
  }
  lcd.print("MISSED");


  int button_pressed; //variable to store voltage value when a key is pressed
  while (true) {
    button_pressed = analogRead(0); //Read analog input pin 0 (section 2.2, figure 2.3)
    if (button_pressed < 800) { //button is pressed
      delay(500);
      return;
    }
  }


}

boolean dead (battleship ship) {
  if (ship.health[0] == false && ship.health[1] == false && ship.health[2] == false) {
    return true;
  }
  return false;
}

player initialize_player(String name) {
  player current_player;
  position posi = move_cursor(0, current_player);
  current_player.ship.posi = posi;
  current_player.name = name;
  current_player.ship.health[0] = true;
  current_player.ship.health[1] = true;
  current_player.ship.health[2] = true;
  return current_player;
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

  custom_char grid[6] = { { byte(0), byte(0), byte(0), byte(0), byte(0), byte(0), byte(0), byte(0) }, { byte(0), byte(0), byte(0), byte(0), byte(0), byte(0), byte(0), byte(0) }, { byte(0), byte(0), byte(0), byte(0), byte(0), byte(0), byte(0), byte(0) }, { byte(0), byte(0), byte(0), byte(0), byte(0), byte(0), byte(0), byte(0) }, { byte(0), byte(0), byte(0), byte(0), byte(0), byte(0), byte(0), byte(0) } };

  for (int i = 0; i < 6; i ++)
  {
    lcd.createChar(i, grid[i].ship);
  }


  lcd.setCursor(0,0);
  lcd.write(byte(0));
  lcd.write(byte(1));
  lcd.write(byte(2));
  lcd.setCursor(0,1);
  lcd.write(byte(3));
  lcd.write(byte(4));
  lcd.write(byte(5));



  while (true) {
    //byte ship[8] = { byte(0), byte(0), byte(0), byte(0), byte(0), byte(0), byte(0), byte(0) };
    button_pressed = analogRead(0); //Read analog input pin 0 (section 2.2, figure 2.3)

    if (button_pressed < 800) { //button is pressed
      delay(200);
      grid[a+(3*b)].ship[d] = byte(0);
      grid[a+(3*b)+1].ship[d] = byte(0);
      lcd.createChar(a+(3*b), grid[a+(3*b)].ship);
      lcd.createChar(a+(3*b)+1, grid[a+(3*b)+1].ship);

    }

    if (button_pressed < 100) { //RIGHT
      posi.x ++;

      if (c > 1 && a < 2)
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
    switch (c) {
    case 16 :
      grid[a+(3*b)].ship[d] = byte(21);
      break;
    case 4 :
      grid[a+(3*b)].ship[d] = byte(5);
      grid[a+(3*b)+1].ship[d] = byte(16);
      break;
    case 1 :
      grid[a+(3*b)].ship[d] = byte(1);
      grid[a+(3*b)+1].ship[d] = byte(20);
      break;
    default :
      Serial.println("Error");
    }
    lcd.createChar(a+(3*b), grid[a+(3*b)].ship);
    lcd.createChar(a+(3*b)+1, grid[a+(3*b)+1].ship);

    //Print other stuff here....

 }
}

pixel posi_to_pixel(position posi, int screen_num) {
  pixel pixel;

  pixel.a = posi.x / 3 + screen_num * 13;
  pixel.b = 1 - posi.y / 4 ;
  pixel.c = 16 / pow(2, (posi.x % 3) * 2);
  pixel.d = 7 - ((posi.y % 4) * 2) - pixel.b;

  return pixel;
}


