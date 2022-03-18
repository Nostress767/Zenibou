#ifndef _ZENIBOU_CLOCK_C_
#define _ZENIBOU_CLOCK_C_

#include "Clock.h"

struct Clock Clock;

void InitializeClock(void){
  Clock.last_second_elapsed_time = 0;
  Clock.last_frame_elapsed_time = 0;
  Clock.total_elapsed_time = 0;
  Clock.frame = 0;
  Clock.frames_last_second = 0;
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
    Clock.frames_last_second = (int32_t) Clock.frame;
    Clock.last_second_elapsed_time = 0.;
    Clock.frame = 0;}}

#endif
