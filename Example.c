#include "Zenibou.h"
#include <stdio.h>

IncludeMedia(Sound1, mp3);
IncludeMedia(Sound2, mp3);

int main(void) {
  StartEngine(600, 600, "サンプル");

  DeclareSound(MediaStart(Sound1, mp3), MediaSize(Sound1, mp3), "Test1");
  DeclareSound(MediaStart(Sound2, mp3), MediaSize(Sound2, mp3), "Test2");

  while (W.is_running) {
    char stringo[12] = {0};
    BeginFrame();
    if (Key['G'].is_pressed)
      PlaySound("Test1");
    else if (Key['H'].is_pressed)
      PlaySound("Test2");
    else if (Key['F'].is_pressed)
      // TODO: fix this function on linux
      ToggleFullscreen();
    else if (Key['R'].is_pressed)
      SetWindowSize(320, 320);
    else if (Key['T'].is_pressed)
      SetWindowSize(800, 800);
    else if (Key['P'].is_pressed)
      W.is_running = false;

    for (i32 i = 0; i < 4; i++) {
      if (Joystick[i].button[kLeftShoulder].is_pressed)
        PlaySound("Test1");
      else if (Joystick[i].button[kRightShoulder].is_pressed)
        PlaySound("Test2");
      else if (Joystick[i].button[kStart].is_pressed)
        // TODO: fix this function on linux
        ToggleFullscreen();
      else if (Joystick[i].button[kLeftThumb].is_pressed)
        SetWindowSize(320, 320);
      else if (Joystick[i].button[kRightThumb].is_pressed)
        SetWindowSize(800, 800);
      else if (Joystick[i].button[kBack].is_pressed)
        W.is_running = false;
    }

    for (int i = 0; i < 256; i++) {
      if (Key[i].is_pressed)
        printf("The pressed key is %03X ('%03d'). It was pressed on frame "
               "%llu(%lf)\n",
               i, i, Clock.frame, Clock.total_elapsed_time);
      // if (Key[i].is_held)
      //   printf("The held key is %03X ('%03d'). It was held on frame "
      //          "%llu(%lf)\n",
      //          i, i, Clock.frame, Clock.total_elapsed_time);
      if (Key[i].is_released)
        printf("The released key is %03X ('%03d'). It was released on frame "
               "%llu(%lf)\n",
               i, i, Clock.frame, Clock.total_elapsed_time);
    }
    if (Mouse.left_pressed)
      printf("Mouse left pressed!\n");
    if (Mouse.left_held)
      printf("Mouse left is being held\n");
    if (Mouse.left_released)
      printf("Mouse left released!\n");
    if (Mouse.middle_pressed)
      printf("Mouse middle pressed!\n");
    if (Mouse.middle_held)
      printf("Mouse middle is being held\n");
    if (Mouse.middle_released)
      printf("Mouse middle released!\n");
    if (Mouse.right_pressed)
      printf("Mouse right pressed!\n");
    if (Mouse.right_held)
      printf("Mouse right is being held\n");
    if (Mouse.right_released)
      printf("Mouse right released!\n");

    for (i32 i = 0; i < 4; i++) {
      for (i32 j = 0; j < 32; j++) {
        if (Joystick[i].button[j].is_pressed)
          printf("Controller %d pressed button %d. It was pressed on frame "
                 "%llu(%lf)\n",
                 i, j, Clock.frame, Clock.total_elapsed_time);
        // if (Joystick[i].button[j].is_held)
        //   printf("Controller %d is holding button %d. It was held on frame "
        //          "%llu(%lf)\n",
        //          i, j, Clock.frame, Clock.total_elapsed_time);
        if (Joystick[i].button[j].is_released)
          printf("Controller %d released button %d. It was released on frame "
                 "%llu(%lf)\n",
                 i, j, Clock.frame, Clock.total_elapsed_time);
      }
    }

    // Clears screen to green
    C(0x00FF00);

    // Random color squares (yes, shamelessly copied from PixelGameEngine)
    for (i32 i = 0; i < (W.height >> 3); i++)
      for (i32 j = 0; j < (W.width >> 3); j++) {
        // Color is defined as ARGB, the first 8 bits are for padding only.
        u32 color = (rand() & 0x0FF0) << 20 | (rand() & 0x0FF0) << 12 |
                    (rand() & 0x0FF0) << 8;
        for (int32_t m = 0; m < 8; m++)
          for (int32_t n = 0; n < 8; n++)
            D((j << 3) + n, (i << 3) + m, color);
      }

    snprintf(stringo, 12, "FPS: %05d\n", Clock.frames_last_second);
    DrawString5x6(0, 30, stringo, 0xFF0000, 4, 1, 5);
    EndFrame();
  }

  return 0;
}
