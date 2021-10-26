#pragma once

enum class LED_Board_Fill
{
  Player1,
  Player2,
  Empty
};

struct LED_cell
{
  int pin;
  LED_Board_Fill bf = LED_Board_Fill::Empty;
  uint8_t stat = LOW;
};
