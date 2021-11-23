// Inspiration from https://www.arduino.cc/en/Tutorial/BuiltInExamples/RowColumnScanning#code
// White = 1
// Gray = 2
// Orange = 3
// Green = 4
// Black = 5
// Yellow = 6
// Purple = 7
// Blue = 8

#define ROW1 52
#define ROW2 50
#define ROW3 48
#define ROW4 46
#define ROW5 44
#define ROW6 42
#define ROW7 40
#define ROW8 38


#define COL1 53
#define COL2 51
#define COL3 49
#define COL4 47
#define COL5 45
#define COL6 43
#define COL7 41
#define COL8 39

const int BUTTON1 = 0;
const int BUTTON2 = 2;
const int BUTTON3 = 4;
const int BUTTON4 = 6;

int BUTTONstate1 = 0;
int BUTTONstate2 = 0;
int BUTTONstate3 = 0;
int BUTTONstate4 = 0;



void setup()
{
  pinMode(ROW1, OUTPUT);
  pinMode(ROW2, OUTPUT);
  pinMode(ROW3, OUTPUT);
  pinMode(ROW4, OUTPUT);
  pinMode(ROW5, OUTPUT);
  pinMode(ROW6, OUTPUT);
  pinMode(ROW7, OUTPUT);
  pinMode(ROW8, OUTPUT);

  pinMode(COL1, OUTPUT);
  pinMode(COL2, OUTPUT);
  pinMode(COL3, OUTPUT);
  pinMode(COL4, OUTPUT);
  pinMode(COL5, OUTPUT);
  pinMode(COL6, OUTPUT);
  pinMode(COL7, OUTPUT);
  pinMode(COL8, OUTPUT);
 
}

void loop()
{
  BUTTONstate1 = digitalRead(BUTTON1);
  if (BUTTONstate1 == HIGH)
  {
    Serial.println("Button 1 ON");
    pinWheel();
  } 
  else{
    Serial.println("Button 1 OFF");
  }
  BUTTONstate2 = digitalRead(BUTTON2);
  if (BUTTONstate2 == HIGH)
  {
    Serial.println("Button 2 ON");
    pulse();
  } 
  else{
    Serial.println("Button 2 OFF");
  }

}
void pinWheel(){
  lightUpUmbrella(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
  lightUpUmbrella(1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1);
  lightUpUmbrella(1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1);
  lightUpUmbrella(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1);
  lightUpUmbrella(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1);
  lightUpUmbrella(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1);
  lightUpUmbrella(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1);
  lightUpUmbrella(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1);
  lightUpUmbrella(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0);
  lightUpUmbrella(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1);
  lightUpUmbrella(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1);
  lightUpUmbrella(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1);
  lightUpUmbrella(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1);
  lightUpUmbrella(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1);
  lightUpUmbrella(1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1);
  lightUpUmbrella(1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1);
}

void pulse(){
  lightUpUmbrella(1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
  lightUpUmbrella(1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
  lightUpUmbrella(1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
  lightUpUmbrella(1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
  lightUpUmbrella(1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
  lightUpUmbrella(1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
  lightUpUmbrella(1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
  lightUpUmbrella(1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0);
  lightUpUmbrella(1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
  lightUpUmbrella(1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
  lightUpUmbrella(1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
  lightUpUmbrella(1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
  lightUpUmbrella(1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
  lightUpUmbrella(1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}

void lightUpUmbrella(int r1, int r2, int r3, int r4, int r5, int r6, int r7, int r8, int c1, int c2, int c3, int c4, int c5, int c6, int c7, int c8){

  int delayVal = 100;

    // ROWS
  
  // Light up all rows and columns
      digitalWrite(ROW1,r1);
      digitalWrite(ROW2,r2);
      digitalWrite(ROW3,r3);
      digitalWrite(ROW4,r4);
      digitalWrite(ROW5,r5);
      digitalWrite(ROW6,r6);
      digitalWrite(ROW7,r7);
      digitalWrite(ROW8,r8);
     
    // COLUMNS
      digitalWrite(COL1,c1);
      digitalWrite(COL2,c2);
      digitalWrite(COL3,c3);
      digitalWrite(COL4,c4);
      digitalWrite(COL5,c5);
      digitalWrite(COL6,c6);
      digitalWrite(COL7,c7);
      digitalWrite(COL8,c8);
      
      
  delay(delayVal);
}


// White = 1
// Gray = 2
// Orange = 3
// Green = 4
// Black = 5
// Yellow = 6
// Purple = 7
// Blue = 8
