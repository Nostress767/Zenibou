#ifndef _ZENIBOU_CLOCK_H_
#define _ZENIBOU_CLOCK_H_

#include <time.h>
#include <stdint.h>

void InitializeClock(void);
void Tick(void);
double GetTime(void);
double GetFrameTime(void);

struct Clock{
  double last_second_elapsed_time, last_frame_elapsed_time, total_elapsed_time;
  uint64_t frame;
  clock_t time1, time2;};

extern struct Clock Clock;

#endif
