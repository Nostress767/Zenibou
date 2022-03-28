#ifndef _ZENIBOU_INPUT_HANDLING_H_
#define _ZENIBOU_INPUT_HANDLING_H_

#include <stdint.h>
#include <stdbool.h>

struct Mouse{
  int16_t x, y;
  bool left_pressed, middle_pressed, right_pressed;
  bool left_held, middle_held, right_held;
  bool left_released, middle_released, right_released;
  bool is_focused;
};

struct Key{
  bool is_pressed, is_held, is_released;
};

extern struct Mouse Mouse;
extern struct Key Key[512];


enum MouseButtons {
  kMouseLeft = 0, kMouseRight = 1, kMouseMiddle = 2
};

// NOTE: do I need to typedef this?
enum OtherKeys {
  kSpace = 32,
  kQuotes = 39,
  kComma = 44, kMinus, kPeriod, kFrontSlash,
  kSemicolon = 59,
  kEqual = 61,
  kLeftBracket = 91, kBackSlash, kRightBracket,
  kBacktick = 96,
  kEscape = 256, kEnter, kTab, kBackspace, kInsert, kDelete, kRight, kLeft, kDown, kUp, kPageUp, kPageDown, kHome, kEnd,
  kCapslock = 280, kScrollLock, kNumLock, kPrintScreen, kPauseBreak,
  kF1 = 290, kF2, kF3, kF4, kF5, kF6, kF7, kF8, kF9, kF10, kF11, kF12,
  kNumpad0 = 320, kNumpad1, kNumpad2, kNumpad3, kNumpad4, kNumpad5, kNumpad6, kNumpad7, kNumpad8, kNumpad9, kDecimal, kDivide, kMultiply, kSubtract, kAdd,
  kLeftShift = 340, kLeftCtrl, kLeftAlt, kLeftSuper, kRightShift = 340, kRightCtrl, kRightAlt, kRightSuper
};

#endif
