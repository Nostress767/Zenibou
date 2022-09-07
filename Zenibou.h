#ifndef _ZENIBOU_ZENIBOU_H_
#define _ZENIBOU_ZENIBOU_H_

// TODO: learn about icons, and how to fit them into executables

#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifndef _WIN32
#define IncludeMedia(x, type)                                                  \
  extern unsigned char _binary_##x##_##type##_start[];                         \
  extern unsigned char _binary_##x##_##type##_end[];
#define MediaStart(x, type) _binary_##x##_##type##_start
#define MediaEnd(x, type) _binary_##x##_##type##_end
#else
#define IncludeMedia(x, type)                                                  \
  extern unsigned char binary_##x##_##type##_start[];                          \
  extern unsigned char binary_##x##_##type##_end[];
#define MediaStart(x, type) binary_##x##_##type##_start
#define MediaEnd(x, type) binary_##x##_##type##_end
#endif
#define MediaSize(x, type) MediaEnd(x, type) - MediaStart(x, type)

// BEGIN GNU/Linux includes
#ifndef _WIN32
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <errno.h>
#include <fcntl.h>
#include <linux/joystick.h>
#include <sys/ioctl.h>
#include <unistd.h>
void ProcessXEvent(void);
// END GNU/Linux includes

// BEGIN Windows includes
#else

#define UNICODE
#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <windowsx.h>
#include <xinput.h>
LRESULT CALLBACK WindowProcedure(HWND window, UINT message, WPARAM w_param,
                                 LPARAM l_param);
// END Windows includes
#endif

// TODO: investigate whatever this is:
// (https://docs.microsoft.com/en-us/windows/win32/gdi/alpha-blending)
// (https://docs.microsoft.com/en-us/windows/win32/gdi/alpha-blending-a-bitmap)

#define STB_IMAGE_IMPLEMENTATION
#include "external/stb_image.h"

#define MA_NO_ENCODING
// TODO: investigate if these below can be safely defined
//#define MA_NO_DEVICE_IO
//#define MA_NO_THREADING
#define MINIAUDIO_IMPLEMENTATION
#include "external/miniaudio.h"
#undef PlaySound

// Thin "wrapper" around miniaudio's functions to fit this style
typedef ma_sound Sound;
#define SoundStart(sound) ma_sound_start(&sound)
#define SoundStop(sound) ma_sound_stop(&sound)
#define SoundSeek(sound, frame) ma_sound_start(&sound, frame)

// Because I love rust-lang
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

//
// BEGIN Circular Dynamic Linked List with Sentinel API
//

// Use this to create a list.
#define CreateList(type) AllocList(sizeof(type))

typedef struct Node {
  void *data;
  struct Node *prev, *next;
} Node;

typedef struct List {
  struct Node *sentinel;
  size_t sz;
  int32_t n;
} List;

typedef struct ListIterator {
  Node *cur;
  List *list;
} ListIterator;

typedef ListIterator list_iterator;

// Memory manipulation.
List AllocList(size_t sz);
void FreeList(List *self);

// Mutators.
void ListPushBack(List *self, void *element);
void ListPushFront(List *self, void *element);
bool ListPopBack(List *self);
bool ListPopFront(List *self);

// Getters.
void *ListBack(List l);
void *ListFront(List l);
bool ListEmpty(List l);
int32_t ListSize(List l);

// Create ListIterator.
ListIterator ListIterateFromFront(List *self);
ListIterator ListIterateFromBack(List *self);

// Insert based on iterator.
void ListInsertPrev(ListIterator *self, void *element);
void ListInsertNext(ListIterator *self, void *element);

// Remove based on iterator.
bool ListRemovePrev(ListIterator *self);
bool ListRemoveNext(ListIterator *self);
ListIterator ListRemove(ListIterator *self);

// Get element from iterator.
void *ListPrevElement(ListIterator it);
void *ListNextElement(ListIterator it);
void *ListElement(ListIterator it);

// Move through iterator.
ListIterator ListPrev(ListIterator it);
ListIterator ListNext(ListIterator it);
bool ListEnd(ListIterator it);

//
// END Linked List API
//

// PNG-type sprite using stb_image's API
typedef struct Sprite {
  i32 x, y;
  i32 width, height, channels;
  u8 **data;
} Sprite;

void UpdateJoystickState(void);
void InitializeAudio(void);
void PlaySound(const char *name);
void DeclareSound(const u8 start[], i32 len, const char *name);
Sound AllocSound(const u8 start[], i32 len, bool loops);
void InitializeClock(void);
void TickClock(void);
void BeginFrame(void);
void EndFrame(void);
void D(i32 x, i32 y, u32 color);
void C(u32 color);
i32 StartEngine(i32 size_x, i32 size_y, const char *name);
void SetWindowSize(i32 size_x, i32 size_y);
void UpdateKeyState(u32 key, u32 bitfield);
void DrawFontSprite(Sprite* spr, i32 size_x, i32 size_y, i32 x, i32 y, char* text, u32 color, i32 scale, i32 space_x, i32 space_y);
void DrawSprite(Sprite *spr);
void FreeSprite(Sprite *spr);
Sprite AllocSprite(const u8 start[], i32 len, i32 x, i32 y);
void ToggleFullscreen(void);

void SendRumble(i32 controller, u16 left, u16 right);

enum MouseButtons {
  kMouseLeft = 1,
  kMouseMiddle,
  kMouseRight,
  kMouseScrollUp,
  kMouseScrollDown
};

enum OtherKeys {
  kEscape = 128,
  kEnter,
  kTab,
  kBackspace,
  kInsert,
  kDelete,
  kRight,
  kLeft,
  kDown,
  kUp,
  kPageUp,
  kPageDown,
  kHome,
  kEnd,
  kCapslock,
  kScrollLock,
  kNumLock,
  kPrintScreen,
  kPauseBreak,
  kF1,
  kF2,
  kF3,
  kF4,
  kF5,
  kF6,
  kF7,
  kF8,
  kF9,
  kF10,
  kF11,
  kF12,
  kNumpad0,
  kNumpad1,
  kNumpad2,
  kNumpad3,
  kNumpad4,
  kNumpad5,
  kNumpad6,
  kNumpad7,
  kNumpad8,
  kNumpad9,
  kDecimal,
  kDivide,
  kMultiply,
  kSubtract,
  kAdd,
  kLeftShift,
  kLeftCtrl,
  kLeftAlt,
  kLeftSuper,
  kRightShift,
  kRightCtrl,
  kRightAlt,
  kRightSuper
};

enum JoystickButtons {
  kDpadUp,
  kDpadDown,
  kDpadLeft,
  kDpadRight,
  kStart,
  kBack,
  kLeftThumb,
  kRightThumb,
  kLeftShoulder,
  kRightShoulder,
  kA,
  kB,
  kX,
  kY,
  kDualShockLeftTrigger,
  kDualShockRightTrigger,
  kDualShockHome
};

enum JoystickAxes {
  kLeftThumbX,
  kLeftThumbY,
  kLeftTrigger,
  kRightThumbX,
  kRightThumbY,
  kRightTrigger
};

struct Mouse {
  i16 x, y;
  bool left_pressed, middle_pressed, right_pressed;
  bool left_held, middle_held, right_held;
  bool left_released, middle_released, right_released;
  bool is_focused;
} Mouse;

struct Key {
  bool is_pressed, is_held, is_released;
} Key[256] = {0};

// TODO: maybe joysticks should also have repeating (like keys)?
struct Joystick {
#ifndef _WIN32
  struct js_event event;
  i32 fd;
  char path[16];
#else
  XINPUT_STATE js_state;
  // f64
  // u8 timer;
#endif
  char name[64];
  bool is_on;
  i32 axes_n;
  i32 buttons_n;
  struct Key button[32];
  i32 axis[16];
} Joystick[4] = {
#ifndef _WIN32
    {{{{0}}, -1, "/dev/input/js0", {{0}}, false, 0, 0, {{0}}, {0}}}},
    {{{{0}}, -1, "/dev/input/js1", {{0}}, false, 0, 0, {{0}}, {0}}}},
    {{{{0}}, -1, "/dev/input/js2", {{0}}, false, 0, 0, {{0}}, {0}}}},
    {{{{0}}, -1, "/dev/input/js3", {{0}}, false, 0, 0, {{0}}, {0}}}}
#else
    // To Windows every controller is Xbox Controller
    { {0}, "Xbox Controller", false, 6, 14, {{0}}, {0}},
    { {0}, "Xbox Controller", false, 6, 14, {{0}}, {0}},
    { {0}, "Xbox Controller", false, 6, 14, {{0}}, {0}},
    { {0}, "Xbox Controller", false, 6, 14, {{0}}, {0}}
#endif
};

struct Clock {
  f64 last_second_elapsed_time, last_frame_elapsed_time, total_elapsed_time;
  u64 frame;
  i32 frames_last_second;
  clock_t time1, time2;
} Clock;

struct W {
  i32 width, height;
  i32 previous_width, previous_height;
  i32 offset_x, offset_y;
  i32 current_pos_x, current_pos_y;
  void *bitmap_memory;
  bool is_running;
  bool is_focused;
  bool is_fullscreen;
  ma_engine audio_engine;
  ma_decoder_config decoder_config;
  List audio_decoders;
#ifndef _WIN32
  char name[4096];
  Display *display;
  Visual *visual;
  XImage *bitmap;
  GC bitmap_device_context;
  XEvent msg;
  Window handle;
#else
  BITMAPINFO bitmap_info;
  HDC bitmap_device_context;
  MSG msg;
  HWND handle;
  HMODULE xinput_library;
  DWORD (WINAPI *xinput_get_state)(DWORD, XINPUT_STATE*);
  DWORD (WINAPI *xinput_set_state)(DWORD, XINPUT_VIBRATION*);
#endif
} W;

void InitializeClock(void) {
  Clock.last_second_elapsed_time = 0;
  Clock.last_frame_elapsed_time = 0;
  Clock.total_elapsed_time = 0;
  Clock.frame = 0;
  Clock.frames_last_second = 0;
  Clock.time1 = clock();
  Clock.time2 = clock();
}

void TickClock(void) {
  Clock.time2 = clock();
  Clock.last_frame_elapsed_time =
      ((f64)(Clock.time2 - Clock.time1)) / CLOCKS_PER_SEC;
  Clock.time1 = Clock.time2;
  Clock.last_second_elapsed_time += Clock.last_frame_elapsed_time;
  Clock.total_elapsed_time += Clock.last_frame_elapsed_time;
  Clock.frame++;
  if (Clock.last_second_elapsed_time > 1.) {
    Clock.frames_last_second = (i32)Clock.frame;
    Clock.last_second_elapsed_time = 0.;
    Clock.frame = 0;
  }
}

void BeginFrame(void) {
#ifndef _WIN32
  UpdateJoystickState();
  while (XPending(W.display) > 0) {
    XNextEvent(W.display, &W.msg);
    ProcessXEvent();
  }
#else
  if(W.xinput_library)
    UpdateJoystickState();
  while (PeekMessage(&W.msg, NULL, 0, 0, PM_REMOVE)) {
    TranslateMessage(&W.msg);
    DispatchMessage(&W.msg);
  }
#endif
}

void EndFrame(void) {
#ifndef _WIN32
  XPutImage(W.display, W.handle, W.bitmap_device_context, W.bitmap, 0, 0, 0, 0,
            W.bitmap->width, W.bitmap->height);
#else
  // NOTE: StretchDIBits actually supports scaling, but this was removed due to
  // XPutImage not supporting it (to maintain consistency)
  StretchDIBits(W.bitmap_device_context, W.offset_x, W.offset_y, W.width,
                W.height, 0, 0, W.width, W.height, W.bitmap_memory,
                &W.bitmap_info, DIB_RGB_COLORS, SRCCOPY);
#endif
  for (i8 i = 0; i < 4; i++) {
    for (i8 j = 0; j < 32; j++) {
      if (Joystick[i].button[j].is_pressed)
        Joystick[i].button[j].is_held = true;
      Joystick[i].button[j].is_pressed = false;
      Joystick[i].button[j].is_released = false;
    }
  }

  for (i16 i = 0; i < 256; i++) {
    if (Key[i].is_pressed)
      Key[i].is_held = true;
    Key[i].is_pressed = false;
    Key[i].is_released = false;
  }

  // NOTE: I don't know what to do with modifier keys
  Key[kLeftShift].is_held = false;
  Key[kLeftCtrl].is_held = false;
  Key[kLeftAlt].is_held = false;
  Key[kLeftSuper].is_held = false;
  Key[kRightShift].is_held = false;
  Key[kRightCtrl].is_held = false;
  Key[kRightAlt].is_held = false;
  Key[kRightSuper].is_held = false;

  if (Mouse.left_pressed)
    Mouse.left_held = true;
  if (Mouse.middle_pressed)
    Mouse.middle_held = true;
  if (Mouse.right_pressed)
    Mouse.right_held = true;

  Mouse.left_pressed = false;
  Mouse.left_released = false;
  Mouse.middle_pressed = false;
  Mouse.middle_released = false;
  Mouse.right_pressed = false;
  Mouse.right_released = false;

  TickClock();
}

void D(i32 x, i32 y, u32 color) {
  if (x < 0 || y < 0 || x >= W.width || y >= W.height)
    return;
#ifndef _WIN32
  // On Xlib the y-axis is inverted (compared to windows)
  *((u32 *)W.bitmap_memory + (W.height - 1 - y) * W.width + x) = color;
#else
  *((u32 *)W.bitmap_memory + y * W.width + x) = color;
#endif
}

void C(u32 color) {
  for (i32 i = 0; i < W.width; ++i)
    for (i32 j = 0; j < W.height; ++j)
#ifndef _WIN32
      // On X11 the y-axis is inverted (compared to windows)
      *((u32 *)W.bitmap_memory + (W.height - 1 - j) * W.width + i) = color;
#else
      *((u32 *)W.bitmap_memory + j * W.width + i) = color;
#endif
}

// Always load these fonts
IncludeMedia(font5x6,png);
IncludeMedia(font5x5,png);
Sprite internal_font5x6;
Sprite internal_font5x5;
#define DrawString5x6(x,y,str,col,scal,spc_x,spc_y) DrawFontSprite(&internal_font5x6,5,6,x,y,str,col,scal,spc_x,spc_y)
#define DrawString5x5(x,y,str,col,scal,spc_x,spc_y) DrawFontSprite(&internal_font5x5,5,5,x,y,str,col,scal,spc_x,spc_y)

i32 StartEngine(i32 size_x, i32 size_y, const char *name) {
  internal_font5x6 = AllocSprite(MediaStart(font5x6,png), MediaSize(font5x6,png), 0, 0);
  internal_font5x5 = AllocSprite(MediaStart(font5x5,png), MediaSize(font5x5,png), 0, 0);
#ifndef _WIN32
  // TODO: check if high DPI settings are needed
  W.display = XOpenDisplay(0);

  W.width = size_x;
  W.height = size_y;

  memset(W.name, 0, 4096);
  memcpy(W.name, name, strlen(name));

  W.handle = XCreateWindow(W.display, DefaultRootWindow(W.display), 0, 0,
                           W.width, W.height, 0, CopyFromParent, CopyFromParent,
                           W.visual, 0, NULL);

  XSizeHints *size_hints = XAllocSizeHints();
  size_hints->flags = PMinSize | PMaxSize;
  size_hints->min_width = size_hints->max_width = W.width;
  size_hints->min_height = size_hints->max_height = W.height;
  XSetWMNormalHints(W.display, W.handle, size_hints);
  XFree(size_hints);

  XStoreName(W.display, W.handle, W.name);

  // Unicode -> https://github.com/godotengine/godot/issues/2952
  Xutf8SetWMProperties(W.display, W.handle, W.name, NULL, NULL, 0, NULL, NULL,
                       NULL);

  XSelectInput(W.display, W.handle,
               FocusChangeMask | EnterWindowMask | LeaveWindowMask |
                   KeyPressMask | KeyReleaseMask | ButtonPressMask |
                   ButtonReleaseMask | PointerMotionMask);
  XMapWindow(W.display, W.handle);

  XWindowAttributes windowAttributes;
  XGetWindowAttributes(W.display, W.handle, &windowAttributes);

  W.bitmap_device_context = XCreateGC(W.display, W.handle, 0, 0);
  W.bitmap_memory = malloc(W.width * W.height * 4);

  W.bitmap =
      XCreateImage(W.display, W.visual, windowAttributes.depth, ZPixmap, 0,
                   (char *)W.bitmap_memory, W.width, W.height, 8 * 4, 0);
#else
  wchar_t title[256];
  MultiByteToWideChar(CP_UTF8, 0, name, -1, title,
                      MultiByteToWideChar(CP_UTF8, 0, name, -1, NULL, 0));

  SetProcessDPIAware();

  HINSTANCE instance = GetModuleHandle(0);

  const wchar_t class_name[] = L"Zenibou";
  WNDCLASSW window_class = {
      .lpfnWndProc = WindowProcedure,
      .hInstance = instance,
      .style = CS_HREDRAW | CS_VREDRAW,
      .lpszClassName = class_name,
      .hCursor = LoadCursor(0, IDC_ARROW),
  };
  // ShowCursor(false);

  RegisterClass(&window_class);

  W.current_pos_x = (GetSystemMetrics(SM_CXSCREEN) / 2) - (size_x / 2);
  W.current_pos_y = (GetSystemMetrics(SM_CYSCREEN) / 2) - (size_y / 2);

  RECT rect = {0, 0, size_x, size_y};
  AdjustWindowRectEx(&rect,
                     WS_CAPTION | WS_VISIBLE | WS_SYSMENU | WS_MAXIMIZEBOX |
                         WS_MINIMIZEBOX,
                     false, 0);

  W.offset_x = 0;
  W.offset_y = 0;
  W.width = size_x;
  W.height = size_y;

  W.handle =
      CreateWindowEx( // WS_EX_OVERLAPPEDWINDOW,
                      // //(https://docs.microsoft.com/en-us/windows/win32/winmsg/extended-window-styles)
          0, class_name, title, WS_CAPTION | WS_VISIBLE | WS_SYSMENU,
          // WS_POPUP|WS_VISIBLE,
          //|WS_VISIBLE,
          W.current_pos_x,        // start_x
          W.current_pos_y,        // start_y
          rect.right - rect.left, // size_x
          rect.bottom - rect.top, // size_y
          0, 0, instance, 0);

  W.bitmap_memory = VirtualAlloc(0, W.width * W.height * 4,
                                 MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
  W.bitmap_info =
      (BITMAPINFO){.bmiHeader = {.biSize = sizeof(W.bitmap_info.bmiHeader),
                                 .biWidth = W.width,
                                 .biHeight = W.height,
                                 .biPlanes = 1,
                                 .biBitCount = 32,
                                 .biCompression = BI_RGB}};
  W.bitmap_device_context = GetDC(W.handle);
  W.xinput_library = LoadLibraryA("xinput1_3.dll");
  if(W.xinput_library){
    W.xinput_get_state = (DWORD (WINAPI *)(DWORD, XINPUT_STATE*))GetProcAddress(W.xinput_library, "XInputGetState");
    W.xinput_set_state = (DWORD (WINAPI *)(DWORD, XINPUT_VIBRATION*))GetProcAddress(W.xinput_library, "XInputSetState");
  }
#endif
  W.is_running = true;
  InitializeClock();
  InitializeAudio();

  W.is_fullscreen = false;

  return 0;
}

void SetWindowSize(i32 size_x, i32 size_y) {
#ifndef _WIN32
  XDestroyImage(W.bitmap);
  XDestroyWindow(W.display, W.handle);

  W.width = size_x;
  W.height = size_y;

  W.handle = XCreateWindow(W.display, DefaultRootWindow(W.display), 0, 0,
                           W.width, W.height, 0, CopyFromParent, CopyFromParent,
                           W.visual, 0, NULL);

  XStoreName(W.display, W.handle, W.name);
  Xutf8SetWMProperties(W.display, W.handle, W.name, NULL, NULL, 0, NULL, NULL,
                       NULL);

  XSelectInput(W.display, W.handle,
               KeyPressMask | KeyReleaseMask | ButtonPress | ButtonRelease |
                   MotionNotify);
  XMapWindow(W.display, W.handle);

  XWindowAttributes windowAttributes;
  XGetWindowAttributes(W.display, W.handle, &windowAttributes);

  W.bitmap_device_context = XCreateGC(W.display, W.handle, 0, 0);
  W.bitmap_memory = malloc(W.width * W.height * 4);

  XSizeHints *size_hints = XAllocSizeHints();
  size_hints->flags = PMinSize | PMaxSize;
  size_hints->min_width = size_hints->max_width = W.width;
  size_hints->min_height = size_hints->max_height = W.height;
  XSetWMNormalHints(W.display, W.handle, size_hints);
  XFree(size_hints);

  W.bitmap =
      XCreateImage(W.display, W.visual, windowAttributes.depth, ZPixmap, 0,
                   (char *)W.bitmap_memory, W.width, W.height, 8 * 4, 0);
#else
  VirtualFree(W.bitmap_memory, 0, MEM_RELEASE);
  W.bitmap_memory = VirtualAlloc(0, size_x * size_y * 4,
                                 MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

  ReleaseDC(W.handle, W.bitmap_device_context);
  W.bitmap_info =
      (BITMAPINFO){.bmiHeader = {.biSize = sizeof(W.bitmap_info.bmiHeader),
                                 .biWidth = size_x,
                                 .biHeight = size_y,
                                 .biPlanes = 1,
                                 .biBitCount = 32,
                                 .biCompression = BI_RGB}};
  W.bitmap_device_context = GetDC(W.handle);

  RECT rect = {0, 0, size_x, size_y};
  if (size_x > GetSystemMetrics(SM_CXSCREEN) ||
      size_y > GetSystemMetrics(SM_CYSCREEN))
    return;
  else if (size_x == GetSystemMetrics(SM_CXSCREEN) &&
           size_y == GetSystemMetrics(SM_CYSCREEN)) {
    SetWindowLongPtr(W.handle, GWL_STYLE, WS_POPUP | WS_VISIBLE);
    AdjustWindowRectEx(&rect, WS_POPUP | WS_VISIBLE, false, 0);
  } else {
    SetWindowLongPtr(W.handle, GWL_STYLE, WS_CAPTION | WS_VISIBLE | WS_SYSMENU);
    AdjustWindowRectEx(&rect, WS_CAPTION | WS_VISIBLE | WS_SYSMENU, false, 0);
  }
  W.current_pos_x = (GetSystemMetrics(SM_CXSCREEN) / 2) - (size_x / 2);
  W.current_pos_y = (GetSystemMetrics(SM_CYSCREEN) / 2) - (size_y / 2);
  MoveWindow(W.handle, W.current_pos_x, W.current_pos_y, rect.right - rect.left,
             rect.bottom - rect.top, true);
#endif
}

void UpdateKeyState(u32 key, u32 bitfield) {
  // TODO: check to make sure that linux is 100% consistent with windows
  u32 mapped_key = key;

#ifndef _WIN32
  bool is_down = bitfield;

  switch (key) {
  case 0xFF1B:
    mapped_key = kEscape;
    break;
  case 0xFF0D:
  case 0xFF8D:
    mapped_key = kEnter;
    break;
  case 0xFF09:
    mapped_key = kTab;
    break;
  case 0xFF08:
    mapped_key = kBackspace;
    break;
  case 0xFF63:
    mapped_key = kInsert;
    break;
  case 0xFFFF:
  case 0xFF9F:
    mapped_key = kDelete;
    break;
  case 0xFF53:
    mapped_key = kRight;
    break;
  case 0xFF51:
    mapped_key = kLeft;
    break;
  case 0xFF54:
    mapped_key = kDown;
    break;
  case 0xFF52:
    mapped_key = kUp;
    break;
  case 0xFF55:
    mapped_key = kPageUp;
    break;
  case 0xFF56:
    mapped_key = kPageDown;
    break;
  // case 0xFF:
  //   mapped_key = kHome;
  //   break;
  case 0xFF57:
    mapped_key = kEnd;
    break;
  case 0xFFE5:
    mapped_key = kCapslock;
    break;
  case 0xFF14:
    mapped_key = kScrollLock;
    break;
  case 0xFF7F:
    mapped_key = kNumLock;
    break;
  // case 0xFF:
  //   mapped_key = kPrintScreen;
  //   break;
  case 0xFF13:
    mapped_key = kPauseBreak;
    break;
  case 0xFFBE:
    mapped_key = kF1;
    break;
  case 0xFFBF:
    mapped_key = kF2;
    break;
  case 0xFFC0:
    mapped_key = kF3;
    break;
  case 0xFFC1:
    mapped_key = kF4;
    break;
  case 0xFFC2:
    mapped_key = kF5;
    break;
  case 0xFFC3:
    mapped_key = kF6;
    break;
  case 0xFFC4:
    mapped_key = kF7;
    break;
  case 0xFFC5:
    mapped_key = kF8;
    break;
  case 0xFFC6:
    mapped_key = kF9;
    break;
  case 0xFFC7:
    mapped_key = kF10;
    break;
  case 0xFFC8:
    mapped_key = kF11;
    break;
  case 0xFFC9:
    mapped_key = kF12;
    break;
  case 0xFF9E:
    mapped_key = kNumpad0;
    break;
  case 0xFF9C:
    mapped_key = kNumpad1;
    break;
  case 0xFF99:
    mapped_key = kNumpad2;
    break;
  case 0xFF9B:
    mapped_key = kNumpad3;
    break;
  case 0xFF96:
    mapped_key = kNumpad4;
    break;
  case 0xFF9D:
    mapped_key = kNumpad5;
    break;
  case 0xFF98:
    mapped_key = kNumpad6;
    break;
  case 0xFF95:
    mapped_key = kNumpad7;
    break;
  case 0xFF97:
    mapped_key = kNumpad8;
    break;
  case 0xFF9A:
    mapped_key = kNumpad9;
    break;
  // case 0xFF:
  //   mapped_key = kDecimal;
  //   break;
  case 0xFFAF:
    mapped_key = kDivide;
    break;
  case 0xFFAA:
    mapped_key = kMultiply;
    break;
  case 0xFFAD:
    mapped_key = kSubtract;
    break;
  case 0xFFAB:
    mapped_key = kAdd;
    break;
  case 0xFFE1:
    mapped_key = kLeftShift;
    break;
  case 0xFFE3:
    mapped_key = kLeftCtrl;
    break;
  case 0xFFE9:
    mapped_key = kLeftAlt;
    break;
  case 0xFFEB:
    mapped_key = kLeftSuper;
    break;
  case 0xFFE2:
    mapped_key = kRightShift;
    break;
  case 0xFFE4:
    mapped_key = kRightCtrl;
    break;
  case 0xFF03:
    mapped_key = kRightAlt;
    break;
  case 0xFF67: // NOTE: I don't think that this key is Super but it works for
               // now
    mapped_key = kRightSuper;
    break;
  }
  if (mapped_key >= 'a' && mapped_key <= 'z') {
    Key[mapped_key - 32].is_pressed = is_down;
    Key[mapped_key - 32].is_held = false;
    Key[mapped_key - 32].is_released = !is_down;
  }
  Key[mapped_key].is_pressed = is_down;
  Key[mapped_key].is_held = false;
  Key[mapped_key].is_released = !is_down;
#else
  bool was_down = bitfield >> 30 & 1;
  bool is_down = bitfield >> 31 ^ 1;
  switch (key) {
  case VK_ESCAPE:
    mapped_key = kEscape;
    break;
  case VK_RETURN:
    mapped_key = kEnter;
    break;
  case VK_TAB:
    mapped_key = kTab;
    break;
  case VK_BACK:
    mapped_key = kBackspace;
    break;
  case VK_INSERT:
    mapped_key = kInsert;
    break;
  case VK_DELETE:
    mapped_key = kDelete;
    break;
  case VK_RIGHT:
    mapped_key = kRight;
    break;
  case VK_LEFT:
    mapped_key = kLeft;
    break;
  case VK_DOWN:
    mapped_key = kDown;
    break;
  case VK_UP:
    mapped_key = kUp;
    break;
  case VK_PRIOR:
    mapped_key = kPageUp;
    break;
  case VK_NEXT:
    mapped_key = kPageDown;
    break;
  case VK_HOME:
    mapped_key = kHome;
    break;
  case VK_END:
    mapped_key = kEnd;
    break;
  case VK_CAPITAL:
    mapped_key = kCapslock;
    break;
  case VK_SCROLL:
    mapped_key = kScrollLock;
    break;
  case VK_NUMLOCK:
    mapped_key = kNumLock;
    break;
  case VK_SNAPSHOT:
    mapped_key = kPrintScreen;
    break;
  case VK_PAUSE:
    mapped_key = kPauseBreak;
    break;
  case VK_F1:
    mapped_key = kF1;
    break;
  case VK_F2:
    mapped_key = kF2;
    break;
  case VK_F3:
    mapped_key = kF3;
    break;
  case VK_F4:
    mapped_key = kF4;
    break;
  case VK_F5:
    mapped_key = kF5;
    break;
  case VK_F6:
    mapped_key = kF6;
    break;
  case VK_F7:
    mapped_key = kF7;
    break;
  case VK_F8:
    mapped_key = kF8;
    break;
  case VK_F9:
    mapped_key = kF9;
    break;
  case VK_F10:
    mapped_key = kF10;
    break;
  case VK_F11:
    mapped_key = kF11;
    break;
  case VK_F12:
    mapped_key = kF12;
    break;
  case VK_NUMPAD0:
    mapped_key = kNumpad0;
    break;
  case VK_NUMPAD1:
    mapped_key = kNumpad1;
    break;
  case VK_NUMPAD2:
    mapped_key = kNumpad2;
    break;
  case VK_NUMPAD3:
    mapped_key = kNumpad3;
    break;
  case VK_NUMPAD4:
    mapped_key = kNumpad4;
    break;
  case VK_NUMPAD5:
    mapped_key = kNumpad5;
    break;
  case VK_NUMPAD6:
    mapped_key = kNumpad6;
    break;
  case VK_NUMPAD7:
    mapped_key = kNumpad7;
    break;
  case VK_NUMPAD8:
    mapped_key = kNumpad8;
    break;
  case VK_NUMPAD9:
    mapped_key = kNumpad9;
    break;
  case VK_DECIMAL:
    mapped_key = kDecimal;
    break;
  case VK_DIVIDE:
    mapped_key = kDivide;
    break;
  case VK_MULTIPLY:
    mapped_key = kMultiply;
    break;
  case VK_SUBTRACT:
    mapped_key = kSubtract;
    break;
  case VK_ADD:
    mapped_key = kAdd;
    break;
  // TODO: fix special VK_KEYS with right variants (or leave as is)
  case VK_SHIFT:
  case VK_LSHIFT:
    mapped_key = kLeftShift;
    break;
  case VK_CONTROL:
  case VK_LCONTROL:
    mapped_key = kLeftCtrl;
    break;
  case VK_MENU:
  case VK_LMENU:
    mapped_key = kLeftAlt;
    break;
  case VK_LWIN:
    mapped_key = kLeftSuper;
    break;
  case VK_RSHIFT:
    mapped_key = kRightShift;
    break;
  case VK_RCONTROL:
    mapped_key = kRightCtrl;
    break;
  case VK_RMENU:
    mapped_key = kRightAlt;
    break;
  case VK_RWIN:
    mapped_key = kRightSuper;
    break;
  }
  if (mapped_key >= 'A' && mapped_key <= 'Z') {
    Key[mapped_key + 32].is_pressed = is_down;
    Key[mapped_key + 32].is_held = false;
    Key[mapped_key + 32].is_released = (was_down) & (!is_down);
  }
  Key[mapped_key].is_pressed = is_down;
  Key[mapped_key].is_held = false;
  Key[mapped_key].is_released = (was_down) & (!is_down);
#endif
}

#ifndef _WIN32
void ProcessXEvent(void) {
  // NOTE: Winapi equivalents missing HERE:
  // WM_SIZE
  // WM_CLOSE
  // WM_DESTROY
  switch (W.msg.type) {
  case FocusIn: {
    W.is_focused = true;
  } break;
  case FocusOut: {
    W.is_focused = false;
  } break;
  case EnterNotify: {
    Mouse.is_focused = true;
  } break;
  case LeaveNotify: {
    Mouse.is_focused = false;
  } break;
  case KeyPress: {
    UpdateKeyState(XLookupKeysym(&W.msg.xkey, 0), 1);
    break;
  }
  case KeyRelease: {
    UpdateKeyState(XLookupKeysym(&W.msg.xkey, 0), 0);
    break;
  }
  case ButtonPress: {
    // NOTE: This also detects scrolling (as ints 4 and 5), if ever needed
    switch (W.msg.xbutton.button) {
    case kMouseLeft: {
      Mouse.left_pressed = true;
      Mouse.left_held = false;
    } break;
    case kMouseMiddle: {
      Mouse.middle_pressed = true;
      Mouse.middle_held = false;
    } break;
    case kMouseRight: {
      Mouse.right_pressed = true;
      Mouse.right_held = false;
    } break;
    }
    break;
  }
  case ButtonRelease: {
    // NOTE: This also detects scrolling (as ints 4 and 5), if ever needed
    switch (W.msg.xbutton.button) {
    case kMouseLeft: {
      Mouse.left_released = true;
      Mouse.left_held = false;
    } break;
    case kMouseMiddle: {
      Mouse.middle_released = true;
      Mouse.middle_held = false;
    } break;
    case kMouseRight: {
      Mouse.right_released = true;
      Mouse.right_held = false;
    } break;
    }
  } break;
  case MotionNotify: {
    // NOTE: (1,1) is at bottom-left corner
    Mouse.x = W.msg.xmotion.x;
    Mouse.y = W.height - W.msg.xmotion.y;
  } break;
  }
}
#else
LRESULT CALLBACK WindowProcedure(HWND window, UINT message, WPARAM w_param,
                                 LPARAM l_param) {
  switch (message) {
  case WM_MOUSEMOVE: {
    Mouse.is_focused = true;
    Mouse.x = GET_X_LPARAM(l_param);
    Mouse.y = GET_Y_LPARAM(l_param);
  }
    return 0;
  case WM_MOUSELEAVE: {
    Mouse.is_focused = false;
  }
    return 0;
  case WM_SIZE: {
    W.width = GET_X_LPARAM(l_param);
    W.height = GET_Y_LPARAM(l_param);
  }
    return 0;
  case WM_MOVE: {
    W.current_pos_x = (i32)(i16)LOWORD(l_param);
    W.current_pos_y = (i32)(i16)HIWORD(l_param);
  }
    return 0;
  case WM_SETFOCUS: {
    W.is_focused = true;
  }
    return 0;
  case WM_KILLFOCUS: {
    W.is_focused = false;
  }
    return 0;
  case WM_LBUTTONDOWN: {
    Mouse.left_pressed = true;
    Mouse.left_held = false;
  }
    return 0;
  case WM_LBUTTONUP: {
    Mouse.left_released = true;
    Mouse.left_held = false;
  }
    return 0;
  case WM_MBUTTONDOWN: {
    Mouse.middle_pressed = true;
    Mouse.middle_held = false;
  }
    return 0;
  case WM_MBUTTONUP: {
    Mouse.middle_released = true;
    Mouse.middle_held = false;
  }
    return 0;
  case WM_RBUTTONDOWN: {
    Mouse.right_pressed = true;
    Mouse.right_held = false;
  }
    return 0;
  case WM_RBUTTONUP: {
    Mouse.right_released = true;
    Mouse.right_held = false;
  }
    return 0;
  case WM_KEYUP:
  case WM_SYSKEYDOWN:
  case WM_SYSKEYUP:
  case WM_KEYDOWN: {
    UpdateKeyState(w_param, l_param);
  }
    return 0;

  case WM_CLOSE: {
    W.is_running = false;
  }
    return 0;
  case WM_DESTROY: {
    PostQuitMessage(0);
    DestroyWindow(W.handle);
    W.is_running = false;
  }
    return 0;
  }
  return DefWindowProc(window, message, w_param, l_param);
}
#endif

void UpdateJoystickState(void) {
#ifndef _WIN32
  for (i8 i = 0; i < 4; i++) {
    if (!Joystick[i].is_on &&
        (Joystick[i].fd = open(Joystick[i].path, O_NONBLOCK)) > 0) {
      Joystick[i].is_on = true;
      ioctl(Joystick[i].fd, JSIOCGAXES, &Joystick[i].axes_n);
      ioctl(Joystick[i].fd, JSIOCGBUTTONS, &Joystick[i].buttons_n);
      ioctl(Joystick[i].fd, JSIOCGNAME(128), Joystick[i].name);
      // printf("%s was connected on port %d\n", Joystick[i].name, i);
      // printf("It has %d buttons and %d axes\n", Joystick[i].buttons_n,
      //        Joystick[i].axes_n);
    }
  }
  for (i8 i = 0; i < 4; i++) {
    if (!Joystick[i].is_on)
      continue;
    // TODO: clean this up
    // Since windows uses the enum directly, it could be re-ordered to fit linux
    // as ints to avoid switch
    // e.g.: as has already been done with the axes
    while (read(Joystick[i].fd, &Joystick[i].event, sizeof(Joystick[i].event)) >
           0) {
      switch (Joystick[i].event.type) {
      case JS_EVENT_BUTTON: {
        if (Joystick[i].event.value) {
          i32 mapped_button = 0;
          switch (Joystick[i].event.number) {
          default: {
            mapped_button = kA;
          } break;
          case 1: {
            mapped_button = kB;
          } break;
          case 2: {
            mapped_button = kX;
          } break;
          case 3: {
            mapped_button = kY;
          } break;
          case 4: {
            mapped_button = kLeftShoulder;
          } break;
          case 5: {
            mapped_button = kRightShoulder;
          } break;
          case 6: {
            if (Joystick[i].name[0] != 'X')
              mapped_button = kDualShockLeftTrigger;
            else
              mapped_button = kBack;
          } break;
          case 7: {
            if (Joystick[i].name[0] != 'X')
              mapped_button = kDualShockRightTrigger;
            else
              mapped_button = kStart;
          } break;
          case 8: {
            if (Joystick[i].name[0] != 'X')
              mapped_button = kBack;
            else
              mapped_button = kLeftThumb;
          } break;
          case 9: {
            if (Joystick[i].name[0] != 'X')
              mapped_button = kStart;
            else
              mapped_button = kRightThumb;
          } break;
          case 10: {
            if (Joystick[i].name[0] != 'X')
              mapped_button = kDualShockHome;
            else
              ;
          } break;
          case 11: {
            if (Joystick[i].name[0] != 'X')
              mapped_button = kLeftThumb;
            else
              ;
          } break;
          case 12: {
            if (Joystick[i].name[0] != 'X')
              mapped_button = kRightThumb;
            else
              ;
          } break;
          case 13: {
            mapped_button = kDpadUp;
          } break;
          case 14: {
            mapped_button = kDpadDown;
          } break;
          case 15: {
            mapped_button = kDpadLeft;
          } break;
          case 16: {
            mapped_button = kDpadRight;
          } break;
          }
          Joystick[i].button[mapped_button].is_pressed = true;
          Joystick[i].button[mapped_button].is_held = false;
          // printf("%s pressed button: %d\n", Joystick[i].name,
          //        Joystick[i].event.number);
        } else {
          i32 mapped_button = 0;
          switch (Joystick[i].event.number) {
          default: {
            mapped_button = kA;
          } break;
          case 1: {
            mapped_button = kB;
          } break;
          case 2: {
            mapped_button = kX;
          } break;
          case 3: {
            mapped_button = kY;
          } break;
          case 4: {
            mapped_button = kLeftShoulder;
          } break;
          case 5: {
            mapped_button = kRightShoulder;
          } break;
          case 6: {
            if (Joystick[i].name[0] != 'X')
              mapped_button = kDualShockLeftTrigger;
            else
              mapped_button = kBack;
          } break;
          case 7: {
            if (Joystick[i].name[0] != 'X')
              mapped_button = kDualShockRightTrigger;
            else
              mapped_button = kStart;
          } break;
          case 8: {
            if (Joystick[i].name[0] != 'X')
              mapped_button = kBack;
            else
              mapped_button = kLeftThumb;
          } break;
          case 9: {
            if (Joystick[i].name[0] != 'X')
              mapped_button = kStart;
            else
              mapped_button = kRightThumb;
          } break;
          case 10: {
            if (Joystick[i].name[0] != 'X')
              mapped_button = kDualShockHome;
            else
              ;
          } break;
          case 11: {
            if (Joystick[i].name[0] != 'X')
              mapped_button = kLeftThumb;
            else
              ;
          } break;
          case 12: {
            if (Joystick[i].name[0] != 'X')
              mapped_button = kRightThumb;
            else
              ;
          } break;
          case 13: {
            mapped_button = kDpadUp;
          } break;
          case 14: {
            mapped_button = kDpadDown;
          } break;
          case 15: {
            mapped_button = kDpadLeft;
          } break;
          case 16: {
            mapped_button = kDpadRight;
          } break;
          }
          Joystick[i].button[mapped_button].is_released = true;
          Joystick[i].button[mapped_button].is_held = false;
          // printf("%s released button: %d\n", Joystick[i].name,
          //        Joystick[i].event.number);
        }

      } break;
      case JS_EVENT_AXIS: {
        if (Joystick[i].event.number < 6) {
          Joystick[i].axis[Joystick[i].event.number] = Joystick[i].event.value;
        } else {
          switch (Joystick[i].event.number) {
          default: {
            if (Joystick[i].event.value > 0) {
              Joystick[i].button[kDpadRight].is_pressed = true;
              Joystick[i].button[kDpadRight].is_held = false;
            } else if (Joystick[i].event.value < 0) {
              Joystick[i].button[kDpadLeft].is_pressed = true;
              Joystick[i].button[kDpadLeft].is_held = false;
            } else {
              if (Joystick[i].button[kDpadRight].is_held) {
                Joystick[i].button[kDpadRight].is_released = true;
                Joystick[i].button[kDpadRight].is_held = false;
              } else {
                Joystick[i].button[kDpadLeft].is_released = true;
                Joystick[i].button[kDpadLeft].is_held = false;
              }
            }
          } break;
          case 7: {
            if (Joystick[i].event.value > 0) {
              Joystick[i].button[kDpadDown].is_pressed = true;
              Joystick[i].button[kDpadDown].is_held = false;
            } else if (Joystick[i].event.value < 0) {
              Joystick[i].button[kDpadUp].is_pressed = true;
              Joystick[i].button[kDpadUp].is_held = false;
            } else {
              if (Joystick[i].button[kDpadDown].is_held) {
                Joystick[i].button[kDpadDown].is_released = true;
                Joystick[i].button[kDpadDown].is_held = false;
              } else {
                Joystick[i].button[kDpadUp].is_released = true;
                Joystick[i].button[kDpadUp].is_held = false;
              }
            }
          } break;
          }
        }
        // printf("%s moved axis %d with value: %d \n", Joystick[i].name,
        //        Joystick[i].event.number, Joystick[i].event.value);
      } break;
      default: {
        // JS_EVENT_INIT event
      } break;
      }
    }
    if (errno == EAGAIN) {
      // Queue is empty
    } else if (errno == ENODEV) {
      // printf("%s was disconnected on port %d\n", Joystick[i].name, i);
      //   Device got disconnected
      close(Joystick[i].fd);
      Joystick[i].event = (struct js_event){0};
      Joystick[i].fd = -1;
      memset(Joystick[i].name, 0, sizeof(Joystick[i].name));
      Joystick[i].is_on = false;
      Joystick[i].axes_n = 0;
      Joystick[i].buttons_n = 0;
      for (i8 j = 0; j < 32; j++)
        Joystick[i].button[j] = (struct Key){0};
      for (i8 j = 0; j < 16; j++)
        Joystick[i].axis[j] = 0;
    } else if (errno == EBADF) {
      // Trying to read invalid FD
    }
  }
#else
  // TODO: Maybe investigate Winmm for joystick input (only if it's better for
  // this use)
  for (i32 i = 0; i < 4; i++) {
    if ((Joystick[i].is_on =
            (W.xinput_get_state(i, &Joystick[i].js_state) == ERROR_SUCCESS))) {
      // Joystick is connected

      if (!Joystick[i].button[kDpadUp].is_held) {
        Joystick[i].button[kDpadUp].is_pressed =
            Joystick[i].js_state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP;
        Joystick[i].button[kDpadUp].is_held = false;
      } else if (!(Joystick[i].js_state.Gamepad.wButtons &
                   XINPUT_GAMEPAD_DPAD_UP)) {
        Joystick[i].button[kDpadUp].is_released = true;
        Joystick[i].button[kDpadUp].is_held = false;
      }
      if (!Joystick[i].button[kDpadDown].is_held) {
        Joystick[i].button[kDpadDown].is_pressed =
            Joystick[i].js_state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN;
        Joystick[i].button[kDpadDown].is_held = false;
      } else if (!(Joystick[i].js_state.Gamepad.wButtons &
                   XINPUT_GAMEPAD_DPAD_DOWN)) {
        Joystick[i].button[kDpadDown].is_released = true;
        Joystick[i].button[kDpadDown].is_held = false;
      }
      if (!Joystick[i].button[kDpadLeft].is_held) {
        Joystick[i].button[kDpadLeft].is_pressed =
            Joystick[i].js_state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT;
        Joystick[i].button[kDpadLeft].is_held = false;
      } else if (!(Joystick[i].js_state.Gamepad.wButtons &
                   XINPUT_GAMEPAD_DPAD_LEFT)) {
        Joystick[i].button[kDpadLeft].is_released = true;
        Joystick[i].button[kDpadLeft].is_held = false;
      }
      if (!Joystick[i].button[kDpadRight].is_held) {
        Joystick[i].button[kDpadRight].is_pressed =
            Joystick[i].js_state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT;
        Joystick[i].button[kDpadRight].is_held = false;
      } else if (!(Joystick[i].js_state.Gamepad.wButtons &
                   XINPUT_GAMEPAD_DPAD_RIGHT)) {
        Joystick[i].button[kDpadRight].is_released = true;
        Joystick[i].button[kDpadRight].is_held = false;
      }
      if (!Joystick[i].button[kStart].is_held) {
        Joystick[i].button[kStart].is_pressed =
            Joystick[i].js_state.Gamepad.wButtons & XINPUT_GAMEPAD_START;
        Joystick[i].button[kStart].is_held = false;
      } else if (!(Joystick[i].js_state.Gamepad.wButtons &
                   XINPUT_GAMEPAD_START)) {
        Joystick[i].button[kStart].is_released = true;
        Joystick[i].button[kStart].is_held = false;
      }
      if (!Joystick[i].button[kBack].is_held) {
        Joystick[i].button[kBack].is_pressed =
            Joystick[i].js_state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK;
        Joystick[i].button[kBack].is_held = false;
      } else if (!(Joystick[i].js_state.Gamepad.wButtons &
                   XINPUT_GAMEPAD_BACK)) {
        Joystick[i].button[kBack].is_released = true;
        Joystick[i].button[kBack].is_held = false;
      }
      if (!Joystick[i].button[kLeftThumb].is_held) {
        Joystick[i].button[kLeftThumb].is_pressed =
            Joystick[i].js_state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB;
        Joystick[i].button[kLeftThumb].is_held = false;
      } else if (!(Joystick[i].js_state.Gamepad.wButtons &
                   XINPUT_GAMEPAD_LEFT_THUMB)) {
        Joystick[i].button[kLeftThumb].is_released = true;
        Joystick[i].button[kLeftThumb].is_held = false;
      }
      if (!Joystick[i].button[kRightThumb].is_held) {
        Joystick[i].button[kRightThumb].is_pressed =
            Joystick[i].js_state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB;
        Joystick[i].button[kRightThumb].is_held = false;
      } else if (!(Joystick[i].js_state.Gamepad.wButtons &
                   XINPUT_GAMEPAD_RIGHT_THUMB)) {
        Joystick[i].button[kRightThumb].is_released = true;
        Joystick[i].button[kRightThumb].is_held = false;
      }
      if (!Joystick[i].button[kLeftShoulder].is_held) {
        Joystick[i].button[kLeftShoulder].is_pressed =
            Joystick[i].js_state.Gamepad.wButtons &
            XINPUT_GAMEPAD_LEFT_SHOULDER;
        Joystick[i].button[kLeftShoulder].is_held = false;
      } else if (!(Joystick[i].js_state.Gamepad.wButtons &
                   XINPUT_GAMEPAD_LEFT_SHOULDER)) {
        Joystick[i].button[kLeftShoulder].is_released = true;
        Joystick[i].button[kLeftShoulder].is_held = false;
      }
      if (!Joystick[i].button[kRightShoulder].is_held) {
        Joystick[i].button[kRightShoulder].is_pressed =
            Joystick[i].js_state.Gamepad.wButtons &
            XINPUT_GAMEPAD_RIGHT_SHOULDER;
        Joystick[i].button[kRightShoulder].is_held = false;
      } else if (!(Joystick[i].js_state.Gamepad.wButtons &
                   XINPUT_GAMEPAD_RIGHT_SHOULDER)) {
        Joystick[i].button[kRightShoulder].is_released = true;
        Joystick[i].button[kRightShoulder].is_held = false;
      }
      if (!Joystick[i].button[kA].is_held) {
        Joystick[i].button[kA].is_pressed =
            Joystick[i].js_state.Gamepad.wButtons & XINPUT_GAMEPAD_A;
        Joystick[i].button[kA].is_held = false;
      } else if (!(Joystick[i].js_state.Gamepad.wButtons & XINPUT_GAMEPAD_A)) {
        Joystick[i].button[kA].is_released = true;
        Joystick[i].button[kA].is_held = false;
      }
      if (!Joystick[i].button[kB].is_held) {
        Joystick[i].button[kB].is_pressed =
            Joystick[i].js_state.Gamepad.wButtons & XINPUT_GAMEPAD_B;
        Joystick[i].button[kB].is_held = false;
      } else if (!(Joystick[i].js_state.Gamepad.wButtons & XINPUT_GAMEPAD_B)) {
        Joystick[i].button[kB].is_released = true;
        Joystick[i].button[kB].is_held = false;
      }
      if (!Joystick[i].button[kX].is_held) {
        Joystick[i].button[kX].is_pressed =
            Joystick[i].js_state.Gamepad.wButtons & XINPUT_GAMEPAD_X;
        Joystick[i].button[kX].is_held = false;
      } else if (!(Joystick[i].js_state.Gamepad.wButtons & XINPUT_GAMEPAD_X)) {
        Joystick[i].button[kX].is_released = true;
        Joystick[i].button[kX].is_held = false;
      }
      if (!Joystick[i].button[kY].is_held) {
        Joystick[i].button[kY].is_pressed =
            Joystick[i].js_state.Gamepad.wButtons & XINPUT_GAMEPAD_Y;
        Joystick[i].button[kY].is_held = false;
      } else if (!(Joystick[i].js_state.Gamepad.wButtons & XINPUT_GAMEPAD_Y)) {
        Joystick[i].button[kY].is_released = true;
        Joystick[i].button[kY].is_held = false;
      }

      Joystick[i].axis[kLeftTrigger] =
          Joystick[i].js_state.Gamepad.bLeftTrigger;
      Joystick[i].axis[kRightTrigger] =
          Joystick[i].js_state.Gamepad.bRightTrigger;

      Joystick[i].axis[kLeftThumbX] = Joystick[i].js_state.Gamepad.sThumbLX;
      Joystick[i].axis[kLeftThumbY] = Joystick[i].js_state.Gamepad.sThumbLY;
      Joystick[i].axis[kRightThumbX] = Joystick[i].js_state.Gamepad.sThumbRX;
      Joystick[i].axis[kRightThumbY] = Joystick[i].js_state.Gamepad.sThumbRY;
    } else {
      // Joystick is not connected
    }
  }
#endif
}

#ifndef _WIN32
// TODO: implement joystick rumble for linux
#else
void SendRumble(i32 controller, u16 left, u16 right) {
  W.xinput_set_state(controller, &(XINPUT_VIBRATION){left, right});
}
#endif

void DrawFontSprite(Sprite* spr, i32 size_x, i32 size_y, i32 x, i32 y, char* text, u32 color, i32 scale, i32 space_x, i32 space_y){
  int32_t text_x = 0, text_y = 0;
  size_t str_len = strlen(text);
  for(size_t i = 0; i < str_len; i++){
    if(text[i] == '\n'){
      text_x = 0; text_y -= size_y * scale + space_y;}
    else{
      uint32_t char_index_x = (text[i] - 32) % 16, char_index_y = (text[i] - 32) / 16;
      if(scale > 1){
        for(uint32_t j = 0; j < size_x; j++)
          for(uint32_t k = 0; k < size_y; k++)
            if(spr->data[k + char_index_y * size_y][(j + char_index_x * size_x) * 4])
              for (uint32_t scaled_i = 0; scaled_i < scale; scaled_i++)
                for (uint32_t scaled_j = 0; scaled_j < scale; scaled_j++)
                  D(x + text_x + (j * scale) + scaled_i, y + text_y + (k * scale) + scaled_j, color);
      }
      else{
        for(uint32_t j = 0; j < size_x; j++)
          for(uint32_t k = 0; k < size_y; k++)
            if(spr->data[k + char_index_y * size_y][(j + char_index_x * size_x) * 4])
              D(x + text_x + j, y + text_y + k, color);}
      text_x += (size_x + space_x) * scale ;}}
}

void DrawSprite(Sprite *spr) {
  for (i32 i = 0; i < spr->height; i++)
    for (i32 j = 0; j < spr->width; j++)
      D(spr->x + j, spr->y + i,
        spr->data[i][j * 4] << 24 | spr->data[i][j * 4 + 1] << 16 |
            (spr->data[i][j * 4 + 2]) << 8 | spr->data[i][j * 4 + 3]);
}

void FreeSprite(Sprite *spr) {
  Sprite tmp = {0};
  for (i32 i = 0; i < spr->height; i++)
    free(spr->data[i]);
  free(spr->data);
  *spr = tmp;
}

void ToggleFullscreen(void) {
#ifndef _WIN32
  // TODO: make this (function) work
  // I have no idea how to do this
  if (W.is_fullscreen) {
    SetWindowSize(W.previous_width, W.previous_height);
    W.is_fullscreen = false;
  } else {
    W.previous_width = W.width;
    W.previous_height = W.height;
    SetWindowSize(DisplayWidth(W.display, DefaultScreen(W.display)),
                  DisplayHeight(W.display, DefaultScreen(W.display)));
    W.is_fullscreen = true;
  }
#else
  if (W.is_fullscreen) {
    W.is_fullscreen = false;
    SetWindowSize(W.previous_width, W.previous_height);
    // SetWindowLongPtr(W.handle, GWL_STYLE,
    //                  WS_CAPTION | WS_VISIBLE | WS_SYSMENU);
    // RECT rect = {0, 0, W.previous_width, W.previous_height};
    // AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW | WS_VISIBLE, false, 0);
    // MoveWindow(W.handle, (GetSystemMetrics(SM_CXSCREEN) / 2) -
    // (W.previous_width / 2),
    //            (GetSystemMetrics(SM_CYSCREEN) / 2) - (W.previous_height / 2),
    //            rect.right - rect.left, rect.bottom - rect.top, true);
  } else {
    W.is_fullscreen = true;
    W.previous_width = W.width;
    W.previous_height = W.height;
    SetWindowSize(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
    // SetWindowLongPtr(W.handle, GWL_STYLE, WS_POPUP | WS_VISIBLE);
    // MoveWindow(W.handle, 0, 0, GetSystemMetrics(SM_CXSCREEN),
    //            GetSystemMetrics(SM_CYSCREEN), true);
  }
#endif
}

Sprite AllocSprite(const u8 start[], i32 len, i32 x, i32 y) {
  Sprite spr = {
      x,
      y,
  };
  u8 *reverse_rows = stbi_load_from_memory(start, len, &spr.width, &spr.height,
                                           &spr.channels, 4);
  // Reverse row order (from "left to right, top to bottom" to "left to right,
  // bottom to top")
  spr.data = (uint8_t **)malloc(sizeof(u8 *) * spr.height);
  for (i32 i = 0; i < spr.height; i++) {
    spr.data[i] = (uint8_t *)malloc(4 * spr.width);
    memcpy(spr.data[i], reverse_rows + (spr.height - 1 - i) * 4 * spr.width,
           4 * spr.width);
  }

  free(reverse_rows);
  return spr;
}

void InitializeAudio(void) {
  ma_engine_init(NULL, &W.audio_engine);
  W.audio_decoders = CreateList(ma_decoder);
  W.decoder_config = ma_decoder_config_init_default();
}

void PlaySound(const char *name) {
  ma_engine_play_sound(&W.audio_engine, name, NULL);
}
void DeclareSound(const u8 start[], i32 len, const char *name) {
  ma_resource_manager_register_encoded_data(
      ma_engine_get_resource_manager(&W.audio_engine), name, start, len);
}
// TODO: Add a way to either keep track of malloc-ed sounds or to free them
Sound AllocSound(const u8 start[], i32 len, bool loops) {
  ma_decoder decoder = {0};
  ListPushBack(&W.audio_decoders, &decoder);
  ma_decoder_init_memory(start, len, &W.decoder_config,
                         (ma_decoder *)ListBack(W.audio_decoders));

  ma_sound sound = {0};
  ma_sound_init_from_data_source(&W.audio_engine,
                                 (ma_decoder *)ListBack(W.audio_decoders),
                                 MA_SOUND_FLAG_DECODE, NULL, &sound);

  if (loops)
    ma_sound_set_looping(&sound, MA_TRUE);

  return sound;
}

List AllocList(size_t sz) {
  List l = {(Node *)malloc(sizeof(Node)), sz, 0};
  l.sentinel->prev = l.sentinel->next = l.sentinel;
  l.sentinel->data = NULL;
  return l;
}

void FreeList(List *self) {
  while (ListPopBack(self))
    ;
  free(self->sentinel);
  List temp = {0};
  *self = temp;
}

void ListPushBack(List *self, void *element) {
  Node *new_node = (Node *)malloc(sizeof(Node));
  new_node->data = malloc(self->sz);
  new_node->next = self->sentinel;
  if (ListEmpty(*self)) {
    self->sentinel->next = new_node;
    new_node->prev = self->sentinel;
  } else {
    new_node->prev = self->sentinel->prev;
    self->sentinel->prev->next = new_node;
  }
  self->sentinel->prev = new_node;
  memmove(new_node->data, element, self->sz);
  self->n++;
}

void ListPushFront(List *self, void *element) {
  Node *new_node = (Node *)malloc(sizeof(Node));
  new_node->data = malloc(self->sz);
  new_node->prev = self->sentinel;
  if (ListEmpty(*self)) {
    self->sentinel->prev = new_node;
    new_node->next = self->sentinel;
  } else {
    new_node->next = self->sentinel->next;
    self->sentinel->next->prev = new_node;
  }
  self->sentinel->next = new_node;
  memmove(new_node->data, element, self->sz);
  self->n++;
}

bool ListPopBack(List *self) {
  if (ListEmpty(*self))
    return false;
  Node *old_node = self->sentinel->prev;
  self->sentinel->prev = old_node->prev;
  self->sentinel->prev->next = self->sentinel;
  free(old_node->data);
  free(old_node);
  self->n--;
  return true;
}

bool ListPopFront(List *self) {
  if (ListEmpty(*self))
    return false;
  Node *old_node = self->sentinel->next;
  self->sentinel->next = old_node->next;
  self->sentinel->next->prev = self->sentinel;
  free(old_node->data);
  free(old_node);
  self->n--;
  return true;
}

void *ListBack(List l) {
  if (ListEmpty(l))
    return NULL;
  return l.sentinel->prev->data;
}

void *ListFront(List l) {
  if (ListEmpty(l))
    return NULL;
  return l.sentinel->next->data;
}

bool ListEmpty(List l) { return !l.n; }

int32_t ListSize(List l) { return l.n; }

ListIterator ListIterateFromFront(List *self) {
  ListIterator it = {self->sentinel->next, self};
  return it;
}

ListIterator ListIterateFromBack(List *self) {
  ListIterator it = {self->sentinel->prev, self};
  return it;
}

void ListInsertPrev(ListIterator *self, void *element) {
  Node *new_node = (Node *)malloc(sizeof(Node));
  new_node->data = malloc(self->list->sz);
  memmove(new_node->data, element, self->list->sz);
  new_node->prev = self->cur->prev;
  new_node->next = self->cur;
  new_node->prev->next = new_node;
  self->cur->prev = new_node;
  self->list->n++;
}

void ListInsertNext(ListIterator *self, void *element) {
  Node *new_node = (Node *)malloc(sizeof(Node));
  new_node->data = malloc(self->list->sz);
  memmove(new_node->data, element, self->list->sz);
  new_node->next = self->cur->next;
  new_node->prev = self->cur;
  new_node->next->prev = new_node;
  self->cur->next = new_node;
  self->list->n++;
}

bool ListRemovePrev(ListIterator *self) {
  if (ListEmpty(*self->list))
    return false;
  Node *old_node = self->cur->prev;
  self->cur->prev = old_node->prev;
  self->cur->prev->next = self->cur;
  free(old_node->data);
  free(old_node);
  self->list->n--;
  return true;
}

bool ListRemoveNext(ListIterator *self) {
  if (ListEmpty(*self->list))
    return false;
  Node *old_node = self->cur->next;
  self->cur->next = old_node->next;
  self->cur->next->prev = self->cur;
  free(old_node->data);
  free(old_node);
  self->list->n--;
  return true;
}

ListIterator ListRemove(ListIterator *self) {
  if (ListEmpty(*self->list))
    return (ListIterator){0};
  Node *new_node = self->cur->next;
  self->cur->prev->next = self->cur->next;
  self->cur->next->prev = self->cur->prev;
  self->list->n--;
  ListIterator new_it = {new_node, self->list};
  free(self->cur->data);
  free(self->cur);
  return new_it;
}

void *ListPrevElement(ListIterator it) {
  if (it.cur->prev == it.list->sentinel)
    return it.cur->prev->prev->data;
  return it.cur->prev->data;
}

void *ListNextElement(ListIterator it) {
  if (it.cur->next == it.list->sentinel)
    return it.cur->next->next->data;
  return it.cur->next->data;
}

void *ListElement(ListIterator it) { return it.cur->data; }

ListIterator ListPrev(ListIterator it) {
  if (it.cur == it.list->sentinel)
    return it;
  it.cur = it.cur->prev;
  return it;
}

ListIterator ListNext(ListIterator it) {
  if (it.cur == it.list->sentinel)
    return it;
  it.cur = it.cur->next;
  return it;
}

bool ListEnd(ListIterator it) { return (it.cur == it.list->sentinel); }

#endif
