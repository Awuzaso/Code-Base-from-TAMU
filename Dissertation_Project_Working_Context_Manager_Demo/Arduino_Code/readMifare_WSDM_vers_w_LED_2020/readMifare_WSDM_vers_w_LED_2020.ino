#include <stdio.h>
#include <stdlib.h>

#include <Wire.h>
#include <SPI.h>
#include "Adafruit_PN532.h"

// If using the breakout with SPI, define the pins for SPI communication.
#define PN532_SCK  (2)
#define PN532_MOSI (3)
#define PN532_SS   (4)
#define PN532_MISO (5)

// #define DEBUG ;

// If using the breakout or shield with I2C, define just the pins connected
// to the IRQ and reset lines.  Use the values below (2, 3) for the shield!
#define PN532_IRQ   (2)
#define PN532_RESET (3)  // Not connected by default on the NFC Shield

// Uncomment just _one_ line below depending on how your breakout or shield
// is connected to the Arduino:

// Use this line for a breakout with a software SPI connection (recommended):
Adafruit_PN532 nfc(PN532_SCK, PN532_MISO, PN532_MOSI, PN532_SS);

// Use this line for a breakout with a hardware SPI connection.  Note that
// the PN532 SCK, MOSI, and MISO pins need to be connected to the Arduino's
// hardware SPI SCK, MOSI, and MISO pins.  On an Arduino Uno these are
// SCK = 13, MOSI = 11, MISO = 12.  The SS line can be any digital IO pin.
//Adafruit_PN532 nfc(PN532_SS);

// Or use this line for a breakout or shield with an I2C connection:
//Adafruit_PN532 nfc(PN532_IRQ, PN532_RESET);

#if defined(ARDUINO_ARCH_SAMD)
// for Zero, output on USB Serial console, remove line below if using programming port to program the Zero!
// also change #define in Adafruit_PN532.cpp library file
   #define Serial SerialUSB
#endif


////////////////////////////
//https://forum.arduino.cc/index.php?topic=288234.0
char receivedChar;
boolean newData = false;
const int RED_PIN = 8;
const int GREEN_PIN = 9;
const int BLUE_PIN = 10;
const int DISPLAY_TIME = 8; 
char *_GG_prevUIDStr ;  // This should always hold the previous uid read. 
char *_GG_currUIDStr ;  // This is the new UID. It should be copied to _GG_prevUIDStr after comparing
boolean _GG_cardChanged = false ;

// used in mainColors() to determine the 
// length of time each color is displayed.
//////////////////////////


void setup(void) {
  // Setup the global UID strings
  _GG_prevUIDStr = malloc (9) ;
  _GG_currUIDStr = malloc (9) ;

  strcpy(_GG_prevUIDStr, "00000000\n");
  strcpy(_GG_prevUIDStr, "00000000\n");
  
  
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  digitalWrite(RED_PIN, HIGH);
  digitalWrite(GREEN_PIN, HIGH);
  digitalWrite(BLUE_PIN, HIGH);
  
  #ifndef ESP8266
    while (!Serial); // for Leonardo/Micro/Zero
  #endif


//  Serial.begin(9600);

  
//  Serial.begin(115200);

  Serial.begin(230400);

  nfc.begin();
  
  // configure board to read RFID tags
  nfc.SAMConfig();
}






////////////
//https://stackoverflow.com/questions/27448168/conversion-of-uint8-t-to-a-string-c
void *convert(uint8_t *a)
{
 // char* buffer2;
  int i;

//  buffer2 = malloc(9);
//  if (!buffer2)
//    return NULL;

  //char *_GG_newUIDStr[8] = 0;
  for (i = 0; i <= 7; i++)
    _GG_currUIDStr[7 - i] = (((*a) >> i) & (0x01)) + '0';

#ifdef DEBUG
  puts(buffer2);
#endif

  //return _GG_newUIDStr ;
}
///////////////




bool deadManActive = false;


 bool cardIsOnReader = false;

void setLEDGreen(){
    digitalWrite(GREEN_PIN, LOW);
    digitalWrite(RED_PIN, HIGH);
    digitalWrite(BLUE_PIN,HIGH);
}

void setLEDBlue(){
    digitalWrite(RED_PIN, HIGH);
    digitalWrite(GREEN_PIN,HIGH);
    digitalWrite(BLUE_PIN,LOW);
}

void blinkYellow(){
//      digitalWrite(RED_PIN, LOW);
//      digitalWrite(GREEN_PIN, LOW);
//      digitalWrite(BLUE_PIN, LOW);
      delay(250);   // Delay for 10 ms (1/100th of a second) - to help the "smoothing"
       digitalWrite(RED_PIN, LOW);
      digitalWrite(GREEN_PIN, LOW);
      digitalWrite(BLUE_PIN, HIGH);
      delay(250);   // Delay for 10 ms (1/100th of a second) - to help the "smoothing"

}

void blinkRed(){

    int iterate = 0;
    while(iterate != 4){
      iterate=iterate+1;
      digitalWrite(RED_PIN, HIGH);
      digitalWrite(GREEN_PIN,HIGH);
      digitalWrite(BLUE_PIN, HIGH);
      
      delay(125);   // Delay for 10 ms (1/100th of a second) - to help the "smoothing"
      
      digitalWrite(RED_PIN, LOW);
      digitalWrite(GREEN_PIN, HIGH);
      digitalWrite(BLUE_PIN, HIGH);
      
      delay(125);   // Delay for 10 ms (1/100th of a second) - to help the "smoothing"
      
    }

}

void turnOffLED(){
    digitalWrite(RED_PIN, LOW);
    digitalWrite(GREEN_PIN, LOW);
    digitalWrite(BLUE_PIN,LOW);
}


boolean gg_systemIsIdle = true;
 
bool redLEDIsOff = true;

bool gg_systemIsActive = false;



void loop(void) {

  static char *preVal = malloc(9) ;
  
  uint8_t success;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer to store the returned UID
  uint8_t uidLength;
  uint16_t timeout = 250;
 
  
  
  //Serial.println("The loop is starting.");
  //Serial.println(cardIsOnReader);

//  if(cardIsOnReader == true){
//    digitalWrite(RED_PIN, HIGH);
//    digitalWrite(GREEN_PIN, HIGH);
//    digitalWrite(BLUE_PIN,HIGH);
//    Serial.print("Card is on reader...");
//    cardIsOnReader=false;
//  }
//  else{
//    digitalWrite(RED_PIN, HIGH);
//    digitalWrite(GREEN_PIN, LOW);
//    digitalWrite(BLUE_PIN,HIGH);
//    Serial.print("Card is not on reader...");
//  }

  if(gg_systemIsIdle==true){
    setLEDGreen () ; // if the card reads immediately, green should just flash on and off every cycle.

    redLEDIsOff = true;
  }               // If the nfc.Read blocks (i.e. no card), the green stays on till a card is read
//  else if(gg_systemIsActive == true){
//    // system Is active
//    setLEDBlue();
//  }
  else{
    //turnOffLED();
    redLEDIsOff = false;
  }
  
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength,timeout);
  
  if (success) {
   
        convert(uid); // convert uid into _GG_currUIDStr

        //if(prevVal != *final_string){
        if (strcmp(_GG_prevUIDStr, _GG_currUIDStr) ) { // Check if the strings are different
          
            strcpy (_GG_prevUIDStr, _GG_currUIDStr) ;
//            strcpy (_GG_currUIDStr, "00000000\n") ;
            _GG_cardChanged = true ; // This flag tells the system to inform the context manager to change contexts
#ifdef DEBUG
            //Serial.print("New value.");
#endif
            // need to free preVal - better to have static preValStr and newValStr and always read into newValStr. 
            // If different then copy newValStr to preValStr and zero out newValStr.
//            free(preVal) ;              // This construction is asking for a memory leak and needs constant request for new strings
//            prevVal = *final_string;


            // We have a new card, so blink yellow
            blinkYellow () ;
            
            // setLEDYellow()
            
            
            cardIsOnReader = true;
            //Serial.println("Card value is now:");
            //Serial.println(cardIsOnReader);
            /* WHAT IS BEING SENT*/
           // Serial.print("\n");
            Serial.print("_");
            nfc.PrintHex(uid, uidLength);
            Serial.print("\n");
            /*/////////////////////////////*/ 
        }
        else{ // case where same card is being read
          _GG_cardChanged = false ; 
          /* WHAT IS BEING SENT*/
//            Serial.print("_");
//            nfc.PrintHex(uid, uidLength);
              //Serial.print("\n");
            /*/////////////////////////////*/ 
//            Serial.print("Old value.");
            //blueColorTransition();

            digitalWrite(RED_PIN, HIGH);
            digitalWrite(GREEN_PIN, HIGH);
            digitalWrite(BLUE_PIN,LOW);
            
//            digitalWrite(RED_PIN, LOW);
//            digitalWrite(GREEN_PIN, LOW);
//            digitalWrite(BLUE_PIN,LOW);
//            delay(500);   // Delay for 10 ms (1/100th of a second) - to help the "smoothing"
//            digitalWrite(RED_PIN, HIGH);
//            digitalWrite(GREEN_PIN, HIGH);
//            digitalWrite(BLUE_PIN, HIGH);
//            cardIsOnReader = true;
//            Serial.println("Card value is now:");
//            Serial.println(cardIsOnReader);
            //gg_systemIsActive = true;
            gg_systemIsIdle = false;
        }   
     
  }
  else{
    Serial.println("Reader timed out.");
    if(redLEDIsOff == false){
      strcpy(_GG_prevUIDStr, "00000000\n");
      strcpy(_GG_prevUIDStr, "00000000\n");
      blinkRed();
      /* WHAT IS BEING SENT*/
            //Serial.print("\n");
            //Serial.print("_");
            Serial.print("XXXXXX\n");
            /*/////////////////////////////*/ 
      // Send a flag to the system to disengage card if associated.
    }
    gg_systemIsIdle = true;
                

  }
  

}

/*--------------------------------------------------------------*/
/* SUPPORT FUNCTIONS*/
/*--------------------------------------------------------------*/

void blueColorTransition(){
  
  //Serial.println("////////////");
  int val=0;
  int increm = 20;
  while(val != 255){
      int inVal=255-val;
      analogWrite(BLUE_PIN,inVal);
      analogWrite(RED_PIN,255);
      analogWrite(GREEN_PIN,255);
//      delay(20);

//      delay(DISPLAY_TIME);
      delay(1);

      val=val+1;
//        val=val+increm;
//      Serial.println(val);
  }
  
  //Serial.println("xxxxxxxxxxxxxx");
  delay(1000);
  val = 255;

  while(val != 0){
     int inVal=255-val;
     analogWrite(BLUE_PIN,inVal);
     analogWrite(RED_PIN,255);
     analogWrite(GREEN_PIN,255);
//     delay(DISPLAY_TIME);
      delay(1);

     val=val-1;
//      val-val-increm;
     Serial.println(val);
  }
}


void recvOneChar() {
 if (Serial.available() > 0) {
 receivedChar = Serial.read();
 newData = true;
 
 }
}

void showNewData() {
     if (newData == true) {
        //Serial.print("This just in ... ");
        //Serial.println(receivedChar);
         if(receivedChar == 'H'){
            blueColorTransition();
         }
         
         if(receivedChar == 'i'){
            digitalWrite(RED_PIN, LOW);
            digitalWrite(GREEN_PIN, LOW);
            digitalWrite(BLUE_PIN, HIGH);
            delay(2000);
         }
         
         if(receivedChar == 'z'){
            digitalWrite(RED_PIN, LOW);
            digitalWrite(GREEN_PIN, HIGH);
            digitalWrite(BLUE_PIN,HIGH);
            delay(2000);
     }
     
    
    
    newData = false;
 }
 digitalWrite(RED_PIN, HIGH);
 digitalWrite(GREEN_PIN, HIGH);
 digitalWrite(BLUE_PIN, HIGH);
}
