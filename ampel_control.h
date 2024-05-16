#include <stdint.h>

#ifndef _AMPEL_CONTROL_H
#define _AMPEL_CONTROL_H

#define TIME_IN_RED 10
#define TIME_IN_RED_YELLOW 2
#define TIME_IN_YELLOW 4
#define TIME_IN_GREEN 10

typedef enum { RED = 1, RED_YELLOW, YELLOW, GREEN } AmpelState;

typedef struct {
  uint8_t red;
  uint8_t yellow;
  uint8_t green;

  AmpelState current_state;
  AmpelState next_state;

  uint8_t time_in_state;
} Ampel;

void ampel_control(Ampel *ampel);
void time_in_state(Ampel *ampel);

#endif

// end of file