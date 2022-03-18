#include "Zenibou.h"
#include <stdio.h>
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
    if(Key['Q'].is_pressed)
      SetWindowSizes(640,480);
    else if(Key['W'].is_pressed)
      SetWindowSizes(1280,720);
    else if(Key['E'].is_pressed)
      SetWindowSizes(1920,1080);
    else if(Key['R'].is_pressed)
      SetWindowSizes(600,600);
    else if(Key['P'].is_pressed)
      // TODO: maybe kill the window in a cleaner way?
      Window.is_running = false;
    for(int i = 0; i < 512; i++){
      if(Key[i].is_pressed)
        printf("The pressed key is %03X ('%03d'). It was pressed on frame %llu(%lf)\n", i, i, Clock.frame, Clock.total_elapsed_time);
      if(Key[i].is_released)
        printf("The released key is %03X ('%03d'). It was released on frame %llu(%lf)\n", i, i, Clock.frame, Clock.total_elapsed_time);}
    C(0xFFFF00FF);
    D(100,100,0xFF0000FF);
    snprintf(stringo,11,"FPS: %05d\n",Clock.frames_last_second);
    DrawString5x6(0,400, stringo, 0xFF0000FF, 4, 1, 5);
    //DrawSpriteTest24x24(0, 360, "The quick brown fox jumps\n over the lazy dog.!@#$%^&*()<>", 1);
    //DrawSpriteTest24x24(0, 160, "s s s", 5);
  EndFrame();
}

