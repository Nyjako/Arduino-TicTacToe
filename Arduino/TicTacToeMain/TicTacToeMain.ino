#include "select_oponent.h"
#include "Game.h"

#define BLINK_DELAY 150

const int left   = 11;
const int right  = 12;
const int select = 10;

const int player1_led = 9;
const int player2_led = 13;

short frame = 0;

bool buttonClicked = false;

OponentMenu *om;
TicTacToeGame *tttg;

void setup()
{
  Serial.begin(9600);
  om = new OponentMenu();

  pinMode(player1_led, OUTPUT);
  pinMode(player2_led, OUTPUT);

  pinMode(select, INPUT_PULLUP);
  pinMode(left, INPUT_PULLUP);
  pinMode(right, INPUT_PULLUP);
}

void loop()
{
  if(frame == 0)
  {
    if(!buttonClicked)
    {
      short o = om->loop(left,right,select);
      if(o != 0) 
      {
        Serial.write("Next Frame");
        frame++;
        delete om;
        tttg = new TicTacToeGame(o == 1, player1_led, player2_led);
        
      }
    }

    if(digitalRead(left) == LOW || digitalRead(right) == LOW || digitalRead(select) == LOW) buttonClicked = true;
    else buttonClicked = false;
  }
  else if(frame == 1)
  {
    tttg->loop(left,right,select);
  }

  
}
