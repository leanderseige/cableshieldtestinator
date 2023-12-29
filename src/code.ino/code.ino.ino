/*

Cableshieldtestinator

(c) 2023, Leander Seige

This is the software for a 

*/

// #define DEBUG 1

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int analogPin = A0; // Pin, der gelesen werden soll: Pin A3
int val = 0; 

int values[] = {-1,-1,-1,-1};
int progress = -1;
int delta=-1;
int mode=0;

void setup() {
  pinMode(10,OUTPUT);
  pinMode(1,OUTPUT);
  pinMode(2,OUTPUT);
  pinMode(A3,INPUT);
  digitalWrite(10,0);
  digitalWrite(1,0);
  digitalWrite(2,0);

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    for(;;); // Don't proceed, loop forever
  }
  display.clearDisplay();
  display.display();

}

int getAValue() {
  int retval = 0;
  for(int x=0; x<10; x++) {
    retval = retval + analogRead(A3);
  }
  return(retval/10);
}

int updateDisplay() {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.cp437(true);
  if(mode==1) {
    display.setCursor(0, 0); 
    display.setTextSize(2);
    display.print("ANALYZING");
    display.fillRect(0,16,progress,32,WHITE);
#ifdef DEBUG
    display.setTextColor(SSD1306_BLACK);
    display.setTextSize(1);
    for(int x=0;x<4;x++) {
      display.setCursor(32*x+2,16); 
      display.print(values[x]);
    }
    display.setCursor(2, 24); 
    display.print(delta);
    display.setTextColor(SSD1306_WHITE);
#endif
  } else if(mode==2) {
    display.setCursor(0, 0); 
    display.setTextSize(2);
    if(delta<1) {
      display.print("NO CABLE");
    } else {
      display.print(delta>70?"SHIELDED":"UNSHIELDED");
    }    
    display.setTextSize(1); 
    display.setCursor(0, 16); 
    display.print("PRESS BUTTON");
    display.setCursor(0, 24); 
    display.print("TO RESTART");
  } else if(mode==0) {
    display.setCursor(0, 0); 
    display.setTextSize(2);
    display.print("SHIELDTEST");
    display.setTextSize(1); 
    display.setCursor(0, 16); 
    display.print("PRESS BUTTON");
    display.setCursor(0, 24); 
    display.print("TO START");
  }
  display.display();

}

/*
  mode 0 => no result, waiting
  mode 1 => analyzing
  mode 2 => result available, waiting for restart
*/

void loop() {

  updateDisplay();
  
  while(digitalRead(8)) {
    delay(10);
  }

  mode=1;
  values[0]=values[1]=values[2]=values[3]=-1;
  delta=-1;
  progress=0;

  updateDisplay();

  digitalWrite(1,0);
  digitalWrite(2,0);  
  progress=32;
  delay(100);
  values[0] = getAValue();

  updateDisplay();

  digitalWrite(1,0);
  digitalWrite(2,1);  
  progress=64;
  delay(100);
  values[1] = getAValue();

  updateDisplay();

  digitalWrite(1,1);
  digitalWrite(2,0);  
  progress=96;
  delay(100);
  values[2] = getAValue();

  updateDisplay();

  digitalWrite(1,1);
  digitalWrite(2,1);  
  progress=128;
  delay(100);
  values[3] = getAValue();

  updateDisplay();

  int max = -1;
  int min = 9999;
  for(int x=0;x<4;x++) {
    max=max>values[x]?max:values[x];
    min=min<values[x]?min:values[x];
  }

  delta=max-min;

  mode=2;

  updateDisplay();

  digitalWrite(1,0);
  digitalWrite(2,0);  

  delay(500);

}
