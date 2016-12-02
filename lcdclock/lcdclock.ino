/*
 Simple LCD Timer
 Madnerd.org
 github.com/pigetArduino/lcdclock
-----------------------------------
 Components
-----------------------------------
Arduino Uno 
DFROBOT LCD Keypad Shield

Usage
-----------------------------------
LEFT: -1 minute
RIGHT: +1 minute
UP: +1 hour
DOWN -1 hour
RST: Reset timer
Select: Turn off/on backlight

Source
--------
DFRobot LCD : https://www.dfrobot.com/wiki/index.php/LCD_KeyPad_Shield_For_Arduino_SKU:_DFR0009
Arduino DateTime: http://playground.arduino.cc/Code/DateTime
*/

#include <LiquidCrystal.h>
#include <TimeLib.h>

// Setup lcd screen
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// The backlight led is on pin 10
const int BACKLIGHT = 10;
bool backlight = true;

// define buttons
int lcd_key     = 0;
int adc_key_in  = 0;
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

void setup() {
 //Disable onboard Led
 pinMode(13,OUTPUT);
 digitalWrite(13,LOW);

 //Turn on/off backlight
 pinMode(BACKLIGHT, OUTPUT);
 turnoff();
 delay(1000);
 turnon();
 
 //Serial.begin(9600);

 //Start LCD Screen
 lcd.begin(16, 2);
 //Setup Time
 setTime(0,0,0,1,1,2000);
}

//
void loop() {
  digitalClockDisplay(); //Display Time 
  check_buttons(); //Check Buttons
}


/* Backlight */

void turnoff() {
  digitalWrite(BACKLIGHT, LOW);
}

void turnon() {
  digitalWrite(BACKLIGHT, HIGH);
}


/* Time */

// Add 0 if needed and print to next characters on lcd
void printDigits(byte digits) {
  if (digits < 10)
    lcd.print('0');
  lcd.print(digits);
}

//Make : : blink each seconds
char sep()
{
  if (second() % 2 == 0)
  {
    lcd.print(":");
  }
  else {
    lcd.print(" ");
  }
}


void digitalClockDisplay() {
  //Get current time
  now();

  //Center Text
  lcd.setCursor(4, 0);

  //Print time
  printDigits(hour());
  sep();
  printDigits(minute());
  sep();
  printDigits(second());
  
  // Debug
  //Serial.print(hour());
  //Serial.print(":");
  //Serial.print(minute());
  //Serial.print(":");
  //Serial.println(second());
}


/* BUTTONS */

//Buttons are all on Analog0
int read_LCD_buttons()
{
  adc_key_in = analogRead(0);
  if (adc_key_in > 1000) return btnNONE;
  if (adc_key_in < 50)   return btnRIGHT;
  if (adc_key_in < 195)  return btnUP;
  if (adc_key_in < 380)  return btnDOWN;
  if (adc_key_in < 555)  return btnLEFT;
  if (adc_key_in < 790)  return btnSELECT;
  return btnNONE;  // when all others fail, return this...
}

//Perform actions when buttons are pressed
int check_buttons() {
  lcd_key = read_LCD_buttons();  // read the buttons
  switch (lcd_key)               // depending on which button was pushed, we perform an action
  {

    //+1 hour
    case btnRIGHT:
      {
        adjustTime(3600);
        delay(200);
        break;
      }

    //-1 hour
    case btnLEFT:
      {
       
        adjustTime(-3600);
        //lcd.clear();
        delay(200);
        break;
      }
    //+1 minute
    case btnUP:
      {

        adjustTime(60);

        //lcd.clear();
        delay(200);
        break;
      }

    //-1 minute
    case btnDOWN:
      {     
        adjustTime(-60);
        //lcd.clear();
        delay(200);
        break;
      }

    //On/Off Backlight
    case btnSELECT:
      {
        if (backlight) {
          turnoff();
          backlight = false;
        }
        else {
          turnon();
          backlight = true;
        }
        delay(200);
        break;
      }
    case btnNONE:
      {
        break;
      }
  }
}





