#pragma once

#include <Vector.h>
#include "TicTacToe.h"
#include "AI.h"
#include "data.h"

#define REQUIRED_TO_WIN 3
#define BOARD_SIZE 3

#define GAME_DELAY 150

class TicTacToeGame : TicTacToe, AI
{
  private:
    int bSize = BOARD_SIZE;
    bool done = false;
    bool playWithAI;
    LED_cell grid[3][3];
    unsigned short x = 0, y = 0;
    bool displayBoard = true;

    int p1_pin;
    int p2_pin;

    boardFill gameDone = boardFill::Empty;
  public:
    TicTacToeGame(bool playWithAI, int p1_pin, int p2_pin) : TicTacToe(BOARD_SIZE, REQUIRED_TO_WIN)
    {
      TicTacToeGame::playWithAI = playWithAI;
      TicTacToeGame::p1_pin = p1_pin;
      TicTacToeGame::p2_pin = p2_pin;

      for (int i = 0; i < 3; i++)
      {
        for (int j = 0; j < 3; j++)
        {
          grid[i][j].pin = (i * 3 + j);
          pinMode(grid[i][j].pin, OUTPUT);
        }
      }
    }

  public:
    void loop(const int left, const int right, const int select)
    {
      digitalWrite(p1_pin, (player1Move) ? HIGH : LOW);
      digitalWrite(p2_pin, (!player1Move)? HIGH : LOW);

      if (gameDone == boardFill::Empty)
      {
        if(displayBoard)
        {
           drawBoard();
           if(digitalRead(select) == LOW) displayBoard = false;
        }
        else
        {

          boardFill player = (player1Move) ? boardFill::Player1 : boardFill::Player2;

          if(digitalRead(select) != LOW || !isEmpty(x, y))
          {
            if(digitalRead(left) == LOW) x--;
            else if(digitalRead(right) == LOW) x++;

            if(x < 0) { x = 2; y--; }
            else if(x > 2) { x = 0; y++; }

            if(y < 0) y = 2;
            else if(y > 2) y = 0;

            drawPoint();
          }
          else
          {
            buttonWait(select);
            move(x, y, player);
            if (playerWin(player))
              gameDone = player;

            if (playWithAI && gameDone == boardFill::Empty)
            {
              auto b = getBoard();
              vec2d v = calculateBestMove(b);
              if (v.x >= b.size() || v.y >= b.size() || b[v.x][v.y] != boardFill::Empty)
                v = getRandomMove(b);
              move(v.x, v.y, boardFill::Player2);
              player1Move = true;

              if (playerWin(boardFill::Player2))
                gameDone = boardFill::Player2;
            }

            if (checkDraw()) gameDone = boardFill::Draw;

            displayBoard = true;
          }
        }


      }
      else
      {
        if (gameDone != boardFill::Draw)
        {
          if(gameDone == boardFill::Player1) {} // Wygrał p1
          else if(gameDone == boardFill::Player1) {} // Wygrał p2
        }
        else {} // Remis
      }

      delay(GAME_DELAY);
    }

  private:
    void drawPoint()
    {
      auto b = getBoard();

      if(b[x][y] != boardFill::Empty) grid[x][y].stat = (grid[x][y].stat == HIGH)? LOW : HIGH;
      else grid[x][y].stat = HIGH;

      for(int i = 0; i < 3; i++)
      {
        for(int j = 0; j < 3; j++)
        {
          if(i == x && j == y) digitalWrite(grid[i][j].pin, grid[i][j].stat);
          else digitalWrite(grid[i][j].pin, LOW);
        }
      }
    }

    void drawBoard()
    {
      auto b = getBoard();

      for(int i = 0; i < b.size(); i++)
      {
        for(int j = 0; j < b[i].size(); j++)
        {
          if(b[i][j] != boardFill::Empty)
          {
            grid[i][j].bf = (b[i][j] == boardFill::Player1)? LED_Board_Fill::Player1 : LED_Board_Fill::Player2;
            if(grid[i][j].bf == LED_Board_Fill::Player1 && grid[i][j].stat != HIGH) grid[i][j].stat = HIGH;
            else grid[i][j].stat = (grid[i][j].stat == HIGH)? LOW : HIGH;
          }
          else grid[i][j].stat = LOW;

          digitalWrite(grid[i][j].pin, grid[i][j].stat);
        }
      }
    }
};
