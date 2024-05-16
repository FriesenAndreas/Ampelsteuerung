#include "ampel_control.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>

// Flags and variables
bool init_flag = false;
bool one_second_passed = false;

time_t time_1 = 0;
time_t time_2 = 0;

Ampel ampel = {0, 0, 0, RED, RED_YELLOW, TIME_IN_RED};

uint16_t simulation_counter = 100;

// Function prototypes
void timer_isr_simulation(void);

/**
 * @brief Main function
 */

int main() {

  if (!init_flag) {
    printf("Traffic light simulation started\n");

    init_flag = true;
  }

  while (simulation_counter != 0) {

    timer_isr_simulation();

    if (one_second_passed) {
      ampel_control(&ampel);

      simulation_counter--;

      one_second_passed = false;
    }
  }

  return 0;
}

/**
 * @brief Simulate the timer interrupt service routine
 */
void timer_isr_simulation(void) {
  time(&time_2);

  if (time_2 - time_1 >= 1) {
    one_second_passed = true;
    time_1 = time_2;
  }
}

// end of file