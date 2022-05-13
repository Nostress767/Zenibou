﻿#ifndef _ZENIBOU_ZENIBOU_H_
#define _ZENIBOU_ZENIBOU_H_

#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#if !defined(PLATFORM_WEB) && defined(_WIN32)
#define UNICODE
#define STB_IMAGE_IMPLEMENTATION
#include "external/stb_image.h"
#define MA_NO_ENCODING
#define MINIAUDIO_IMPLEMENTATION
#include "external/miniaudio.h"
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#endif
#ifdef RAYLIB
  #include "raylib.h"
#if !defined(PLATFORM_WEB) && defined(_WIN32)
  #pragma comment(lib, "winmm.lib")
  #pragma comment(lib, "kernel32.lib")
  #pragma comment(lib, "shell32.lib")
#endif
// TODO: investigate whatever this is: (https://docs.microsoft.com/en-us/windows/win32/gdi/alpha-blending) (https://docs.microsoft.com/en-us/windows/win32/gdi/alpha-blending-a-bitmap)
  // TODO: investigate multithreading in C for message loop (https://docs.microsoft.com/en-us/cpp/parallel/multithreading-with-c-and-win32?view=msvc-170)
  // TODO: investigate tcc(tiny c compiler)'s compiling capabilities and figure out if could compile out of the box (downloading), copy from raylib command
#else
  #define DPI_AWARENESS_CONTEXT_SYSTEM_AWARE ((DPI_AWARENESS_CONTEXT)-2)
  #define WIN32_LEAN_AND_MEAN
  #define _CRT_SECURE_NO_WARNINGS
  #include <windows.h>
  #include <windowsx.h>
  #undef PlaySound
  //typedef void (WINAPI *PGNSI)(DPI_AWARENESS_CONTEXT);
  LRESULT CALLBACK WindowProcedure(HWND window, UINT message, WPARAM w_param, LPARAM l_param);
#endif
// TODO: clean up this file

#define f32 float
#define f64 double
#define i8 int8_t
#define i16 int16_t
#define i32 int32_t
#define i64 int64_t
#define u8 uint8_t
#define u16 uint16_t
#define u32 uint32_t
#define u64 uint64_t

#define SoundStart(sound) ma_sound_start(&sound)
#define SoundStop(sound) ma_sound_stop(&sound)
#define SoundSeek(sound, frame) ma_sound_start(&sound, frame)

typedef ma_sound Sound;

//
// BEGIN Circular Dynamic Linked List with Sentinel API
//

// Use this to create a list.
#define CreateList(type) AllocList(sizeof(type))

typedef struct Node{
	void* data;
	struct Node* prev, *next;
} Node;

typedef struct List{
	struct Node* sentinel;
	size_t sz;
	int32_t n;
} List;

typedef struct ListIterator{
	Node* cur;
	List* list;
} ListIterator;

typedef ListIterator list_iterator;

// Memory manipulation.
List AllocList(size_t sz);
void FreeList(List* self);

// Mutators.
void ListPushBack(List* self, void* element);
void ListPushFront(List* self, void* element);
bool ListPopBack(List* self);
bool ListPopFront(List* self);

// Getters.
void* ListBack(List l);
void* ListFront(List l);
bool ListEmpty(List l);
int32_t ListSize(List l);

// Create ListIterator.
ListIterator ListIterateFromFront(List* self);
ListIterator ListIterateFromBack(List* self);

// Insert based on iterator.
void ListInsertPrev(ListIterator* self, void* element);
void ListInsertNext(ListIterator* self, void* element);

// Remove based on iterator.
bool ListRemovePrev(ListIterator* self);
bool ListRemoveNext(ListIterator* self);
ListIterator ListRemove(ListIterator* self);

// Get element from iterator.
void* ListPrevElement(ListIterator it);
void* ListNextElement(ListIterator it);
void* ListElement(ListIterator it);

// Move through iterator.
ListIterator ListPrev(ListIterator it);
ListIterator ListNext(ListIterator it);
bool ListEnd(ListIterator it);

//
// END Linked List API
//

#ifndef RAYLIB
#define IncludeMedia(x,type) extern unsigned char binary_##x##_##type##_start[];extern unsigned char binary_##x##_##type##_end[];
#define MediaStart(x,type) binary_##x##_##type##_start
#define MediaEnd(x,type) binary_##x##_##type##_end
#else
#define IncludeMedia(x,type) extern unsigned char _binary_##x##_##type##_start[];extern unsigned char _binary_##x##_##type##_end[];
#define MediaStart(x,type) _binary_##x##_##type##_start
#define MediaEnd(x,type) _binary_##x##_##type##_end
#endif
#define MediaSize(x,type) MediaEnd(x,type)-MediaStart(x,type)

// PNG-type sprite
typedef struct Sprite{
  i32 x, y;
  i32 width, height, channels;
  u8** data;
} Sprite;

#ifndef RAYLIB
void InitializeAudio(void);
void PlaySound(const char* name);
void DeclareSound(const u8 start[], i32 len, const char* name);
Sound AllocSound(const u8 start[], i32 len, bool loops);
#endif
void InitializeClock(void);
void Tick(void);
void BeginFrame(void);
void EndFrame(void);
void D(i32 x, i32 y, u32 color);
void C(u32 color);
i32 StartEngine(i32 size_x, i32 size_y, const char* name);
i32 SetWindowSizes(i32 size_x, i32 size_y);
void UpdateKeyState(u32 key, u32 bitfield);
void DrawSprite(Sprite* spr);
void FreeSprite(Sprite* spr);
Sprite AllocSprite(const u8 start[], i32 len, i32 x, i32 y);
void ToggleFullscreen(void);

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

struct Mouse{
  i16 x, y;
  bool left_pressed, middle_pressed, right_pressed;
  bool left_held, middle_held, right_held;
  bool left_released, middle_released, right_released;
  bool is_focused;
} Mouse;

struct Key{
  bool is_pressed, is_held, is_released;
} Key[512] = {0};

struct Clock{
  f64 last_second_elapsed_time, last_frame_elapsed_time, total_elapsed_time;
  u64 frame;
  i32 frames_last_second;
  clock_t time1, time2;
} Clock;

struct Window{
  // NOTE: maybe remove these global variables? Maybe not also? IDK, whatever is easier
  i32 width, height;
  i32 starting_width, starting_height;
  i32 offset_x, offset_y;
  i32 current_pos_x, current_pos_y;
  f64 aspect_ratio;
  void* bitmap_memory;
  bool is_running;
  bool is_focused;
  bool is_fullscreen;
  #ifdef RAYLIB
    Image bitmap_info;
    Texture2D bitmap_device_context;
    Vector2 origin;
    Rectangle screen;
    Rectangle starting_screen;
  #elif _WIN32
    ma_engine audio_engine;
    ma_decoder_config decoder_config;
    List audio_decoders;
    BITMAPINFO bitmap_info;
    HDC bitmap_device_context;
    MSG msg;
    HWND handle;
  #endif
} Window;

void InitializeClock(void){
  Clock.last_second_elapsed_time = 0;
  Clock.last_frame_elapsed_time = 0;
  Clock.total_elapsed_time = 0;
  Clock.frame = 0;
  Clock.frames_last_second = 0;
  Clock.time1 = clock();
  Clock.time2 = clock();
}

void Tick(void){
  Clock.time2 = clock();
  Clock.last_frame_elapsed_time = ((f64)(Clock.time2 - Clock.time1)) / CLOCKS_PER_SEC;
  Clock.time1 = Clock.time2;
  Clock.last_second_elapsed_time += Clock.last_frame_elapsed_time;
  Clock.total_elapsed_time += Clock.last_frame_elapsed_time;
  Clock.frame++;
  if(Clock.last_second_elapsed_time > 1.){
    Clock.frames_last_second = (i32) Clock.frame;
    Clock.last_second_elapsed_time = 0.;
    Clock.frame = 0;
  }
}

void BeginFrame(void){
#ifdef RAYLIB
  i32 key;
  while((key = GetKeyPressed()) != 0)
    UpdateKeyState(key, 0);

  // TODO: maybe make a UpdateMouseState for cleaner code
  Mouse.left_pressed = IsMouseButtonPressed(kMouseLeft);
  Mouse.middle_pressed = IsMouseButtonPressed(kMouseMiddle);
  Mouse.right_pressed = IsMouseButtonPressed(kMouseRight);

  Mouse.left_held = IsMouseButtonDown(kMouseLeft);
  Mouse.middle_held = IsMouseButtonDown(kMouseMiddle);
  Mouse.right_held = IsMouseButtonDown(kMouseRight);

  Mouse.left_released = IsMouseButtonReleased(kMouseLeft);
  Mouse.middle_released = IsMouseButtonReleased(kMouseMiddle);
  Mouse.right_released = IsMouseButtonReleased(kMouseRight);
#else
  while(PeekMessage(&Window.msg, NULL, 0, 0, PM_REMOVE)){
    TranslateMessage(&Window.msg);
    DispatchMessage(&Window.msg);
  }
#endif
}

void EndFrame(void){
#ifdef RAYLIB
  Window.screen = (Rectangle){0.f, 0.f, (float) GetScreenWidth(), (float) GetScreenHeight()};
  UpdateTexture(Window.bitmap_device_context, Window.bitmap_memory);
  BeginDrawing();
  DrawTexturePro(Window.bitmap_device_context, Window.starting_screen, Window.screen, Window.origin, 0.f, WHITE);
  EndDrawing();
#ifndef PLATFORM_WEB
  if(!Window.is_running)
    CloseWindow();
  Window.is_running = !WindowShouldClose();
  if(!Window.is_running)
    CloseWindow();
#endif
#else
  //printf("Crash, why? %d %d\n", Window.offset_x, Window.offset_y);
  StretchDIBits(Window.bitmap_device_context,
                Window.offset_x, Window.offset_y,
                Window.width, Window.height,
                0,0,
                Window.starting_width, Window.starting_height,
                Window.bitmap_memory,
                &Window.bitmap_info,
                DIB_RGB_COLORS,
                SRCCOPY);//SRCCOPY);
#endif
  for(i32 i = 0; i < 512; i++){
    if(Key[i].is_pressed){
      Key[i].is_pressed = false;
      Key[i].is_held = true;
      Key[i].is_released = false;}
    else if(Key[i].is_held){
#ifdef RAYLIB
      Key[i].is_held = IsKeyDown(i);
      if(!Key[i].is_held)
        Key[i].is_released = true;
#endif
      }
    else if(Key[i].is_released){
      Key[i].is_pressed = false;
      Key[i].is_held = false;
      Key[i].is_released = false;}}
  Tick();
}

void D(i32 x, i32 y, u32 color){
#ifdef RAYLIB
  if(x < 0 || y < 0 || x >= Window.width || y >= Window.height)
#else
  if(x < 0 || y < 0 || x >= Window.starting_width || y >= Window.starting_height)
#endif
    return;
  u32* pixel = (u32*)Window.bitmap_memory;
#ifdef RAYLIB
  // Invert y, because of OpenGL reasons
  pixel += (Window.height - y - 1) * Window.width + x;
  // Gets optimized to a single bswap instruction, great!
  *pixel = (color >> 24) | ((color >> 8) & 0xFF00) | ((color << 8) & 0xFF0000) | (color << 24);
#else
  pixel += y * Window.starting_width + x;
  // On windows its ARGB
  // But we default RGBA, so roll over byte
  *pixel = (color << 24) | (color >> 8);
#endif
}

void C(u32 color){
#ifdef RAYLIB
  for(i32 i = 0; i < Window.width; ++i)
    for(i32 j = 0; j < Window.height; ++j)
#else
  for(i32 i = 0; i < Window.starting_width; ++i)
    for(i32 j = 0; j < Window.starting_height; ++j)
#endif
      D(i, j, color);
}

i32 StartEngine(i32 size_x, i32 size_y, const char* name){
#ifdef RAYLIB
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(size_x,size_y,name);
  //HideCursor();
  //SetWindowState(FLAG_WINDOW_UNDECORATED);
  Window.bitmap_memory = MemAlloc(size_x * size_y * 4);
  Window.bitmap_info = GenImageColor(size_x,size_y,BLACK);
  Window.bitmap_device_context = LoadTextureFromImage(Window.bitmap_info);
  Window.width = size_x;
  Window.height = size_y;
  Window.is_running = true;
  Window.origin = (Vector2){0};
  Window.screen = (Rectangle){0.f, 0.f, (float) Window.width, (float) Window.height};
  Window.starting_screen = (Rectangle){0.f, 0.f, (float) Window.width, (float) Window.height};
  InitializeClock();
  return 0;
#else  
  wchar_t title[256];
  MultiByteToWideChar(CP_UTF8,0,name,-1,title,MultiByteToWideChar(CP_UTF8,0,name,-1,NULL,0));

  SetProcessDPIAware();
  //PGNSI pGNSI = (PGNSI)GetProcAddress(GetModuleHandle(TEXT("user32.dll")), "SetProcessDpiAwarenessContext");
  //if(pGNSI != NULL)
  //  pGNSI(DPI_AWARENESS_CONTEXT_SYSTEM_AWARE);
  //SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_SYSTEM_AWARE);
  
  HINSTANCE instance = GetModuleHandle(0);

  const wchar_t class_name[] = L"Zenibou";
  WNDCLASSW window_class = {.lpfnWndProc = WindowProcedure,.hInstance = instance,.style = CS_HREDRAW | CS_VREDRAW,
                            .lpszClassName = class_name,.hCursor = LoadCursor(0, IDC_ARROW),};
  //ShowCursor(false);

  RegisterClass(&window_class);
  
  Window.current_pos_x = (GetSystemMetrics(SM_CXSCREEN) / 2) - (size_x / 2);
  Window.current_pos_y = (GetSystemMetrics(SM_CYSCREEN) / 2) - (size_y / 2); 

  RECT rect = { 0, 0, size_x, size_y };
  AdjustWindowRectEx(&rect, WS_CAPTION | WS_VISIBLE | WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX, false, 0);

  Window.offset_x = 0;
  Window.offset_y = 0;
  Window.width = size_x;
  Window.height = size_y;
  Window.aspect_ratio = (f64)size_x / size_y;
  Window.starting_width = size_x;
  Window.starting_height = size_y;

  Window.handle = CreateWindowEx(//WS_EX_OVERLAPPEDWINDOW, //(https://docs.microsoft.com/en-us/windows/win32/winmsg/extended-window-styles)
                                 0, 
                                 class_name, title,
                                 WS_CAPTION | WS_VISIBLE | WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX,
                                 //WS_POPUP|WS_VISIBLE,
                                 //|WS_VISIBLE,
                                 Window.current_pos_x, // start_x
                                 Window.current_pos_y, // start_y
                                 rect.right - rect.left, // size_x
                                 rect.bottom - rect.top, // size_y
                                 0, 0, instance, 0);

  Window.is_running = true;
  InitializeClock();
  InitializeAudio();
  
  Window.is_fullscreen = false;
  Window.bitmap_memory = VirtualAlloc(0,Window.width * Window.height * 4,MEM_RESERVE|MEM_COMMIT,PAGE_READWRITE);
  Window.bitmap_info = (BITMAPINFO){ .bmiHeader = {.biSize = sizeof(Window.bitmap_info.bmiHeader), .biWidth = Window.width,
                                     .biHeight = Window.height, .biPlanes = 1, .biBitCount = 32, .biCompression = BI_RGB}};
  Window.bitmap_device_context = GetDC(Window.handle);
  
  return 0;
#endif
}

#ifndef RAYLIB
// TODO: fix weird behaviour here (or don't use this function at all)
i32 SetWindowSize(i32 size_x, i32 size_y){
  RECT rect = { 0, 0, size_x, size_y };
  if(size_x > GetSystemMetrics(SM_CXSCREEN) || size_y > GetSystemMetrics(SM_CYSCREEN))
    return 0;
  else if(size_x == GetSystemMetrics(SM_CXSCREEN) && size_y == GetSystemMetrics(SM_CYSCREEN)){
    SetWindowLongPtr(Window.handle, GWL_STYLE, WS_POPUP | WS_VISIBLE);
    AdjustWindowRectEx(&rect, WS_POPUP | WS_VISIBLE, false, 0);
  }
  else{
    SetWindowLongPtr(Window.handle, GWL_STYLE, WS_CAPTION | WS_VISIBLE | WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX);
    AdjustWindowRectEx(&rect, WS_CAPTION | WS_VISIBLE | WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX, false, 0);
  }
  Window.current_pos_x = (GetSystemMetrics(SM_CXSCREEN) / 2) - (size_x / 2);
  Window.current_pos_y = (GetSystemMetrics(SM_CYSCREEN) / 2) - (size_y / 2); 
  MoveWindow(Window.handle, Window.current_pos_x, Window.current_pos_y, rect.right - rect.left, rect.bottom - rect.top, true);
  return 0;
}
#endif

void UpdateKeyState(u32 key, u32 bitfield){
#ifdef RAYLIB
  (void)bitfield;
// Snippets from raylib. NOTE: do I need those keys?
//    KEY_NULL            = 0,        // Key: NULL, used for no key pressed
//    KEY_KB_MENU         = 348,      // Key: KB menu
  Key[key].is_pressed  = IsKeyPressed(key);
  Key[key].is_released = IsKeyReleased(key);
}
#else
  u32 mapped_key = key;
  bool was_down = bitfield >> 30 & 1;
  bool is_down = bitfield >> 31 ^ 1;
  //printf("key: %d %X\n", mapped_key, mapped_key);
  switch(key){
    // NOTE: if there is any need to differentiate 'A' from 'a' (or any other shift key) come back to this, but beware of compatibility with raylib
    case VK_SPACE:      mapped_key = kSpace;        break;
    case VK_OEM_7:      mapped_key = kQuotes;       break;
    case VK_OEM_COMMA:  mapped_key = kComma;        break;
    case VK_OEM_MINUS:  mapped_key = kMinus;        break;
    case VK_OEM_PERIOD: mapped_key = kPeriod;       break;
    case VK_OEM_2:      mapped_key = kFrontSlash;   break;
    case VK_OEM_1:      mapped_key = kSemicolon;    break;
    case VK_OEM_PLUS:   mapped_key = kEqual;        break;
    case VK_OEM_4:      mapped_key = kLeftBracket;  break;
    case VK_OEM_5:      mapped_key = kBackSlash;    break;
    case VK_OEM_6:      mapped_key = kRightBracket; break;
    case VK_OEM_3:      mapped_key = kBacktick;     break;
    case VK_ESCAPE:     mapped_key = kEscape;       break;
    case VK_RETURN:     mapped_key = kEnter;        break;
    case VK_TAB:        mapped_key = kTab;          break;
    case VK_BACK:       mapped_key = kBackspace;    break;
    case VK_INSERT:     mapped_key = kInsert;       break;
    case VK_DELETE:     mapped_key = kDelete;       break;
    case VK_RIGHT:      mapped_key = kRight;        break;
    case VK_LEFT:       mapped_key = kLeft;         break;
    case VK_DOWN:       mapped_key = kDown;         break;
    case VK_UP:         mapped_key = kUp;           break;
    case VK_PRIOR:      mapped_key = kPageUp;       break;
    case VK_NEXT:       mapped_key = kPageDown;     break;
    case VK_HOME:       mapped_key = kHome;         break;
    case VK_END:        mapped_key = kEnd;          break;
    case VK_CAPITAL:    mapped_key = kCapslock;     break;
    case VK_SCROLL:     mapped_key = kScrollLock;   break;
    case VK_NUMLOCK:    mapped_key = kNumLock;      break;
    case VK_SNAPSHOT:   mapped_key = kPrintScreen;  break;
    case VK_PAUSE:      mapped_key = kPauseBreak;   break;
    case VK_F1:         mapped_key = kF1;           break;
    case VK_F2:         mapped_key = kF2;           break;
    case VK_F3:         mapped_key = kF3;           break;
    case VK_F4:         mapped_key = kF4;           break;
    case VK_F5:         mapped_key = kF5;           break;
    case VK_F6:         mapped_key = kF6;           break;
    case VK_F7:         mapped_key = kF7;           break;
    case VK_F8:         mapped_key = kF8;           break;
    case VK_F9:         mapped_key = kF9;           break;
    case VK_F10:        mapped_key = kF10;          break;
    case VK_F11:        mapped_key = kF11;          break;
    case VK_F12:        mapped_key = kF12;          break;
    case VK_NUMPAD0:    mapped_key = kNumpad0;      break;
    case VK_NUMPAD1:    mapped_key = kNumpad1;      break;
    case VK_NUMPAD2:    mapped_key = kNumpad2;      break;
    case VK_NUMPAD3:    mapped_key = kNumpad3;      break;
    case VK_NUMPAD4:    mapped_key = kNumpad4;      break;
    case VK_NUMPAD5:    mapped_key = kNumpad5;      break;
    case VK_NUMPAD6:    mapped_key = kNumpad6;      break;
    case VK_NUMPAD7:    mapped_key = kNumpad7;      break;
    case VK_NUMPAD8:    mapped_key = kNumpad8;      break;
    case VK_NUMPAD9:    mapped_key = kNumpad9;      break;
    case VK_DECIMAL:    mapped_key = kDecimal;      break;
    case VK_DIVIDE:     mapped_key = kDivide;       break;
    case VK_MULTIPLY:   mapped_key = kMultiply;     break;
    case VK_SUBTRACT:   mapped_key = kSubtract;     break;
    case VK_ADD:        mapped_key = kAdd;          break;
    // TODO: fix special VK_KEYS with left right variants
    case VK_SHIFT:
    case VK_LSHIFT:     mapped_key = kLeftShift;    break;
    case VK_LCONTROL:   mapped_key = kLeftCtrl;     break;
    case VK_LMENU:      mapped_key = kLeftAlt;      break;
    case VK_LWIN:       mapped_key = kLeftSuper;    break;
    case VK_RSHIFT:     mapped_key = kRightShift;   break;
    case VK_RCONTROL:   mapped_key = kRightCtrl;    break;
    case VK_RMENU:      mapped_key = kRightAlt;     break;
    case VK_RWIN:       mapped_key = kRightSuper;   break;
  }
  //printf("key: %d %X\n", mapped_key, mapped_key);
  Key[mapped_key].is_pressed  = (!was_down) & ( is_down);
  Key[mapped_key].is_held     = ( was_down) & ( is_down);
  Key[mapped_key].is_released = ( was_down) & (!is_down);
}
LRESULT CALLBACK WindowProcedure(HWND window, UINT message, WPARAM w_param, LPARAM l_param){
  switch(message){
    case WM_MOUSEMOVE:{
      Mouse.is_focused = true;
      Mouse.x = GET_X_LPARAM(l_param);
      Mouse.y = GET_Y_LPARAM(l_param);
    } return 0;
    case WM_MOUSELEAVE:{
      Mouse.is_focused = false;
    } return 0;
    case WM_SIZE:{
      HBRUSH temp = CreateSolidBrush(0);
      SelectObject(Window.bitmap_device_context, temp);
      Rectangle(Window.bitmap_device_context, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
      //Window.width = GET_X_LPARAM(l_param);
      Window.height = GET_Y_LPARAM(l_param);
      Window.width = (i32)floor(Window.height * Window.aspect_ratio);
      Window.offset_x = (GET_X_LPARAM(l_param) - Window.width) / 2;
      DeleteObject(temp);
    } return 0;
    case WM_MOVE:{
      Window.current_pos_x = (i32)(i16) LOWORD(l_param);
      Window.current_pos_y = (i32)(i16) HIWORD(l_param);
    } return 0;
    case WM_SETFOCUS:{
      Window.is_focused = true;
    } return 0;
    case WM_KILLFOCUS:{
      Window.is_focused = false;
    } return 0;
    case WM_LBUTTONDOWN:{
      Mouse.left_pressed = true;
    } return 0;
    case WM_LBUTTONUP:{
      Mouse.left_pressed = false;
    } return 0;
    case WM_MBUTTONDOWN:{
      Mouse.middle_pressed = true;
    } return 0;
    case WM_MBUTTONUP:{
      Mouse.middle_pressed = false;
    } return 0;
    case WM_RBUTTONDOWN:{
      Mouse.right_pressed = true;
    } return 0;
    case WM_RBUTTONUP:{
      Mouse.right_pressed = false;
    } return 0;
    case WM_KEYUP:
    case WM_SYSKEYDOWN:
    case WM_SYSKEYUP:
    case WM_KEYDOWN:{
      UpdateKeyState(w_param, l_param);
    } return 0;

    case WM_CLOSE:{
      Window.is_running = false;
    } return 0;
    case WM_DESTROY:{
      PostQuitMessage(0);
      DestroyWindow(Window.handle);
      Window.is_running = false;
    } return 0;
  }
  return DefWindowProc(window, message, w_param, l_param);  
}
#endif

void DrawSprite(Sprite* spr){
  for(i32 i = 0; i < spr->height; i++)
    for(i32 j = 0; j < spr->width; j++)
      D(spr->x + j, spr->y + i, spr->data[i][j*4] << 24 | spr->data[i][j*4+1] << 16 | (spr->data[i][j*4+2]) << 8 | spr->data[i][j*4+3]);
}

void FreeSprite(Sprite* spr){
  Sprite tmp = {0};
  for(i32 i = 0; i < spr->height; i++)
    free(spr->data[i]);
  free(spr->data);
  *spr = tmp;
}

#ifndef RAYLIB
void ToggleFullscreen(void){
  if(Window.is_fullscreen){
    SetWindowLongPtr(Window.handle, GWL_STYLE, WS_CAPTION | WS_VISIBLE | WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX);
    Window.width = Window.starting_width;
    Window.height = Window.starting_height;
    Window.is_fullscreen = false;
    RECT rect = { 0, 0, Window.width, Window.height };
    AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW | WS_VISIBLE, false, 0);  
    MoveWindow(Window.handle,
        (GetSystemMetrics(SM_CXSCREEN) / 2) - (Window.width / 2), (GetSystemMetrics(SM_CYSCREEN) / 2) - (Window.height / 2),
        rect.right - rect.left, rect.bottom - rect.top, true);
  }
  else{
    SetWindowLongPtr(Window.handle, GWL_STYLE, WS_POPUP | WS_VISIBLE);
    MoveWindow(Window.handle, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), true);
    Window.is_fullscreen = true;
  }
}
#endif

Sprite AllocSprite(const u8 start[], i32 len, i32 x, i32 y){
  Sprite spr = { x, y, };
  u8* reverse_rows = stbi_load_from_memory(start, len, &spr.width, &spr.height, &spr.channels, 4);
  // Reverse row order (from "left to right, top to bottom" to "left to right, bottom to top")
  spr.data = malloc(sizeof(u8*) * spr.height);
  for(i32 i = 0; i < spr.height; i++){
    spr.data[i] = malloc(4 * spr.width);
    memcpy(spr.data[i], reverse_rows + (spr.height - 1 - i) * 4 * spr.width, 4 * spr.width);
  }

  free(reverse_rows);
  return spr;
}

#ifndef RAYLIB
void InitializeAudio(void){
  ma_engine_init(NULL, &Window.audio_engine);
  Window.audio_decoders = CreateList(ma_decoder);
  Window.decoder_config = ma_decoder_config_init_default();
}

void PlaySound(const char* name){
  ma_engine_play_sound(&Window.audio_engine, name, NULL);
}
void DeclareSound(const u8 start[], i32 len, const char* name){
  ma_resource_manager_register_encoded_data(ma_engine_get_resource_manager(&Window.audio_engine), name, start, len);
}
Sound AllocSound(const u8 start[], i32 len, bool loops){  
  ma_decoder decoder = { 0 };
  ListPushBack(&Window.audio_decoders, &decoder);
  ma_decoder_init_memory(start, len, &Window.decoder_config, (ma_decoder*)ListBack(Window.audio_decoders));

  ma_sound sound = { 0 };
  ma_sound_init_from_data_source(&Window.audio_engine, (ma_decoder*)ListBack(Window.audio_decoders), MA_SOUND_FLAG_DECODE, NULL, &sound);

  if(loops)
    ma_sound_set_looping(&sound, MA_TRUE);

  return sound;
}
#endif

List AllocList(size_t sz){
  List l = { malloc(sizeof(Node)), sz, 0 };
  l.sentinel->prev = l.sentinel->next = l.sentinel;
  l.sentinel->data = NULL;
  return l;
}

void FreeList(List* self){
  while(ListPopBack(self));
  free(self->sentinel);
  List temp = { 0 };
  *self = temp;
}

void ListPushBack(List* self, void* element){
  Node* new_node = malloc(sizeof(Node));
  new_node->data = malloc(self->sz);
  new_node->next = self->sentinel;
  if(ListEmpty(*self)){
    self->sentinel->next = new_node;
    new_node->prev = self->sentinel;}
  else{
    new_node->prev = self->sentinel->prev;
    self->sentinel->prev->next = new_node;}
  self->sentinel->prev = new_node;
  memmove(new_node->data, element, self->sz);
  self->n++;
}

void ListPushFront(List* self, void* element){
  Node* new_node = malloc(sizeof(Node));
  new_node->data = malloc(self->sz);
  new_node->prev = self->sentinel;
  if(ListEmpty(*self)){
    self->sentinel->prev = new_node;
    new_node->next = self->sentinel;}
  else{
    new_node->next = self->sentinel->next;
    self->sentinel->next->prev = new_node;}
  self->sentinel->next = new_node;
  memmove(new_node->data, element, self->sz);
  self->n++;
}

bool ListPopBack(List* self){
  if(ListEmpty(*self))
    return false;
  Node* old_node = self->sentinel->prev;
  self->sentinel->prev = old_node->prev;
  self->sentinel->prev->next = self->sentinel;
  free(old_node->data);
  free(old_node);
  self->n--;
  return true;
}

bool ListPopFront(List* self){
  if(ListEmpty(*self))
    return false;
  Node* old_node = self->sentinel->next;
  self->sentinel->next = old_node->next;
  self->sentinel->next->prev = self->sentinel;
  free(old_node->data);
  free(old_node);
  self->n--;
  return true;
}

void* ListBack(List l){
  if(ListEmpty(l))
    return NULL;
  return l.sentinel->prev->data;
}

void* ListFront(List l){
  if(ListEmpty(l))
    return NULL;
  return l.sentinel->next->data;
}

bool ListEmpty(List l){ return !l.n; }

int32_t ListSize(List l){ return l.n; }

ListIterator ListIterateFromFront(List* self){
  ListIterator it = { self->sentinel->next, self };
  return it;
}

ListIterator ListIterateFromBack(List* self){
  ListIterator it = { self->sentinel->prev, self };
  return it;
}

void ListInsertPrev(ListIterator* self, void* element){
  Node* new_node = malloc(sizeof(Node));
  new_node->data = malloc(self->list->sz);
  memmove(new_node->data, element, self->list->sz);
  new_node->prev = self->cur->prev;
  new_node->next = self->cur;
  new_node->prev->next = new_node;
  self->cur->prev = new_node;
  self->list->n++;
}

void ListInsertNext(ListIterator* self, void* element){
  Node* new_node = malloc(sizeof(Node));
  new_node->data = malloc(self->list->sz);
  memmove(new_node->data, element, self->list->sz);
  new_node->next = self->cur->next;
  new_node->prev = self->cur;
  new_node->next->prev = new_node;
  self->cur->next = new_node;
  self->list->n++;
}

bool ListRemovePrev(ListIterator* self){
  if(ListEmpty(*self->list))
    return false;
  Node* old_node = self->cur->prev;
  self->cur->prev = old_node->prev;
  self->cur->prev->next = self->cur;
  free(old_node->data);
  free(old_node);
  self->list->n--;
  return true;
}

bool ListRemoveNext(ListIterator* self){
  if(ListEmpty(*self->list))
    return false;
  Node* old_node = self->cur->next;
  self->cur->next = old_node->next;
  self->cur->next->prev = self->cur;
  free(old_node->data);
  free(old_node);
  self->list->n--;
  return true;
}

ListIterator ListRemove(ListIterator* self){
  if(ListEmpty(*self->list))
    return (ListIterator){ 0 };
  Node* new_node = self->cur->next;
  self->cur->prev->next = self->cur->next;
  self->cur->next->prev = self->cur->prev;
  self->list->n--;
  ListIterator new_it = { new_node, self->list };
  free(self->cur->data);
  free(self->cur);
  return new_it;
}

void* ListPrevElement(ListIterator it){
  if(it.cur->prev == it.list->sentinel)
    return it.cur->prev->prev->data;
  return it.cur->prev->data;
}

void* ListNextElement(ListIterator it){
  if(it.cur->next == it.list->sentinel)
    return it.cur->next->next->data;
  return it.cur->next->data;
}

void* ListElement(ListIterator it){
  return it.cur->data;
}

ListIterator ListPrev(ListIterator it){
  if(it.cur == it.list->sentinel)
    return it;
  it.cur = it.cur->prev;
  return it;
}

ListIterator ListNext(ListIterator it){
  if(it.cur == it.list->sentinel)
    return it;
  it.cur = it.cur->next;
  return it;
}

bool ListEnd(ListIterator it){ return (it.cur == it.list->sentinel); }

// NOTE: this was used for checking high-DPI settings
////#pragma comment(lib, "shcore.lib")
////#include <shellscalingapi.h>
#endif
