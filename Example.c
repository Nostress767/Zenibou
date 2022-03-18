#include "Zenibou.h"
#include <stdio.h>
#include <stdlib.h>
#include "fonts/font5x6.h"
#include "fonts/font5x5.h"
#include "sprites/test.h"

// TODO: Fix sprite and font generating scripts (change DrawPixel to D, and check if fail or no fail)

int main(void){
  StartEngine(600,600,"サンプル");
  char stringo[12] = {0};
  while(Window.is_running){
    BeginFrame();
      if(Key['Q'].is_pressed)
        SetWindowSizes(640,480);
      else if(Key['W'].is_pressed)
        SetWindowSizes(1280,720);
      else if(Key['E'].is_pressed)
        SetWindowSizes(1920,1080);
      else if(Key['R'].is_pressed)
        SetWindowSizes(600,600);
      else if(Key['T'].is_pressed)
        // TODO: maybe kill the window in a cleaner way?
        Window.is_running = false;
      for(int i = 0; i < 512; i++){
        if(Key[i].is_pressed)
          printf("The pressed key is %03X ('%03d'). It was pressed on frame %llu(%lf)\n", i, i, Clock.frame, Clock.total_elapsed_time);
        if(Key[i].is_released)
          printf("The released key is %03X ('%03d'). It was released on frame %llu(%lf)\n", i, i, Clock.frame, Clock.total_elapsed_time);}
      DrawString5x5(0,200,"The quick brown fox jumps\n over the lazy dog.!@#$%^\n&*()<>",0x00FFFFFF, 4, 1, 5);
      C(0xFFFF00FF);
      D(100,100,0xFF0000FF);
      snprintf(stringo,11,"FPS: %05d\n",Clock.frames_last_second);
      DrawSpriteTest24x24(0, 360, "The quick brown fox jumps\n over the lazy dog.!@#$%^&*()<>", 1);
      DrawString5x6(0,100, "The quick brown fox jumps\n over the lazy dog.!@#$%^\n&*()<>",0xFF0000FF, 4, 1, 5);
      DrawString5x6(0,200, stringo, 0xFF0000FF, 4, 1, 5);
    EndFrame();
  }
  return 0;
}
