#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

LiquidCrystal_I2C lcd(0x27, 20, 4); // I2C address 0x27, 16 column and 2 rows

String questionone[5][5] = {{
  "Question one", 
  "Question two",
  "Question three", 
  "Question four",
  "Question five"
},{
  "7859", 
  "3456",
  "7687", 
  "3214",
  "8781"
}};

const byte ROWS = 4; 
const byte COLS = 4; 

// Declare the pins for the Buttons
int yellowb = 26;
int blueb = 27;
int greenb = 28;
int orangeb = 29;

int whiteb1 = 22;
int whiteb2 = 23;
int whiteb3 = 24;
int whiteb4 = 25;

int switch_pin = 10;
int state = 0, Loadstate=0;

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6}; 
byte colPins[COLS] = {5, 4, 3, 2}; 

int currentGame = 1;

String code = "";
int gameindex = 0;
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void setup() {

  lcd.init();
  lcd.backlight();
  randomSeed(analogRead(0));
  gameindex = getRandomInt();
  pinMode(yellowb, INPUT_PULLUP);
  pinMode(blueb, INPUT_PULLUP);
  pinMode(greenb, INPUT_PULLUP);
  pinMode(orangeb, INPUT_PULLUP);

  pinMode(whiteb1, INPUT_PULLUP);
  pinMode(whiteb2, INPUT_PULLUP);
  pinMode(whiteb3, INPUT_PULLUP);
  pinMode(whiteb4, INPUT_PULLUP);

  pinMode(switch_pin, INPUT);
}

void loop() {
  
  switch(currentGame) {
    case 1:
    game1();
    break;
    case 2:
    game2();
    break;
    }
}

int getRandomInt(){
  return random(1,5);
}

void game1()  {
  char customKey = customKeypad.getKey();
  
  lcd.setCursor(1,0);
  String question[2] = questionone[0][gameindex];
  lcd.print(question[1]);
  
  if (customKey){
    if(customKey == '#'){
      lcd.setCursor(1,1);
      if(code == questionone[1][gameindex]){
        currentGame = currentGame + 1;
        lcd.print("Correct!");
        lcd.clear();
        }else{
          lcd.print("    ");
          code = "";
          }
      }else if(code.length() == 4){
        } else {
          code.concat(customKey);
          lcd.setCursor(1,1);
          lcd.print(code);
          }
  }
}

void game2() {
  lcd.setCursor(1,0);
  lcd.print("Second game!");
//  int buttonValue = digitalRead(blueb);
//   if (buttonValue == LOW){
//      lcd.setCursor(1,1);
//      lcd.print("Button blue is working!");
//   } else {
//     
//   }
  if (state == 0 && digitalRead(switch_pin) == HIGH) {
    state = 1;
    Loadstate=!Loadstate;
  }
  if (state == 1 && digitalRead(switch_pin) == LOW) {   
    state = 0;
  }
   if (Loadstate==HIGH){
    lcd.setCursor(1,1);
    lcd.print("off");
   }
   else{
    //Add Code block
    lcd.setCursor(1,1);
    lcd.print("on");
   }
  }
