#include "select_oponent.h"
#include "Game.h"
#include "Functions.h"

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

void clear_leds_status()
{
  for(int i = 0; i <= 13; i++)
    if(i != left && i != right && i != select)
      digitalWrite(i, LOW);
}

void setup()
{
  om = new OponentMenu();

  pinMode(player1_led, OUTPUT);
  pinMode(player2_led, OUTPUT);

  pinMode(select, INPUT_PULLUP);
  pinMode(left, INPUT_PULLUP);
  pinMode(right, INPUT_PULLUP);

  Serial.begin(9600);
}

void loop()
{

  clear_leds_status();
  if(frame == 0)
  {
    short o = om->loop(left,right,select);
    if(o != 0) 
    {
      frame++;
      delete om;
      tttg = new TicTacToeGame(o == 1, player1_led, player2_led);
      buttonWait(select);
      buttonWait(left);
      buttonWait(right);
    }
  }
  else if(frame == 1)
  {
    tttg->loop(left,right,select);
  }

  
}
