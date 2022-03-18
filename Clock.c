#ifndef _ZENIBOU_CLOCK_C_
#define _ZENIBOU_CLOCK_C_

// TODO: remove stdio.h from here or introduce DEBUG macro
#include <stdio.h>
#include "Clock.h"
#include "InputHandling.h"

struct Clock Clock;

void InitializeClock(void){
  Clock.last_second_elapsed_time = 0;
  Clock.last_frame_elapsed_time = 0;
  Clock.total_elapsed_time = 0;
  Clock.frame = 0;
  Clock.time1 = clock();
  Clock.time2 = clock();}

void Tick(void){
  Clock.time2 = clock();
  Clock.last_frame_elapsed_time = ((double)(Clock.time2 - Clock.time1)) / CLOCKS_PER_SEC;
  Clock.time1 = Clock.time2;
  Clock.last_second_elapsed_time += Clock.last_frame_elapsed_time;
  Clock.total_elapsed_time += Clock.last_frame_elapsed_time;
  Clock.frame++;
  if(Clock.last_second_elapsed_time > 1.){
    printf("Frames last second: %llu Mouse: x=%hd y=%hd l=%d m=%d r=%d\n",Clock.frame,Mouse.x,Mouse.y,Mouse.left_pressed,Mouse.middle_pressed,Mouse.right_pressed);
    Clock.last_second_elapsed_time = 0.;
    Clock.frame = 0;}}

double GetTime(void){
  return Clock.total_elapsed_time;
}
double GetFrameTime(void){
  return Clock.last_frame_elapsed_time;
}

#endif
