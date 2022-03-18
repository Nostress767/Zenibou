#ifndef _ZENIBOU_INPUT_HANDLING_H_
#define _ZENIBOU_INPUT_HANDLING_H_

#include <stdint.h>
#include <stdbool.h>

struct Mouse{
  int16_t x, y;
  bool left_pressed, middle_pressed, right_pressed;
  bool is_focused;
};

struct Key{
  bool was_pressed, was_held, was_released;
};

extern struct Mouse Mouse;
extern struct Key Key[256];

enum ASCIILessKeys {
  kEscape = 0x80,
  kUp, kDown, kRight, kLeft, // [0x81, 0x84]
  kTab, kShift, kCtrl, kInsert, kDelete, kHome, kEnd, kPageUp, kPageDown, // [0x85, 0x8D]
  kCapslock, kLMenu, // [0x8E, 0x8F]
  kRMenu, kBackspace, kEnter, kPauseBreak, kScrollLock, // [0x90, 0x94]
  kF1 = 0xF1, kF2, kF3, kF4, kF5, kF6, kF7, kF8, kF9, kF10, kF11, kF12, // [0xF1, 0xFC]
};

void UpdateKeyState(uint32_t key, uint32_t bitfield);
bool IsKeyPressed(int32_t key);
bool IsKeyReleased(int32_t key);

#endif
