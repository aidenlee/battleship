// include the librard code:
#include <LiquidCrystal.h> //librard for the LCD display
#include <Arduino.h> //Arduino library
#include "battleship.h" //Arduino library

LiquidCrystal lcd(8, 9, 4, 5, 6, 7); // initialize the librard with the numbers of the interface pins see tutorial link
player player1;
player player2;
char_list main_list;

void setup()
{
    Serial.begin(9600);
    lcd.begin(16, 2); // set up the LCD's number of columns (16) and rows (2):

    lcd.setCursor(3, 0);
    lcd.print("Player 1 pick");
//    initialize_player(player1);
    lcd.clear();

    lcd.setCursor(3, 0);
    lcd.print("Player 2 pick");
//    initialize_player(player2);
    lcd.clear();
}


void loop()
{
  
  delay(500);
}

position get_cursor_position(player player) {  //Used for attacking only not for placing ships
  
  char_list char_list = set_char_list(player);
  main_list = char_list;
  display_custom_char(main_list);
  return move_cursor(char_list);
}

char_list set_char_list(player player) { //Initialises the custom characters
  
  char_list char_list;
  
  pixel ship_pixel[3];
  position ship_position = player.ship.posi;
  
  ship_pixel[0] = position_to_pixel(ship_position, 0);
  ship_position.x++;
  ship_pixel[1] = position_to_pixel(ship_position, 0);
  ship_position.x++;
  ship_pixel[2] = position_to_pixel(ship_position, 0);
  
  char_list.player_ship[0 + ship_pixel[0].a - ship_pixel[0].a].ship[ship_pixel[0].d] = byte(ship_pixel[0].c);  //Sets up the current player's ship
  char_list.player_ship[0 + ship_pixel[1].a - ship_pixel[0].a].ship[ship_pixel[1].d] = byte(ship_pixel[1].c);
  char_list.player_ship[0 + ship_pixel[2].a - ship_pixel[0].a].ship[ship_pixel[2].d] = byte(ship_pixel[2].c);
  
  char_list.ship_char[0][0] = ship_pixel[0].a;
  char_list.ship_char[0][1] = ship_pixel[0].b;
  char_list.ship_char[1][0] = ((ship_pixel[0].a + 1) % 3);
  char_list.ship_char[1][1] = ship_pixel[0].b;
  
  position position_ship = player.ship.posi;  //If the ship is hit, mark a pixel in the appropriate custom char
  for (int i; i < 3; i++) {
    if (player.ship.health[i] == false) {
      pixel pixel = position_to_pixel(position_ship, 1);
      char_list.screen[pixel.a][pixel.b].ship[pixel.d] = byte(pixel.c);
    }
    position_ship.x++;
  }
  
  return char_list;
  
}

void display_custom_char(char_list char_list) {   //Displays the custom characters to the lcd
  
  for (int col = 0; col < 3; col++) { //Displays the characters showing a Hit/Cursor
    for (int row = 0; row < 2; row++) {
      lcd.createChar(col * 3 + row, char_list.screen[col][row].ship);
      lcd.setCursor(col + 13, row);
      lcd.write(byte(col * 3 + row));
    }
  }
  
  for (int i; i < 2; i++) {  //Displays the current player's ship
    lcd.createChar(i + 6, char_list.player_ship[1].ship);
    lcd.setCursor(char_list.ship_char[i][0], char_list.ship_char[i][1]);
    lcd.write(byte(i + 6));
  }
  
  return;
}

position move_cursor(char_list char_list) {
  
  int button_pressed; //variable to store voltage value when a ked is pressed
  pixel pixel = {13, 1, 16, 6};
  position position;
  position.x = 0;
  position.y = 0;

  while (true) {
    button_pressed = analogRead(0); //Read analog input pin 0 (section 2.2, figure 2.3)
    if (button_pressed < 100) { //RIGHT

      if (pixel.c > 1)
      {
        pixel.c = pixel.c/4;
        position.x ++;
      }
      else if (pixel.a < 15)
      {
        pixel.a = pixel.a + 1;
        pixel.c = 16;
        position.x ++;
      }
    }
    else if (button_pressed < 200) { //UP

      if (pixel.d > 1)
      {
        pixel.d = pixel.d - 2;
        position.y ++;
      }
      else if (pixel.b > 0)
      {
        pixel.b = pixel.b - 1;
        pixel.d = 7;
        position.y ++;
      }
    }
    else if (button_pressed < 400) { //DOWN

      if (pixel.d < 6)
      {
        pixel.d = pixel.d + 2;
        position.y --;
      }
      else if (pixel.b < 1)
      {
        pixel.b = pixel.b + 1;
        pixel.d = 0;
        position.y --;
      }
    }
    else if (button_pressed < 600) { //LEFT
    
      if (pixel.c < 16)
      {
        pixel.c = pixel.c*4;
        position.x --;
      }
      else if (pixel.a > 13)
      {
        pixel.a = pixel.a - 1;
        pixel.c = 1;
        position.x --;
      }
    }
    else if(button_pressed < 800) { //SELECT
      return position;
    }
    
    main_list = char_list;
    
    if (!(int(char_list.screen[pixel.a - 13][pixel.b].ship[pixel.d]) / 16 == 1 && pixel.c == 16) ||         //If the cursor is in the same place a a HIT
         ((int(char_list.screen[pixel.a - 13][pixel.b].ship[pixel.d]) % 16) / 4 == 1 && pixel.c == 4) ||
         ((int(char_list.screen[pixel.a - 13][pixel.b].ship[pixel.d]) % 4) == 1 && pixel.c == 1)) {
      main_list.screen[pixel.a - 13][pixel.b].ship[pixel.d] += byte(pixel.c);
    }
    
    if (button_pressed < 800) { //Some button pressed
      delay(200);
    }
  }
}

pixel position_to_pixel(position position, int screen_num) {
  pixel pixel;
  
  pixel.a = position.x / 3 + screen_num * 13;
  pixel.c = 16 / pow(4, (position.x % 3));
  
  pixel.b = 1 - position.y / 4 ;
  pixel.d = 7 - ((position.y % 4) * 2) - pixel.b;
  
  return pixel;
}
