#pragma once

#include "data.h"

class OponentMenu
{
  private:
    LED_cell grid[3][3];
    bool playWithAI = true;

  public:
    OponentMenu()
    {
      for (int i = 0; i < 3; i++)
      {
        for (int j = 0; j < 3; j++)
        {
          grid[i][j].pin = (i * 3 + j);
          pinMode(grid[i][j].pin, OUTPUT);
        }
      }
    }

    short loop(const int left, const int right, const int select)
    {
      for (int i = 0; i < 3; i++)
      {
        for (int j = 0; j < 3; j++)
        {
          if (playWithAI && j == 1) digitalWrite(grid[i][j].pin, HIGH);
          else if (!playWithAI && (j == 0 || j == 2)) digitalWrite(grid[i][j].pin, HIGH);
          else digitalWrite(grid[i][j].pin, LOW);
        }
      }

      if (digitalRead(left) == LOW || digitalRead(right) == LOW) playWithAI = !playWithAI;
      else if (digitalRead(select) == LOW) return (playWithAI) ? 1 : 2;

      return 0;
    }
};
