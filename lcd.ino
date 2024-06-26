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

String questiontwo[5][5] = {{
  "Question one", 
  "Question two",
  "Question three", 
  "Question four",
  "Question five"
},{
  "yellow", 
  "green",
  "blue", 
  "blue",
  "red"
}};

String questionthree[5][5] = {{
  "Question one", 
  "Question two",
  "Question three", 
  "Question four",
  "Question five"
},{
  "B", 
  "C",
  "C", 
  "A",
  "D"
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
int lastState = HIGH; // the previous state from the input pin
int currentState;    // the current reading from the input pin

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {13, 12, 11,10}; 
byte colPins[COLS] = {9, 8, 7, 6}; 

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
//Game 1 enter a code
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
//Game 2 click the right button
void game2() {
  //String question[2] = questiontwo[0][gameindex];
  lcd.setCursor(1,0);
  lcd.print("Game 2!");
  // read the state of the switch/button:
  currentState = digitalRead(yellowb);

  if(lastState == LOW && currentState == HIGH){
    lcd.setCursor(1,1);
    lcd.print("The state changed from LOW to HIGH");
    }
  // save the last state
  lastState = currentState;
  
   
  }

  //Game 3 an A,B,C or D question

  //Game 4 true or false with the switches

  //Game 5 The vault lock
