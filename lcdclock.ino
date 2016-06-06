#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

const int BACKLIGHT = 10;

int initialHours = 0;//variable to initiate hours
int initialMins = 0;//variable to initiate minutes
int initialSecs = 00;//variable to initiate seconds
bool backlight = true;

// define some values used by the panel and buttons
int lcd_key     = 0;
int adc_key_in  = 0;
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5


void setup() {
  pinMode(BACKLIGHT, OUTPUT);
 pinMode(13,OUTPUT);
 digitalWrite(13,LOW);
  turnoff();
  delay(1000);
  turnon();
  //Serial.begin(9600);
  lcd.begin(16, 2);
}

//this loop will conintue to keep looping so that the time can go as follows
void loop() {
  digitalClockDisplay();
  check_buttons();
}

void turnoff() {
  digitalWrite(BACKLIGHT, LOW);
}

void turnon() {
  digitalWrite(BACKLIGHT, HIGH);
}

//thhis is a list of int variables used in this clock program
unsigned long s = 0;
unsigned long sec = 0;
unsigned long hrs = 0;
unsigned long minutes = 0;

//this method is for seconds
unsigned long seconds()
{
  s = initialHours * 3600;
  s = s + (initialMins * 60);
  s = s + initialSecs;
  s = s + (millis() / 1000);
  return s;
}
//this method is for hours
unsigned long hours()
{
  hrs = seconds();
  hrs = hrs / 3600;
  hrs = hrs % 24;
  return hrs;
}
//this method is for minutes
unsigned long mins()
{
  minutes = seconds();
  minutes = minutes / 60;
  minutes = minutes % 60;
  return minutes;
}

unsigned long secs()
{
  sec = seconds();
  sec = sec % 60;
  return sec;
}

void printDigits(byte digits) {
  if (digits < 10)
    lcd.print('0');
  lcd.print(digits);
}

char sep()
{
  s = millis() / 1000;
  if (s % 2 == 0)
  {
    lcd.print(":");
  }
  else {
    lcd.print(" ");
  }
}


void digitalClockDisplay() {
  lcd.setCursor(4, 0);
  printDigits(hours());
  sep();
  printDigits(mins());
  sep();
  printDigits(secs());
  //Serial.print(hours());
  //Serial.print(":");
  //Serial.print(mins());
  //Serial.print(":");
  //Serial.println(secs());
}


/* BUTTONS */
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

int check_buttons() {
  lcd_key = read_LCD_buttons();  // read the buttons
  switch (lcd_key)               // depending on which button was pushed, we perform an action
  {
    case btnRIGHT:
      {
           initialSecs =  initialSecs + 3600;
        //lcd.clear();
        delay(200);
        break;
      }
    case btnLEFT:
      {
       
           initialSecs =  initialSecs - 3600;
        //lcd.clear();
        delay(200);
        break;
      }
    case btnUP:
      {

          initialSecs = initialSecs + 60;

        //lcd.clear();
        delay(200);
        break;
      }
    case btnDOWN:
      {     
          initialSecs = initialSecs - 60;
          
        //lcd.clear();
        delay(200);
        break;
      }
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





