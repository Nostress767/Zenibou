#include "Zenibou.h"
#include <stdio.h>
#include <stdlib.h>
#include "fonts/font5x6.h"
//#include "sprites/test.h"

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
    //DrawSpriteTest24x24(0, 360, "The quick brown fox jumps\n over the lazy dog.!@#$%^&*()<>", 1);
    //DrawSpriteTest24x24(0, 160, "s s s", 5);
  EndFrame();
}

//#include <stdio.h>
//#include <stdlib.h>
//#include "fonts/font5x6.h"
//#include "fonts/font5x5.h"
//#include "sprites/test.h"

// TODO: continue investigating tcc and platform_web
// TODO: Fix sprite and font generating scripts (change DrawPixel to D, and check if fail or no fail)

  //char stringo[12] = {0};

    //DrawString5x5(0,200,"The quick brown fox jumps\n over the lazy dog.!@#$%^\n&*()<>",0x00FFFFFF, 4, 1, 5);
    //snprintf(stringo,11,"FPS: %05d\n",Clock.frames_last_second);
    //DrawSpriteTest24x24(0, 360, "The quick brown fox jumps\n over the lazy dog.!@#$%^&*()<>", 1);
    //DrawString5x6(0,100, "The quick brown fox jumps\n over the lazy dog.!@#$%^\n&*()<>",0xFF0000FF, 4, 1, 5);
    //DrawString5x6(0,200, stringo, 0xFF0000FF, 4, 1, 5);
