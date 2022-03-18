#include "Zenibou.h"
#include <stdio.h>
#include <stdlib.h>
#include "fonts/font5x6.h"
#include "fonts/font5x5.h"
#include "sprites/test.h"

int main(void){
  InitWindow(600,600,"Example");

  while(!WindowShouldClose()){
    BeginDrawing();

    for(int i = 0; i < 75; i++)
      for(int j = 0; j < 75; j++){
        // Color is defined as RGBA (just like raylib)
        unsigned int color = (rand() & 0x0FF0) << 20 | (rand() & 0x0FF0) << 12 | (rand() & 0x0FF0) << 8 | 0xFF;
        DrawRectangle(j << 3, i << 3, 8, 8, color);}

    for(int i = 0; i < 256; i++){
      if(IsKeyPressed(i))
        printf("The pressed key is %X ('%c'). %lf(%lf)\n", i, i, GetFrameTime(), GetTime());
      if(IsKeyReleased(i))
        printf("The released key is %X ('%c'). %lf(%lf)\n", i, i, GetFrameTime(), GetTime());}

    DrawString5x6(0,100, "The quick brown fox jumps\n over the lazy dog.!@#$%^\n&*()<>",0x00FFFF, 4, 1, 5);
    DrawString5x5(0,200,"The quick brown fox jumps\n over the lazy dog.!@#$%^\n&*()<>",0x00FFFFFF, 4, 1, 5);
    DrawSpriteTest24x24(0, 360, "The quick brown fox jumps\n over the lazy dog.!@#$%^&*()<>", 1);

    EndDrawing();
  }


  CloseWindow();
  return 0;
}
