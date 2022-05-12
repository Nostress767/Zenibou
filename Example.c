#include "Zenibou.h"
#include <stdio.h>
#include <stdlib.h>
#include "fonts/font5x6.h"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

void MainLoop(void);

int main(void){
  StartEngine(600,600,"サンプル");
  
#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(MainLoop, 120, 1);
#else
  while(Window.is_running){
    MainLoop();
  }
#endif
  
  return 0;
}

void MainLoop(void){
  char stringo[12] = {0};
  BeginFrame();
    if(Key['F'].is_pressed)
      ToggleFullscreen();
    else if(Key['T'].is_pressed)
      SetWindowSize(400, 400);
    else if(Key['P'].is_pressed)
      // TODO: maybe kill the window in a cleaner way?
      Window.is_running = false;
    for(int i = 0; i < 512; i++){
      if(Key[i].is_pressed)
        printf("The pressed key is %03X ('%03d'). It was pressed on frame %llu(%lf)\n", i, i, Clock.frame, Clock.total_elapsed_time);
      if(Key[i].is_released)
        printf("The released key is %03X ('%03d'). It was released on frame %llu(%lf)\n", i, i, Clock.frame, Clock.total_elapsed_time);}
    C(0xFFFF00FF);

    for(i32 i = 0; i < (Window.starting_height >> 3); i++)
      for(i32 j = 0; j < (Window.starting_width >> 3); j++){
        // Color is defined as RGBA (just like raylib)
        u32 color = (rand() & 0x0FF0) << 20 | (rand() & 0x0FF0) << 12 | (rand() & 0x0FF0) << 8 | 0xFF;
        for(int32_t m = 0; m < 8; m++)
          for(int32_t n = 0; n < 8; n++)
            D((j << 3)+n, (i << 3)+m, color);}

    snprintf(stringo,12,"FPS: %05d\n",Clock.frames_last_second);
    DrawString5x6(0,400, stringo, 0xFF0000FF, 4, 1, 5);
  EndFrame();
}

