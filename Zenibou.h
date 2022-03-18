#ifndef _ZENIBOU_ZENIBOU_H_
#define _ZENIBOU_ZENIBOU_H_

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

#ifndef PLATFORM_WEB
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#endif
#include "Clock.h"
#include "Input.h"
#include <stdint.h>
#include <stdbool.h>

#ifdef RAYLIB
  #include "raylib.h"
#ifndef PLATFORM_WEB
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
  #else
    BITMAPINFO bitmap_info;
    HDC bitmap_device_context;
    MSG msg;
    HWND handle;
  #endif
};

extern struct Window Window;

void BeginFrame(void);
void EndFrame(void);
void D(int32_t x, int32_t y, uint32_t color);
void C(uint32_t color);
int32_t StartEngine(int32_t size_x, int32_t size_y, const char* name);
int32_t SetWindowSizes(int32_t size_x, int32_t size_y);
void UpdateKeyState(uint32_t key, uint32_t bitfield);

// NOTE: this was used for checking high-DPI settings
////#pragma comment(lib, "shcore.lib")
////#include <shellscalingapi.h>
#endif
