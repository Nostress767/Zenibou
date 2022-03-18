#ifndef _ZENIBOU_ZENIBOU_C_
#define _ZENIBOU_ZENIBOU_C_

#include <windowsx.h>
#include "Zenibou.h"

#undef DrawPixel
#undef DrawRectangle
#undef ClearBackground
#undef InitWindow

struct Window Window;

uint32_t GetColor(uint32_t color){return (color>>8)|(color<<24);};

bool WindowShouldClose(void){return !Window.is_running;}

void CloseWindow(void){Window.is_running = false;}

int32_t GetScreenWidth(void){return Window.width;}

int32_t GetScreenHeight(void){return Window.height;}

int32_t WINAPI SetWindowSize(int32_t size_x, int32_t size_y){
  VirtualFree(Window.bitmap_memory, 0, MEM_RELEASE);
  Window.bitmap_memory = VirtualAlloc(0,size_x * size_y * 4,MEM_RESERVE|MEM_COMMIT,PAGE_READWRITE);

  ReleaseDC(Window.handle, Window.bitmap_device_context);
  Window.bitmap_info = (BITMAPINFO){ .bmiHeader = {.biSize = sizeof(Window.bitmap_info.bmiHeader), .biWidth = size_x,
                                     .biHeight = size_y, .biPlanes = 1, .biBitCount = 32, .biCompression = BI_RGB}};
  Window.bitmap_device_context = GetDC(Window.handle);
  
  Window.current_pos_x = (GetSystemMetrics(SM_CXSCREEN) / 2) - (size_x / 2);
  Window.current_pos_y = (GetSystemMetrics(SM_CYSCREEN) / 2) - (size_y / 2);
  MoveWindow(Window.handle, Window.current_pos_x, Window.current_pos_y, size_x, size_y, true);

  return 0;}

int32_t WINAPI InitWindow(int32_t size_x, int32_t size_y, const wchar_t* name){
  SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_SYSTEM_AWARE);
  
  HINSTANCE instance = GetModuleHandle(0);

  const wchar_t class_name[] = L"Zenibou";
  WNDCLASSW window_class = {.lpfnWndProc = WindowProcedure,.hInstance = instance,.style = CS_HREDRAW | CS_VREDRAW,
                            .lpszClassName = class_name,.hCursor = LoadCursor(0, IDC_ARROW),};
  ShowCursor(false);

  RegisterClass(&window_class);
  
  Window.current_pos_x = (GetSystemMetrics(SM_CXSCREEN) / 2) - (size_x / 2);
  Window.current_pos_y = (GetSystemMetrics(SM_CYSCREEN) / 2) - (size_y / 2);
  
  Window.handle = CreateWindowEx(//WS_EX_OVERLAPPEDWINDOW,
                                 0, 
                                 class_name, name,
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
}

void BeginDrawing(void){
  while(PeekMessage(&Window.msg, NULL, 0, 0, PM_REMOVE)){
    //if(msg.message == WM_QUIT) running = false;
    TranslateMessage(&Window.msg);
    DispatchMessage(&Window.msg);
  }
}

void EndDrawing(void){
  Tick();
  //while(PeekMessage(&Window.msg, NULL, 0, 0, PM_REMOVE)){
  //  TranslateMessage(&Window.msg);
  //  DispatchMessage(&Window.msg);}

  for(int32_t i = 0; i < 256; i++){
    if(Key[i].was_pressed){
      Key[i].was_pressed = false;
      Key[i].was_held = true;
      Key[i].was_released = false;}
    else if(Key[i].was_released){
      Key[i].was_pressed = false;
      Key[i].was_held = false;
      Key[i].was_released = false;}}

  StretchDIBits(Window.bitmap_device_context,
                0,0,
                Window.width,Window.height,
                0,0,
                Window.width,Window.height,
                Window.bitmap_memory,
                &Window.bitmap_info,
                DIB_RGB_COLORS,
                SRCCOPY);
}

void DrawPixel(int32_t x, int32_t y, uint32_t color){
  if(x < 0 || y < 0 || x >= Window.width || y >= Window.height)
    return;
  uint32_t* pixel = (uint32_t *)Window.bitmap_memory;
  pixel += y * Window.width + x;
  *pixel = color;}

void DrawRectangle(int32_t x, int32_t y, int32_t size_x, int32_t size_y, uint32_t color){
  for(int32_t i = 0; i < size_y; i++)
    for(int32_t j = 0; j < size_x; j++)
      DrawPixel(x+j, y+i, color);
}

void ClearBackground(uint32_t color){
  uint32_t *pixel = (uint32_t *)Window.bitmap_memory;
  for(int i = 0; i < Window.width * Window.height; ++i)
    *pixel++ = color;}

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
        switch(w_param){
          // "o" exits the program
          case 'O':{
            DestroyWindow(window);
          }; break;
          case 'Q':{
            SetWindowSize(640,480);
          }; break;
          case 'W':{
            SetWindowSize(1280,720);
          }; break;
          case 'E':{
            SetWindowSize(1920,1080);
          }; break;
        }
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
