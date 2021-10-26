#pragma once

#include "TicTacToe.h"
#include <Vector.h>

struct vec2d
{
  unsigned short x, y;

  vec2d(unsigned short x = 0, unsigned short y = 0)
  {
    vec2d::x = x;
    vec2d::y = y;
  }

  bool operator==(const vec2d& rhs)
  {
    return x == rhs.x && y == rhs.y;
  }
};

class AI
{
private:
  static const unsigned short requiredToWin = 3;

  template <typename T>
  static T rv(Vector<T> a)
  {
    if (a.size() > 0) return a[random(a.size())];
  }

  static Vector<vec2d> appendVector(Vector<vec2d> source, Vector<vec2d> child)
  {
    Vector<vec2d> out = source;
    for (vec2d i : child) out.push_back(i);
    return out;
  }

  template <typename T>
  static Vector<T> findSameElement(Vector<T> v1, Vector<T> v2)
  {
    Vector<T> sameElements;
    for (auto i : v1)
      for (auto j : v2)
        if (i == j)
          sameElements.push_back(i);
    return sameElements;
  }

  static vec2d* findWin(Vector< Vector<boardFill> > board, boardFill toSearch)
  {
    vec2d* empty1 = nullptr, * empty2 = nullptr, * empty3 = nullptr, * empty4 = nullptr;
    bool b1 = true, b2 = true, b3 = true, b4 = true;

    for (int i = 0; i < board.size(); i++)
    {
      for (int j = 0; j < board[i].size(); j++)
      {
        if (b1)
        {
          if (board[i][j] == boardFill::Empty && empty1 == nullptr) empty1 = new vec2d(i, j);
          else if (board[i][j] != toSearch)
          {
            empty1 = nullptr;
            b1 = false;
          }
        }

        if (b2)
        {
          if (board[j][i] == boardFill::Empty && empty2 == nullptr) empty2 = new vec2d(j, i);
          else if(board[j][i] != toSearch)
          {
            empty2 = nullptr;
            b2 = false;
          }
        }
      }

      if (empty1 != nullptr && b1)
      {
        delete empty2, empty3, empty4;
        return empty1;
      }
      else if (empty2 != nullptr && b2)
      {
        delete empty1, empty3, empty4;
        return empty2;
      }
      else
      {
        if (b3)
        {
          if (board[i][i] == boardFill::Empty && empty3 == nullptr) empty3 = new vec2d(i, i);
          else if(board[i][i] != toSearch)
          {
            empty3 = nullptr;
            b3 = false;
          }
        }
        if (b4)
        {
          if (board[board.size() - i - 1][i] == boardFill::Empty && empty4 == nullptr) empty4 = new vec2d(board.size() - i - 1, i);
          else if (board[board.size() - i - 1][i] != toSearch)
          {
            empty4 = nullptr;
            b4 = false;
          }
        }
      }
      b1 = true;
      b2 = true;
    }
    if (empty3 != nullptr && b3)
    {
      delete empty1, empty2, empty4;
      return empty3;
    }
    else if (empty4 != nullptr && b4)
    {
      delete empty1, empty2, empty3;
      return empty4;
    }
    else return nullptr;
  }

  static Vector<vec2d> findPosibeWin(Vector< Vector<boardFill> > board, boardFill toSearch)
  {
    vec2d* empty1 = nullptr, * empty2 = nullptr, * empty3 = nullptr, * empty4 = nullptr;
    unsigned short counter1 = 0, counter2 = 0, counter3 = 0, counter4 = 0;
    Vector<vec2d> temp1, temp2, temp3, temp4;

    Vector<vec2d> posibleMoves;

    for (int i = 0; i < board.size(); i++)
    {
      for (int j = 0; j < board.size(); j++)
      {
        if (counter1 != -1)
        {
          if (board[i][j] == boardFill::Empty) temp1.push_back((i, j));
          else if (board[i][j] != toSearch)
          {
            temp1.clear();
            counter1 = -1;
          }
        }

        if (counter2 != -1)
        {
          if (board[j][i] == boardFill::Empty) temp2.push_back((j, i));
          else if (board[j][i] != toSearch)
          {
            temp2.clear();
            counter2 = -1;
          }
        }
      }

      if (!temp1.empty()) posibleMoves = appendVector(posibleMoves, temp1);
      else if (!temp2.empty()) posibleMoves = appendVector(posibleMoves, temp2);
      else
      {
        if (counter3 != -1)
        {
          if (board[i][i] == boardFill::Empty) temp3.push_back((i, i));
          else if (board[i][i] != toSearch)
          {
            temp3.clear();
            counter3 = -1;
          }
        }
        if (counter4 != -1)
        {
          if (board[board.size() - i - 1][i] == boardFill::Empty) temp4.push_back((board.size() - i - 1, i));
          else if (board[board.size() - i - 1][i] != toSearch)
          {
            temp4.clear();
            counter4 = -1;
          }
        }
      }
      counter1 = 0; counter2 = 0;
    }
    if (!temp3.empty()) posibleMoves = appendVector(posibleMoves, temp3);
    else if (!temp4.empty()) posibleMoves = appendVector(posibleMoves, temp4);
    delete empty1, empty2, empty3, empty4;
    return posibleMoves;
  }

  static Vector<vec2d> findEmptyLines(Vector< Vector<boardFill> > board)
  {
    vec2d* empty1 = nullptr, * empty2 = nullptr, * empty3 = nullptr, * empty4 = nullptr;
    unsigned short counter1 = 0, counter2 = 0, counter3 = 0, counter4 = 0;
    Vector<vec2d> temp1, temp2, temp3, temp4;

    Vector<vec2d> posibleMoves;

    for (int i = 0; i < board.size(); i++)
    {
      for (int j = 0; j < board.size(); j++)
      {
        if (counter1 != -1)
        {
          if (board[i][j] == boardFill::Empty) temp1.push_back((i, j));
          else
          {
            temp1.clear();
            counter1 = -1;
          }
        }

        if (counter2 != -1)
        {
          if (board[j][i] == boardFill::Empty) temp2.push_back((j, i));
          else
          {
            temp2.clear();
            counter2 = -1;
          }
        }
      }

      if (!temp1.empty()) posibleMoves = appendVector(posibleMoves, temp1);
      else if (!temp2.empty()) posibleMoves = appendVector(posibleMoves, temp2);
      else
      {
        if (counter3 != -1)
        {
          if (board[i][i] == boardFill::Empty) temp3.push_back((i, i));
          else
          {
            temp3.clear();
            counter3 = -1;
          }
        }
        if (counter4 != -1)
        {
          if (board[board.size() - i - 1][i] == boardFill::Empty) temp4.push_back((board.size() - i - 1, i));
          else
          {
            temp4.clear();
            counter4 = -1;
          }
        }
      }
      counter1 = 0; counter2 = 0;
    }
    if (!temp3.empty()) posibleMoves = appendVector(posibleMoves, temp3);
    else if (!temp4.empty()) posibleMoves = appendVector(posibleMoves, temp4);
    delete empty1, empty2, empty3, empty4;
    return posibleMoves;
  }

  static Vector<vec2d> getAllPosibleMoves(Vector< Vector<boardFill> > board)
  {
    Vector<vec2d> out;
    for (int i = 0; i < board.size(); i++)
      for (int j = 0; j < board.size(); j++)
        if (board[i][j] == boardFill::Empty)
          out.push_back((i, j));
    return out;
  }

  static void cleanVector(Vector<vec2d> &source, Vector< Vector<boardFill> > board)
  {
    for (int i = 0; i < source.size(); i++)
    {
      if (i >= 0 && i < source.size())
      {
        for (int j = i + 1; j < source.size(); j++)
        {
          if (source[i] == source[j])
          {
            source.remove(j);
            i--;
            break;
          }
        }

        if (i >= 0 && i < source.size() && (board[source[i].x][source[i].y] != boardFill::Empty || source[i].x > board.size() || source[i].y > board.size()))
        {
          source.remove(i);
          i--;
        }
      }
    }
  }

protected:
  static vec2d calculateBestMove(Vector< Vector<boardFill> > board)
  {
    if (board[1][1] == boardFill::Empty) return vec2d(1, 1);

    // ruch wygrywajacy
    vec2d* temp = findWin(board, boardFill::Player2);
    if (temp != nullptr)
    {
      return *temp;
    }

    // Blokuje wygrana gracza
    temp = findWin(board, boardFill::Player1);
    if (temp != nullptr)
    {
      return *temp;
    }

    // Szuka pustych lini z jednym znakiem AI do budowy
    auto posibleWin = findPosibeWin(board, boardFill::Player2);
    if (!posibleWin.empty())
    {
      cleanVector(posibleWin, board);
    }

    // Szuka pustych lini z jednym znakiem gracza do zablokowania
    auto posibleBlock = findPosibeWin(board, boardFill::Player1);
    if (!posibleBlock.empty())
    {
      cleanVector(posibleBlock, board);
    }

    // Szuka pustych lini
    auto emptyLines = findEmptyLines(board);
    if (!emptyLines.empty())
    {
      cleanVector(emptyLines, board);
    }

    if (!posibleWin.empty() && !posibleBlock.empty())
    {
      // porownanie czy jest mozliwosc jednoczesnego blokowania jak i budowy
      auto blockAndBuild = findSameElement(posibleWin, posibleBlock);
      if (!blockAndBuild.empty())
      {
        // Czy�ci vector z powtarzaj�cych sie elementow
        cleanVector(blockAndBuild, board);
        if (!emptyLines.empty())
        {
          // porownanie czy jest mozliwosc jednoczesnego blokowania jak i budowy oraz zajecia pustej lini
          auto blockBuildAndEmptyLine = findSameElement(blockAndBuild, emptyLines);
          if (!blockBuildAndEmptyLine.empty())
          {
            // Czy�ci vector z powtarzaj�cych sie elementow
            cleanVector(blockBuildAndEmptyLine, board);
            return rv(blockBuildAndEmptyLine); // I tak lecimy do ko�ca
          }
          else return rv(blockAndBuild);
        }
        else return rv(blockAndBuild);
      }
      else return rv(posibleWin);
    }
    else if (!posibleWin.empty())
    {
      if (!emptyLines.empty())
      {
        auto winAndEmpty = findSameElement(emptyLines, posibleWin);
        if (!winAndEmpty.empty())
        {
          cleanVector(winAndEmpty, board);
          return rv(winAndEmpty);
        }
        else return rv(emptyLines);
      }
      else return rv(posibleWin);
    }
    else if (!posibleBlock.empty()) return rv(posibleBlock);
    else
    {
      auto all = getAllPosibleMoves(board);
      if (!all.empty())
      {
        cleanVector(all, board);
      }
      return rv(all);
    }
  }
  
  static vec2d getRandomMove(Vector< Vector<boardFill> > board)
  {
    Vector<vec2d> out;
    for (int i = 0; i < board.size(); i++)
      for (int j = 0; j < board.size(); j++)
        if (board[i][j] == boardFill::Empty)
          out.push_back((i, j));

    if (!out.empty()) return rv(out);
    else return (-1, -1);

  }
};
