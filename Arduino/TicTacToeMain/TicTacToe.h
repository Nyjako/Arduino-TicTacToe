#pragma once

#include <Vector.h>

enum class boardFill
{
  Player1,
  Player2,
  Empty,
  Draw
};



class Board
{
  virtual void boardClass() = 0;

private:
  Vector< Vector<boardFill> > board;
  unsigned short size = 0;
protected:
  void create(unsigned short size)
  {
    Board::size = size;
    for (int i = 0; i < size; i++)
    {
      board.push_back(Vector<boardFill>());
      for (int j = 0; j < size; j++)
        board[i].push_back(boardFill::Empty);
    }
  }

  const unsigned short getSize()
  {
    return size;
  }

  const boardFill get(int x, int y)
  {
    return board[x][y];
  }

  const Vector< Vector<boardFill> > getBoard()
  {
    return board;
  }

  bool set(int x, int y, boardFill bf)
  {
    if (x < size && y < size)
    {
      board[x][y] = bf;
      return true;
    }
    return false;
  }
};

class TicTacToe : Board
{
  void boardClass() override {}

protected:
  bool player1Move = true;
  unsigned short requiredToWin;

  TicTacToe(unsigned short size, unsigned short requiredToWin = 3)
  {
    TicTacToe::requiredToWin = requiredToWin;
    create(size);
  }

  bool move(int x, int y, boardFill player)
  {
    if (x < getSize() && y < getSize())
    {
      boardFill b = get(x, y);
      if (b == boardFill::Empty)
      {
        set(x, y, player);
        player1Move = !player1Move;
        return true;
      }
    }
    return false;
  }

  bool playerWin(boardFill player)
  {
    unsigned short counter = 0;
    for (int i = 0; i < getSize(); i++)
    {
      for (int j = 0; j < getSize(); j++)
      {
        if (i + requiredToWin <= getSize())
        {
          for (int x = i; x < i + requiredToWin; x++)
          {
            if (get(x, j) == player) counter++;
            else
            {
              counter = 0;
              break;
            }
          }
          if (counter == requiredToWin) return true;
        }
        if (j + requiredToWin <= getSize())
        {
          for (int x = j; x < j + requiredToWin; x++)
          {
            if (get(i, x) == player) counter++;
            else
            {
              counter = 0;
              break;
            }
          }
          if (counter == requiredToWin) return true;
        }
        if (i + requiredToWin <= getSize() && j + requiredToWin <= getSize())
        {
          for (int x = 0; x < requiredToWin; x++)
          {
            if (get(i + x, j + x) == player) counter++;
            else
            {
              counter = 0;
              break;
            }
          }
          if (counter == requiredToWin) return true;


          for (int x = 0; x < requiredToWin; x++)
          {
            if (get(i + x, j + requiredToWin - x - 1) == player) counter++;
            else
            {
              counter = 0;
              break;
            }
          }
          if (counter == requiredToWin) return true;
        }

      }
    }
    return false;
  }

  bool checkDraw()
  {
    auto b = getBoard();
    for (auto i : b)
      for (auto j : i)
        if (j == boardFill::Empty)
          return false;
    if (playerWin(boardFill::Player1) || playerWin(boardFill::Player2))
      return false;
    return true;
  }

  const boardFill get(int x, int y)
  {
    return Board::get(x,y);
  }

  const Vector< Vector<boardFill> > getBoard()
  {
    return Board::getBoard();
  }
};
