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
  "G2 Question one", 
  "G2 Question two",
  "G2 Question three", 
  "G2 Question four",
  "G2 Question five"
},{
  "yellow", 
  "green",
  "blue", 
  "blue",
  "orange"
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
int yellowb = 30;
int blueb = 36;
int greenb = 32;
int orangeb = 33;

int whiteb1 = 22;
int whiteb2 = 23;
int whiteb3 = 37;
int whiteb4 = 25;

int switch1 = 26;
int switch2 = 27;
int switch3 = 28;
int switch4 = 29;

int submitbtn = 5;

String selectedButton = "";
//Keypad setup
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {13, 12, 11, 10}; 
byte colPins[COLS] = {9, 8, 7, 6}; 

int currentGame = 1;

String code = "";
int gameindex = 0;
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
//Buzzer setup
int buzzer = 34;
int note = 1000; // Set the pitch for the buzzer tone

int timeUnit = 100; // This variable will be used to measure dots, dashes, breaks, and pauses
char input; // Variable to save the input to
  //Letter functions
void lA () {dot();dash();letterPause();}//letter A in morse code!
void lB () {dash();dot();dot();dot();letterPause();}//same for B
void lC () {dash();dot();dash();dot();letterPause();}
void lD () {dash();dot();dot();letterPause();}
void lE () {dot();letterPause();}
void lF () {dot();dot();dash();dot();letterPause();}
void lG () {dash();dash();dot();letterPause();}
void lH () {dot();dot();dot();dot();letterPause();}
void lI () {dot();dot();letterPause();}
void lJ () {dot();dash();dash();dash();letterPause();}
void lK () {dash();dot();dash();letterPause();}
void lL () {dot();dash();dot();dot();letterPause();}
void lM () {dash();dash();letterPause();}
void lN () {dash();dot();letterPause();}
void lO () {dash();dash();dash();letterPause();}
void lP () {dot();dash();dash();dot();letterPause();}
void lQ () {dash();dash();dot();dash();letterPause();}
void lR () {dot();dash();dot();letterPause();}
void lS () {dot();dot();dot();letterPause();}
void lT () {dash();letterPause();}
void lU () {dot();dot();dash();letterPause();}
void lV () {dot();dot();dot();dash();letterPause();}
void lW () {dot();dash();dash();letterPause();}
void lX () {dash();dot();dot();dash();letterPause();}
void lY () {dash();dot();dash();dash();letterPause();}
void lZ () {dash();dash();dot();dot();letterPause();}

void dot() //Emit sound for 100 milliseconds
{
tone(buzzer, note, timeUnit);
delay(timeUnit * 2);
}

void dash() //Emit sound for 300 milliseconds
{
tone(buzzer, note, timeUnit * 3);
delay(timeUnit * 4);
}

void letterPause() //Delay between letters for 300 milliseconds
{
delay(timeUnit * 3);
}

void wordPause()
{
delay (timeUnit * 7);
}

void setup() {

  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
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

  pinMode(switch1, INPUT_PULLUP);
  pinMode(switch2, INPUT_PULLUP);
  pinMode(switch3, INPUT_PULLUP);
  pinMode(switch4, INPUT_PULLUP);

  pinMode(submitbtn, INPUT_PULLUP);

}

void loop() {
  
  switch(currentGame) {
    case 1:
    game1();
    break;
    case 2:
    game2();
    break;
    case 3:
    game3();
    break;
   }
}

int getRandomInt(){
  return random(1,5);
}
//Game 1 enter a code
void game1()  {
  char customKey = customKeypad.getKey();
  
  lcd.setCursor(0,0);
  String question[2] = questionone[0][gameindex];
  lcd.print(question[1]);
  
  if (customKey){
      if(code.length() != 4){
        code.concat(customKey);
        lcd.setCursor(1,1);
        lcd.print(code);
       }
    }
    if(digitalRead(submitbtn) == LOW){
        if(code == questionone[1][gameindex]){
        currentGame = currentGame + 1;
        lcd.clear();
        }else{
          lcd.print("    ");
          code = "";
        }
      }
}
//Game 2 click the right button
void game2() {
  String question[2] = questiontwo[0][gameindex];
  lcd.setCursor(0,0);
  lcd.print(question[1]);

  if(digitalRead(blueb) == LOW){
    selectedButton = "blue";
  }else if(digitalRead(greenb) == LOW){
    selectedButton = "green";
  }else if(digitalRead(orangeb) == LOW){
    selectedButton = "orange";
  } else if(digitalRead(yellowb) == LOW){
    selectedButton = "yellow";
  }
  
    if(selectedButton == questiontwo[1][gameindex]){
      currentGame = currentGame + 1;
      lcd.clear();
     }
  }

  //Game 3 an A,B,C or D question
  void game3(){
    String question[2] = questionthree[0][gameindex];
    lcd.setCursor(0,0);
    lcd.print(question[1]);
    lH();
    lO();
    lI();
    wordPause();
}
  //Game 4 true or false with the switches

  //Game 5 The vault lock
