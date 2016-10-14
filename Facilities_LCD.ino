// URTouch_ButtonTest
// Copyright (C)2015 Rinky-Dink Electronics, Henning Karlsen. All right reserved
// web: http://www.RinkyDinkElectronics.com/
//
// This program is a quick demo of how create and use buttons.
//
// This program requires the UTFT library.
//
// It is assumed that the display module is connected to an
// appropriate shield or that you know how to change the pin
// numbers in the setup.
//

#include <UTFT.h>
#include <URTouch.h>

// Initialize display
// ------------------
// Set the pins to the correct ones for your development board
// -----------------------------------------------------------
// Standard Arduino Uno/2009 Shield            : <display model>,19,18,17,16
// Standard Arduino Mega/Due shield            : <display model>,38,39,40,41
// CTE TFT LCD/SD Shield for Arduino Due       : <display model>,25,26,27,28
// Teensy 3.x TFT Test Board                   : <display model>,23,22, 3, 4
// ElecHouse TFT LCD/SD Shield for Arduino Due : <display model>,22,23,31,33
//
// Remember to change the model parameter to suit your display module!
UTFT    myGLCD(SSD1289, 38, 39, 40, 41);

// Initialize touchscreen
// ----------------------
// Set the pins to the correct ones for your development board
// -----------------------------------------------------------
// Standard Arduino Uno/2009 Shield            : 15,10,14, 9, 8
// Standard Arduino Mega/Due shield            :  6, 5, 4, 3, 2
// CTE TFT LCD/SD Shield for Arduino Due       :  6, 5, 4, 3, 2
// Teensy 3.x TFT Test Board                   : 26,31,27,28,29
// ElecHouse TFT LCD/SD Shield for Arduino Due : 25,26,27,29,30
//
URTouch  myTouch( 6, 5, 4, 3, 2);

// Declare which fonts we will be using
extern uint8_t BigFont[];

int x, y;

char* titleStr[] = {"CDA PSI","H2O Temp C","H2O PSI","Vac In H2O","Conc Tank"};

/*************************
**   Custom functions   **
*************************/


void drawButtons()
{
  // Draw the Title Bar
  for (x = 0; x < 5; x++)
  {
    
   //Title Block
    myGLCD.setBackColor(VGA_WHITE);
    myGLCD.setColor(VGA_WHITE); //set color
    myGLCD.fillRoundRect (8, 8, 312, 40); //draw filled rounded rectangle
    myGLCD.setColor(VGA_GREEN); // set color
    myGLCD.drawRoundRect (8, 8, 312, 40);
    myGLCD.setColor(VGA_BLACK);
    myGLCD.print("Facilities Monitor",CENTER,16);
    
    //Descriptions
    myGLCD.setColor(VGA_WHITE); //set color
    myGLCD.fillRoundRect (8, 46 + (x * 26), 312, 66 + (x * 26)); //draw filled rounded rectangle
    //myGLCD.setColor(VGA_GREEN); // set color
    //myGLCD.drawRoundRect (8, 44 + (x * 24), 312, 68 + (x * 28));
    myGLCD.setColor(VGA_BLACK);
    myGLCD.print(titleStr[x], 8 , 48 + (x * 26));
    
    //Alarm Button
    myGLCD.setColor(VGA_RED); //set color
    myGLCD.fillRoundRect (8, 200, 312, 232); //draw filled rounded rectangle
    myGLCD.setColor(VGA_WHITE); // set color
    myGLCD.drawRoundRect (8, 200, 312, 232);
    myGLCD.setColor(VGA_BLACK);
    myGLCD.setBackColor(VGA_RED);
    myGLCD.print("Silence Alarm", CENTER , 208);
    
  }
} 
void updateValues()
{
  if (y < 25)
  {
    for(x = 0; (x < 5) ; x++) 
    {
      myGLCD.setColor(VGA_BLACK);
      myGLCD.setBackColor(VGA_WHITE);
      myGLCD.printNumI(y, 280 , 48 + (x*26),2);      
    }
  }
  else
  {
    y=-1;
  }
}
/*
// Draw a red frame while a button is touched
void waitForIt(int x1, int y1, int x2, int y2)
{
  myGLCD.setColor(255, 0, 0);
  myGLCD.drawRoundRect (x1, y1, x2, y2);
  while (myTouch.dataAvailable())
    myTouch.read();
  delay(50);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (x1, y1, x2, y2);

}
*/
/*************************
**  Required functions  **
*************************/

void setup()
{
  // Initial setup
  myGLCD.InitLCD(LANDSCAPE);
  myGLCD.clrScr();

  myTouch.InitTouch(LANDSCAPE);
  myTouch.setPrecision(PREC_MEDIUM);

  myGLCD.setFont(BigFont);
  myGLCD.setBackColor(255,255,255);
  drawButtons();
}

void loop()
{
  
  x=0;
  updateValues();
  y++;
  delay(100);
  
  
  /*
  while (true)
  {
    if (myTouch.dataAvailable())
    {
      myTouch.read();
      delay(50);
      x = myTouch.getX();
      y = myTouch.getY();

      if (y <= 120) // Upper half
      {
        //myGLCD.clrScr();
        myGLCD.fillScr(255,0,0);
      }

      if (y < 120) // Lower half
      {
        //myGLCD.clrScr();
        myGLCD.fillScr(0,255,0);
      }

      else
      {
        //myGLCD.clrScr();
        myGLCD.fillScr(255,0,0);
      }
         
    }
  }*/
}

