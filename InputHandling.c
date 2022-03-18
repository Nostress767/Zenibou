#ifndef _ZENIBOU_INPUT_HANDLING_C_
#define _ZENIBOU_INPUT_HANDLING_C_

#define WIN32_LEAN_AND_MEAN
#define UNICODE
#include <windows.h>
#include "InputHandling.h"
struct Mouse Mouse;

struct Key Key[256] = {0};

void UpdateKeyState(uint32_t key, uint32_t bitfield){
  bool was_down = bitfield >> 30 & 1;
  bool is_down = bitfield >> 31 ^ 1;

  uint32_t mapped_key = key;

  switch(key){
    case 'A':case 'B':case 'C':case 'D':case 'E':case 'F':case 'G':case 'H':
    case 'I':case 'J':case 'K':case 'L':case 'M':case 'N':case 'O':case 'P':
    case 'Q':case 'R':case 'S':case 'T':case 'U':case 'V':case 'W':case 'X':
    case 'Y':case 'Z':
      if(!Key[kShift].was_pressed || !Key[kShift].was_held)
        mapped_key = key + 32; break;
    case '1':
      if(Key[kShift].was_pressed || Key[kShift].was_held)
        mapped_key = '!'; break;
    case '2':
      if(Key[kShift].was_pressed || Key[kShift].was_held)
        mapped_key = '@'; break;
    case '3':
      if(Key[kShift].was_pressed || Key[kShift].was_held)
        mapped_key = '#'; break;
    case '4':
      if(Key[kShift].was_pressed || Key[kShift].was_held)
        mapped_key = '$'; break;
    case '5':
      if(Key[kShift].was_pressed || Key[kShift].was_held)
        mapped_key = '%'; break;
    case '6':
      if(Key[kShift].was_pressed || Key[kShift].was_held)
        mapped_key = '^'; break;
    case '7':
      if(Key[kShift].was_pressed || Key[kShift].was_held)
        mapped_key = '&'; break;
    case '8':
      if(Key[kShift].was_pressed || Key[kShift].was_held)
        mapped_key = '*'; break;
    case '9':
      if(Key[kShift].was_pressed || Key[kShift].was_held)
        mapped_key = '('; break;
    case '0':
      if(Key[kShift].was_pressed || Key[kShift].was_held)
        mapped_key = ')'; break;
    case VK_ESCAPE:  mapped_key = kEscape; break;
    case VK_UP:      mapped_key = kUp; break;
    case VK_DOWN:    mapped_key = kDown; break;
    case VK_RIGHT:   mapped_key = kRight; break;
    case VK_LEFT:    mapped_key = kLeft; break;
    case VK_TAB:     mapped_key = kTab; break;
    case VK_SHIFT:   mapped_key = kShift; break;
    case VK_CONTROL: mapped_key = kCtrl; break;
    case VK_INSERT:  mapped_key = kInsert; break;
    case VK_DELETE:  mapped_key = kDelete; break;
    case VK_HOME:    mapped_key = kHome; break;
    case VK_END:     mapped_key = kEnd; break;
    case VK_PRIOR:   mapped_key = kPageUp; break;
    case VK_NEXT:    mapped_key = kPageDown; break;
    case VK_CAPITAL: mapped_key = kCapslock; break;
    case VK_LMENU:   mapped_key = kLMenu; break;
    case VK_RMENU:   mapped_key = kRMenu; break;
    case VK_BACK:    mapped_key = kBackspace; break;
    case VK_RETURN:  mapped_key = kEnter; break;
    case VK_PAUSE:   mapped_key = kPauseBreak; break;
    case VK_SCROLL:  mapped_key = kScrollLock; break;
    case VK_F1:      mapped_key = kF1; break;
    case VK_F2:      mapped_key = kF2; break;
    case VK_F3:      mapped_key = kF3; break;
    case VK_F4:      mapped_key = kF4; break;
    case VK_F5:      mapped_key = kF5; break;
    case VK_F6:      mapped_key = kF6; break;
    case VK_F7:      mapped_key = kF7; break;
    case VK_F8:      mapped_key = kF8; break;
    case VK_F9:      mapped_key = kF9; break;
    case VK_F10:     mapped_key = kF10; break;
    case VK_F11:     mapped_key = kF11; break;
    case VK_F12:     mapped_key = kF12; break;
  }
  Key[mapped_key].was_pressed  = (!was_down) & ( is_down);
  Key[mapped_key].was_held     = ( was_down) & ( is_down);
  Key[mapped_key].was_released = ( was_down) & (!is_down);
  //printf("The key is %X. Was Down: %s. Is Down: %s\n", key, was_down ? "Yes" : "No", is_down ? "Yes" : "No");
}
bool IsKeyPressed(int32_t key){return Key[key].was_pressed;}
bool IsKeyReleased(int32_t key){return Key[key].was_released;}
#endif
