#include "ampel_control.h"
#include <stdint.h>
#include <stdio.h>

// local function prototypes
void show_ampel_light(Ampel *ampel);
void switch_ampel_state(Ampel *ampel);

/**
 * @brief Control the traffic light
 * @param ampel Pointer to the traffic light
 * @return 1 if the traffic light has changed, 0 otherwise
 */

void ampel_control(Ampel *ampel) {
  AmpelState state = ampel->current_state;

  switch (state) {
  case RED:
    ampel->current_state = RED;
    ampel->next_state = RED_YELLOW;
    ampel->red = 1;
    ampel->yellow = 0;
    ampel->green = 0;
    break;
  case RED_YELLOW:
    ampel->current_state = RED_YELLOW;
    ampel->next_state = GREEN;
    ampel->red = 1;
    ampel->yellow = 1;
    ampel->green = 0;
    break;
  case YELLOW:
    ampel->current_state = YELLOW;
    ampel->next_state = RED;
    ampel->red = 0;
    ampel->yellow = 1;
    ampel->green = 0;
    break;
  case GREEN:
    ampel->current_state = GREEN;
    ampel->next_state = YELLOW;
    ampel->red = 0;
    ampel->yellow = 0;
    ampel->green = 1;
    break;
  default:
    break;
  }

  show_ampel_light(ampel);

  switch_ampel_state(ampel);
}

void time_in_state(Ampel *ampel) {

  if (ampel->time_in_state > 0) {
    ampel->time_in_state--;
  }

  printf("Time in state: %d\n", ampel->time_in_state);
}

void show_ampel_light(Ampel *ampel) {
  if (ampel->current_state == RED) {
    printf("RED\n");
  }

  if (ampel->current_state == RED_YELLOW) {
    printf("RED_YELLOW\n");
  }

  if (ampel->current_state == YELLOW) {
    printf("YELLOW\n");
  }

  if (ampel->current_state == GREEN) {
    printf("GREEN\n");
  }
}

void switch_ampel_state(Ampel *ampel) {
  time_in_state(ampel);

  if (ampel->time_in_state == 0) {
    ampel->current_state = ampel->next_state;

    switch (ampel->current_state) {
    case RED:
      ampel->time_in_state = TIME_IN_RED;
      break;
    case RED_YELLOW:
      ampel->time_in_state = TIME_IN_RED_YELLOW;
      break;
    case YELLOW:
      ampel->time_in_state = TIME_IN_YELLOW;
      break;
    case GREEN:
      ampel->time_in_state = TIME_IN_GREEN;
      break;
    default:
      break;
    }
  }
}
// end of fil