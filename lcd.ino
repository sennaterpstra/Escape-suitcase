#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <Servo.h>
Servo servo;

int angle = 150;
boolean turned = false;

LiquidCrystal_I2C lcd(0x27, 20, 4); // I2C address 0x27, 16 column and 2 rows

String questionone[5][5] = {{
  "Wat is het kenteken van Donald Duck?"
},{
  "313"
}};

String questiontwo[5][5] = {{
  "Welke kleur heeft de foodtruck?"
},{
  "yellow"
}};

String questionthree[5][5] = {{
  "Een algoritme is een soort stappenplan"
},{
  "true"
}};

String questionfour[5][5] = {{
  "Computers hebben besef van goed en kwaad."
},{
  "false"
}};

String questionfive[5][5] = {{
  "De auto van Katrien wordt omgebouwd tot zelfrijdende auto."
},{
  "false"
}};

String questionsix[5][5] = {{
  "De dader van de datadiefstal is verdachte 3."
},{
  "true"
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

void n1 () {dot();dash();dash();dash();dash();shortspace();}//number 1 in morse code
void n2 () {dot();dot();dash();dash();dash();shortspace();}
void n3 () {dot();dot();dot();dash();dash();shortspace();}
void n4 () {dot();dot();dot();dot();dash();shortspace();}
void n5 () {dot();dot();dot();dot();dot();shortspace();}
void n6 () {dash();dot();dot();dot();dot();shortspace();}
void n7 () {dash();dash();dot();dot();dot();shortspace();}
void n8 () {dash();dash();dash();dot();dot();shortspace();}
void n9 () {dash();dash();dash();dash();dot();shortspace();}
void n0 () {dash();dash();dash();dash();dash();shortspace();}
void shortspace () {delay(600);}//space between letters
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
//Potentiometer
 int CLK = 9;  // Pin 9 to clk on encoder
 int DT = 8;  // Pin 8 to DT on encoder
 int RotPosition = 0; 
 int rotation;  
 int value;
  boolean LeftRight;

void setup() {
Serial.begin (9600);
  rotation = digitalRead(CLK);  
  //Servo
  servo.attach(53);
  servo.write(angle); 
  
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
  randomSeed(analogRead(0));
  //gameindex = getRandomInt();
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
    case 4:
    game4();
    break;
    case 5:
    game5();
    break;
    case 6:
    game6();
    break;
    case 7:
    game7();
    break;
   }
}

int getRandomInt(){
  return random(1,5);
}
//Game 1 enter a code
void game1()  {
  char customKey = customKeypad.getKey();
 
  String question[2] = questionone[0][gameindex];
   lcd.setCursor(0,0);
  lcd.print(question[1]);
  
  if (customKey){
      if(code.length() != 4){
        code.concat(customKey);
        lcd.setCursor(0,3);
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
  void game3(){
    String question[2] = questionthree[0][gameindex];
    lcd.setCursor(0,0);
    lcd.print(question[1]);

    if(digitalRead(switch1) == 1){
      selectedButton = "true";
    }else if(digitalRead(switch1) == 0){
      selectedButton = "false";
    }
    lcd.setCursor(0,1);
    lcd.print(selectedButton);
    lcd.setCursor(0,3);
    lcd.print(questionthree[1][gameindex]);
    if(digitalRead(submitbtn) == LOW){
      if(questionthree[1][gameindex] == selectedButton){
        currentGame = currentGame + 1;
        }
      }
    }

    void game4(){
      selectedButton = "";
    String question[2] = questionfour[0][gameindex];
    lcd.setCursor(0,0);
    lcd.print(question[1]);

    if(digitalRead(switch1) == 1){
      selectedButton = "true";
    }else if(digitalRead(switch1) == 0){
      selectedButton = "false";
    }
    lcd.setCursor(0,1);
    lcd.print(selectedButton);
    lcd.setCursor(0,3);
    lcd.print(questionthree[1][gameindex]);
    if(digitalRead(submitbtn) == LOW){
      if(questionthree[1][gameindex] == selectedButton){
        currentGame = currentGame + 1;
        }
      }
    }

    void game5(){
      selectedButton = "";
    String question[2] = questionfive[0][gameindex];
    lcd.setCursor(0,0);
    lcd.print(question[1]);

    if(digitalRead(switch1) == 1){
      selectedButton = "true";
    }else if(digitalRead(switch1) == 0){
      selectedButton = "false";
    }
    lcd.setCursor(0,1);
    lcd.print(selectedButton);
    lcd.setCursor(0,3);
    lcd.print(questionthree[1][gameindex]);
    if(digitalRead(submitbtn) == LOW){
      if(questionthree[1][gameindex] == selectedButton){
        currentGame = currentGame + 1;
        }
      }
    }

    void game6(){
      selectedButton = "";
    String question[2] = questionsix[0][gameindex];
    lcd.setCursor(0,0);
    lcd.print(question[1]);

    if(digitalRead(switch1) == 1){
      selectedButton = "true";
    }else if(digitalRead(switch1) == 0){
      selectedButton = "false";
    }
    lcd.setCursor(0,1);
    lcd.print(selectedButton);
    lcd.setCursor(0,3);
    lcd.print(questionthree[1][gameindex]);
    if(digitalRead(submitbtn) == LOW){
      if(questionthree[1][gameindex] == selectedButton){
        currentGame = currentGame + 1;
        }
      }
    }
  //Game 3 an A,B,C or D question
  void game7(){
    lcd.setCursor(0,0);
    lcd.print("Klik op de zwarte knop");
    lcd.setCursor(0,1);
    lcd.print("om de kluiscode af te spelen");
    if(digitalRead(submitbtn) == LOW){
     // n5();
     // wordPause();
      //n8();
     }
//       if (customKey){
//      if(code.length() != 4){
//        code.concat(customKey);
//        lcd.setCursor(0,2);
//        lcd.print(code);
//       }
//    }
//    if(customKey == '#'){
//        if(code == questionone[1][gameindex]){
//        currentGame = currentGame + 1;
//        lcd.clear();
//        }else{
//          lcd.print("    ");
//          code = "";
//        }
//      }
}
  //Game 4 true or false with the switches
    void game8(){
      lcd.clear();
      lcd.setCursor(0,1);
      lcd.print("Game finished!");
       if(digitalRead(submitbtn) == LOW && turned == false){

 
      // scan from 0 to 180 degrees
      for(angle = 10; angle > 0; angle++)  
      {                                  
        servo.write(0);               
        delay(15);                   
      } 
      turned = true;
   }
    }
  //Game 5 The vault lock
