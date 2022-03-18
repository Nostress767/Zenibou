#ifdef RAYLIB
#include "raylib.h"
#define DrawPixel(x,y,color) DrawPixel(x,GetScreenWidth()-1 - (y),GetColor(color))
#define DrawRectangle(x,y,sizex,sizey,color) DrawRectangle(x,GetScreenWidth()-1 - (y),sizex,sizey,GetColor(color))
#define ClearBackground(color) ClearBackground(GetColor(color))
#define InitWindow(x,y,name) InitWindow(x,y,"Serokuchi");SetWindowState(FLAG_WINDOW_UNDECORATED);
#else

#ifndef _ZENIBOU_ZENIBOU_H_
#define _ZENIBOU_ZENIBOU_H_

#define DPI_AWARENESS_CONTEXT_SYSTEM_AWARE ((DPI_AWARENESS_CONTEXT)-2)
#define WIN32_LEAN_AND_MEAN
#define UNICODE
#define CloseWindow idkwhattodowiththis
#include <windows.h>
#undef CloseWindow
#include <stdint.h>
#include <stdbool.h>
#include "InputHandling.h"
#include "Clock.h"

uint32_t GetColor(uint32_t color);
bool WindowShouldClose(void);
void CloseWindow(void);
int32_t GetScreenWidth(void);
int32_t GetScreenHeight(void);
LRESULT CALLBACK WindowProcedure(HWND window, UINT message, WPARAM w_param, LPARAM l_param);
int32_t WINAPI SetWindowSize(int32_t size_x, int32_t size_y);
int32_t WINAPI InitWindow(int32_t size_x, int32_t size_y, const wchar_t* name);
void BeginDrawing(void);
void EndDrawing(void);
void DrawPixel(int32_t x, int32_t y, uint32_t color);
void DrawRectangle(int32_t x, int32_t y, int32_t size_x, int32_t size_y, uint32_t color);
void ClearBackground(uint32_t color);

struct Window{
  // TODO: maybe remove these global variables? Maybe not also? IDK, whatever is easier
  int32_t width, height;
  int32_t current_pos_x, current_pos_y;
  void* bitmap_memory;
  bool is_running;
  bool is_focused;
  BITMAPINFO bitmap_info;
  HDC bitmap_device_context;
  MSG msg;
  HWND handle;
};

extern struct Window Window;

#define DrawPixel(x,y,color) DrawPixel(x,y,(color>>8)|(color<<24))
#define DrawRectangle(x,y,sizex,sizey,color) DrawRectangle(x,y,sizex,sizey,(color>>8)|(color<<24))
#define ClearBackground(color) ClearBackground((color>>8)|(color<<24))
#define InitWindow(x,y,name) InitWindow(x,y,L ## name);

#endif

//#pragma comment(lib, "user32.lib")
//#pragma comment(lib, "gdi32.lib")
////#pragma comment(lib, "shcore.lib")
//#pragma comment(linker, "/subsystem:console /ENTRY:mainCRTStartup")
//#include <shellscalingapi.h>
#endif
