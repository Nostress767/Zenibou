#ifndef _ZENIBOU_ZENIBOU_H_
#define _ZENIBOU_ZENIBOU_H_

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

#if !defined(PLATFORM_WEB) && defined(_WIN32)
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#endif
#include <time.h>
#include <stdint.h>

void InitializeClock(void);
void Tick(void);

struct Clock{
  double last_second_elapsed_time, last_frame_elapsed_time, total_elapsed_time;
  uint64_t frame;
  int32_t frames_last_second;
  clock_t time1, time2;};

struct Clock Clock;

void InitializeClock(void){
  Clock.last_second_elapsed_time = 0;
  Clock.last_frame_elapsed_time = 0;
  Clock.total_elapsed_time = 0;
  Clock.frame = 0;
  Clock.frames_last_second = 0;
  Clock.time1 = clock();
  Clock.time2 = clock();}

void Tick(void){
  Clock.time2 = clock();
  Clock.last_frame_elapsed_time = ((double)(Clock.time2 - Clock.time1)) / CLOCKS_PER_SEC;
  Clock.time1 = Clock.time2;
  Clock.last_second_elapsed_time += Clock.last_frame_elapsed_time;
  Clock.total_elapsed_time += Clock.last_frame_elapsed_time;
  Clock.frame++;
  if(Clock.last_second_elapsed_time > 1.){
    Clock.frames_last_second = (int32_t) Clock.frame;
    Clock.last_second_elapsed_time = 0.;
    Clock.frame = 0;}}
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

struct Mouse Mouse;

struct Key Key[512] = {0};
#include <stdint.h>
#include <stdbool.h>

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
  #define UNICODE
  #define _CRT_SECURE_NO_WARNINGS
  #include <windows.h>
  #include <windowsx.h>
  //typedef void (WINAPI *PGNSI)(DPI_AWARENESS_CONTEXT);
  LRESULT CALLBACK WindowProcedure(HWND window, UINT message, WPARAM w_param, LPARAM l_param);
#endif

struct Window{
  // TODO: maybe remove these global variables? Maybe not also? IDK, whatever is easier
  int32_t width, height;
  int32_t current_pos_x, current_pos_y;
  void* bitmap_memory;
  bool is_running;
  bool is_focused;
  #ifdef RAYLIB
    Image bitmap_info;
    Texture2D bitmap_device_context;
    Vector2 origin;
    Rectangle screen;
  #elif _WIN32
    BITMAPINFO bitmap_info;
    HDC bitmap_device_context;
    MSG msg;
    HWND handle;
  #endif
};

void BeginFrame(void);
void EndFrame(void);
void D(int32_t x, int32_t y, uint32_t color);
void C(uint32_t color);
int32_t StartEngine(int32_t size_x, int32_t size_y, const char* name);
int32_t SetWindowSizes(int32_t size_x, int32_t size_y);
void UpdateKeyState(uint32_t key, uint32_t bitfield);

struct Window Window;

int32_t SetWindowSizes(int32_t size_x, int32_t size_y){
#ifdef RAYLIB
  UnloadTexture(Window.bitmap_device_context);
  UnloadImage(Window.bitmap_info);
  MemFree(Window.bitmap_memory);
  Window.bitmap_memory = MemAlloc(size_x * size_y * 4);
  Window.bitmap_info = GenImageColor(size_x,size_y,BLACK);
  Window.bitmap_device_context = LoadTextureFromImage(Window.bitmap_info);
  Window.width = size_x;
  Window.height = size_y;
  // NOTE: another rectangle (source and dest) could be used for scaling the texture
  Window.screen = (Rectangle){0.f, 0.f, (float) Window.width, (float) Window.height};
  int monitor = GetCurrentMonitor();
  Window.current_pos_x = (GetMonitorWidth(monitor) / 2) - (size_x / 2);
  Window.current_pos_y = (GetMonitorHeight(monitor) / 2) - (size_y / 2);
  SetWindowSize(size_x,size_y);
  SetWindowPosition(Window.current_pos_x, Window.current_pos_y);
#else
  VirtualFree(Window.bitmap_memory, 0, MEM_RELEASE);
  Window.bitmap_memory = VirtualAlloc(0,size_x * size_y * 4,MEM_RESERVE|MEM_COMMIT,PAGE_READWRITE);

  ReleaseDC(Window.handle, Window.bitmap_device_context);
  Window.bitmap_info = (BITMAPINFO){ .bmiHeader = {.biSize = sizeof(Window.bitmap_info.bmiHeader), .biWidth = size_x,
                                     .biHeight = size_y, .biPlanes = 1, .biBitCount = 32, .biCompression = BI_RGB}};
  Window.bitmap_device_context = GetDC(Window.handle);
  
  Window.current_pos_x = (GetSystemMetrics(SM_CXSCREEN) / 2) - (size_x / 2);
  Window.current_pos_y = (GetSystemMetrics(SM_CYSCREEN) / 2) - (size_y / 2);
  MoveWindow(Window.handle, Window.current_pos_x, Window.current_pos_y, size_x, size_y, true);
#endif
  return 0;}

void BeginFrame(void){
#ifdef RAYLIB
  int32_t key;
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
    DispatchMessage(&Window.msg);}
#endif
}

void EndFrame(void){
#ifdef RAYLIB
  UpdateTexture(Window.bitmap_device_context, Window.bitmap_memory);
  BeginDrawing();
  DrawTexturePro(Window.bitmap_device_context, Window.screen, Window.screen, Window.origin, 0.f, WHITE);
  EndDrawing();
#ifndef PLATFORM_WEB
  if(!Window.is_running)
    CloseWindow();
  Window.is_running = !WindowShouldClose();
  if(!Window.is_running)
    CloseWindow();
#endif
#else
  StretchDIBits(Window.bitmap_device_context,
                0,0,
                Window.width,Window.height,
                0,0,
                Window.width,Window.height,
                Window.bitmap_memory,
                &Window.bitmap_info,
                DIB_RGB_COLORS,
                SRCCOPY);
#endif
  for(int32_t i = 0; i < 512; i++){
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

void D(int32_t x, int32_t y, uint32_t color){
  if(x < 0 || y < 0 || x >= Window.width || y >= Window.height)
    return;
  uint32_t* pixel = (uint32_t *)Window.bitmap_memory;
#ifdef RAYLIB
  // Invert y, because of OpenGL reasons
  pixel += (Window.height - y - 1) * Window.width + x;
  // Gets optimized to a single bswap instruction, great!
  *pixel = (color >> 24) | ((color >> 8) & 0xFF00) | ((color << 8) & 0xFF0000) | (color << 24);
#else
  pixel += y * Window.width + x;
  // On zenibou its ARGB
  // But we default RGBA, so roll over byte
  *pixel = (color << 24) | (color >> 8);
#endif
}

void C(uint32_t color){
  uint32_t *pixel = (uint32_t *)Window.bitmap_memory;
  for(int i = 0; i < Window.width * Window.height; ++i)
  #ifdef RAYLIB
    *pixel++ = (color >> 24) | ((color >> 8) & 0xFF00) | ((color << 8) & 0xFF0000) | (color << 24);
  #else
    *pixel++ = (color << 24) | (color >> 8);
  #endif
}

//#include <stdio.h>
void UpdateKeyState(uint32_t key, uint32_t bitfield){
#ifdef RAYLIB
  (void)bitfield;
// Snippets from raylib. NOTE: do I need those keys?
//    KEY_NULL            = 0,        // Key: NULL, used for no key pressed
//    KEY_KB_MENU         = 348,      // Key: KB menu
  Key[key].is_pressed  = IsKeyPressed(key);
  Key[key].is_released = IsKeyReleased(key);
}
#else
  uint32_t mapped_key = key;
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
      Window.width = GET_X_LPARAM(l_param);
      Window.height = GET_Y_LPARAM(l_param);
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

int32_t StartEngine(int32_t size_x, int32_t size_y, const char* name){
#ifdef RAYLIB
  InitWindow(size_x,size_y,name);
  HideCursor();
  SetWindowState(FLAG_WINDOW_UNDECORATED);
  Window.bitmap_memory = MemAlloc(size_x * size_y * 4);
  Window.bitmap_info = GenImageColor(size_x,size_y,BLACK);
  Window.bitmap_device_context = LoadTextureFromImage(Window.bitmap_info);
  Window.width = size_x;
  Window.height = size_y;
  Window.is_running = true;
  Window.origin = (Vector2){0};
  Window.screen = (Rectangle){0.f, 0.f, (float) Window.width, (float) Window.height};
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
  ShowCursor(false);

  RegisterClass(&window_class);
  
  Window.current_pos_x = (GetSystemMetrics(SM_CXSCREEN) / 2) - (size_x / 2);
  Window.current_pos_y = (GetSystemMetrics(SM_CYSCREEN) / 2) - (size_y / 2); 

  Window.handle = CreateWindowEx(//WS_EX_OVERLAPPEDWINDOW, //(https://docs.microsoft.com/en-us/windows/win32/winmsg/extended-window-styles)
                                 0, 
                                 class_name, title,
                                 WS_POPUP|WS_VISIBLE,
                                 //|WS_VISIBLE,
                                 Window.current_pos_x, // startx
                                 Window.current_pos_y, // starty
                                 size_x, // sizex
                                 size_y, // sizey
                                 0, 0, instance, 0);

  Window.is_running = true;
  InitializeClock();
  
  Window.bitmap_memory = VirtualAlloc(0,size_x * size_y * 4,MEM_RESERVE|MEM_COMMIT,PAGE_READWRITE);
  Window.bitmap_info = (BITMAPINFO){ .bmiHeader = {.biSize = sizeof(Window.bitmap_info.bmiHeader), .biWidth = size_x,
                                     .biHeight = size_y, .biPlanes = 1, .biBitCount = 32, .biCompression = BI_RGB}};
  Window.bitmap_device_context = GetDC(Window.handle);
  
  return 0;
#endif
}

// NOTE: this was used for checking high-DPI settings
////#pragma comment(lib, "shcore.lib")
////#include <shellscalingapi.h>
#endif
