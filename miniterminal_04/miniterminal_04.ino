//THIS WORKS WITH TEENSY2.0 = TEENSY
/* Does not use PS2keyboard standard lib, but lib in this folder, to avoid compile error.
 *  PS2keyboard.cpp and PS2Keyboard.h come from Paul Stoffregen, as response 
 *  to a problem help query concerning compile error.
 *  
 * Connections:
 * Keyboard to Arduino pins 4, 5 (and GND, +5V)
 * LCD to Arduino pins 11 - 16
 * 
 * LCD shows typed text
 * Text is sent over Tx (GPIO8), only after pressing <Enter>
 * <Backspace> clears character to the left
 * <Esc> clears all
 * All keystrokes are echoed over USB serial for debugging purposes
  */
   
#include "PS2Keyboard.h"
#include <LiquidCrystal.h>

const int DataPin = 4;
const int IRQpin =  5;
const int rs = 11, en = 12, d4 = 13, d5 = 14, d6 = 15, d7 = 16;

String sendbuffer = "";
String receivebuffer = "";

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
PS2Keyboard keyboard;
//-------------------------------------------------------------------
void setup() {
  
  keyboard.begin(DataPin, IRQpin, PS2Keymap_German);
  //keyboard.begin(DataPin, IRQpin, PS2Keymap_French);
  //keyboard.begin(DataPin, IRQpin, PS2Keymap_US);  
  Serial.begin(115200);
  Serial.println("Mini terminal:");

  Serial1.begin(115200);
  Serial1.println("Mini Terminal");

  lcd.begin(20, 2);
  lcd.clear();
  lcd.print("Mini terminal");
  lcd.setCursor(1,1);
  lcd.blink();
  lcd.print("<ESC> to start");
  
}
//-------------------------------------------------------------------
void setbaud(long baudrate){
   Serial1.begin(baudrate);  
   lcd.clear();
   lcd.print(baudrate);
   lcd.print(" baud");

   Serial.print(baudrate);
   Serial.println(" baud");
}
//-----------------------------------------------------------------

void loop() {
  if (keyboard.available()) {
    
    char c = keyboard.read();
    
    // check for some of the special keys
    
    // Enter -> send over both Tx and empty sendbuffer
    if (c == PS2_ENTER) {             
      Serial.println();
      Serial.println(sendbuffer);
      Serial1.println(sendbuffer);
      sendbuffer = "";
      lcd.clear();
      //lcd.blink()
    }

     // Backspace -> delete character at left in sendbuffer 
     else if (c == PS2_DELETE) {         
      Serial.print("[Del]");
      sendbuffer = sendbuffer.substring(0, sendbuffer.length()-1);
      lcd.clear();
      lcd.print(sendbuffer);
    }

    // Esc -> clear all
    else if (c == PS2_ESC) {
      lcd.clear();
      sendbuffer = "";
      Serial.print("[ESC]");
    
    }

    // Use F keys (defined in PSKeyboard.h as 14-25 (not used otherwise)
    else if (c == PS2_F1) {
        setbaud(115200); 
    }
    else if (c == PS2_F2) {
        setbaud(57600); 
    }
    else if (c == PS2_F3) {
        setbaud(38400); 
    }
    else if (c == PS2_F4) {
        setbaud(19200); 
    }
    else if (c == PS2_F5) {
        setbaud(9600); 
    }
    else if (c == PS2_F6) {
        setbaud(4800); 
    }
    else if (c == PS2_F7) {
        setbaud(2400); 
    }
    else if (c == PS2_F8) {
        setbaud(1200); 
    }
    else if (c == PS2_F9) {
        setbaud(600); 
    }
    else if (c == PS2_F10) {
        setbaud(300); 
    }

    // other keys see PS2Keyboard.h
    
    
    else {
      
      // otherwise, just print all normal characters
      Serial.print(c);
      sendbuffer = sendbuffer + c;
      lcd.clear();
      lcd.print(sendbuffer);
    }
  }


  if (Serial1.available()){
    char r = Serial1.read();
    if (r == 13){
        //Serial1.println(receivebuffer);
        lcd.clear();
        lcd.print(receivebuffer);
        receivebuffer = "";
        Serial1.println();
    }
    else{
    receivebuffer = receivebuffer + r;
    Serial.println(receivebuffer);
    Serial1.print(r);
    }
  }
}
